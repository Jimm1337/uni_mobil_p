-- 1. SEQUENCE

CREATE SEQUENCE IF NOT EXISTS GenID
    AS INT
    START WITH 0
    INCREMENT BY 1
    MINVALUE 0
    NO CYCLE;

ALTER SEQUENCE GenID RESTART WITH 0;

-- 2. TABLE

CREATE TABLE IF NOT EXISTS Places
(
    ID          INT          NOT NULL PRIMARY KEY DEFAULT nextval('genid'),
    Name        VARCHAR(100) NOT NULL UNIQUE,
    Description VARCHAR(500),
    Location    VARCHAR(255) NOT NULL,
    Key         VARCHAR(40)  NOT NULL UNIQUE
);

CREATE TABLE IF NOT EXISTS Users
(
    ID       INT          NOT NULL PRIMARY KEY DEFAULT nextval('genid'),
    Username VARCHAR(100) NOT NULL UNIQUE,
    Login    VARCHAR(100) NOT NULL UNIQUE,
    Password VARCHAR(100) NOT NULL,
    Admin    BOOLEAN      NOT NULL             DEFAULT FALSE,
    Points   INT          NOT NULL             DEFAULT 0
);

CREATE TABLE IF NOT EXISTS Comments
(
    ID       INT          NOT NULL PRIMARY KEY DEFAULT nextval('genid'),
    UserID   INT          NOT NULL REFERENCES Users (ID),
    PlaceID  INT          NOT NULL REFERENCES Places (ID),
    Content  VARCHAR(500) NOT NULL,
    TimeStmp TIMESTAMP    NOT NULL             DEFAULT CURRENT_TIMESTAMP,
    Likes    INT          NOT NULL             DEFAULT 0
);

CREATE TABLE IF NOT EXISTS Visits
(
    ID       INT       NOT NULL PRIMARY KEY DEFAULT nextval('genid'),
    UserID   INT       NOT NULL REFERENCES Users (ID),
    PlaceID  INT       NOT NULL REFERENCES Places (ID),
    TimeStmp TIMESTAMP NOT NULL             DEFAULT CURRENT_TIMESTAMP
);

-- 3. INSERT

INSERT INTO Places (Name, Description, Location, Key)
VALUES ('Example Place 0', 'Example place description 0', 'example place location 0', 'example-key-0'),
       ('Example Place 1', 'Example place description 1', 'example place location 1', 'example-key-1'),
       ('Example Place 2', 'Example place description 2', 'example place location 2', 'example-key-2'),
       ('Example Place 3', 'Example place description 3', 'example place location 3', 'example-key-3'),
       ('Example Place 4', 'Example place description 4', 'example place location 4', 'example-key-4')
ON CONFLICT (ID) DO NOTHING;

INSERT INTO Users (Username, Login, Password, Admin)
VALUES ('Admin 0', 'admin0', 'admin', TRUE),
       ('Example User 0', 'example-user-0', 'example-password-0', FALSE),
       ('Example User 1', 'example-user-1', 'example-password-1', FALSE),
       ('Example User 2', 'example-user-2', 'example-password-2', FALSE),
       ('Example User 3', 'example-user-3', 'example-password-3', FALSE),
       ('Example User 4', 'example-user-4', 'example-password-4', FALSE)
ON CONFLICT (ID) DO NOTHING;

INSERT INTO Comments (UserID, PlaceID, Content)
VALUES (6, 0, 'Example comment 0'),
       (7, 0, 'Example comment 1'),
       (8, 0, 'Example comment 2'),
       (9, 0, 'Example comment 3'),
       (10, 0, 'Example comment 4')
ON CONFLICT (ID) DO NOTHING;

INSERT INTO Visits (UserID, PlaceID)
VALUES (6, 1),
       (7, 1),
       (8, 1),
       (9, 1),
       (10, 1)
ON CONFLICT (ID) DO NOTHING;

-- 4. VIEW

CREATE MATERIALIZED VIEW IF NOT EXISTS Ranking AS
SELECT ID AS UserID,
       Username,
       Points
FROM Users
ORDER BY Points DESC;

CREATE MATERIALIZED VIEW IF NOT EXISTS PlacesAlphabetically AS
SELECT ID AS PlaceID,
       Name,
       Description,
       Location
FROM Places
ORDER BY Name;

-- 5. INDEX

CREATE INDEX IF NOT EXISTS idx_hash_places_id ON Places USING HASH (ID);
CREATE INDEX IF NOT EXISTS idx_hash_users_id ON Users USING HASH (ID);
CREATE INDEX IF NOT EXISTS idx_hash_comments_id ON Comments USING HASH (ID);
CREATE INDEX IF NOT EXISTS idx_hash_visits_id ON Visits USING HASH (ID);
CREATE INDEX IF NOT EXISTS idx_hash_places_alphabetically_id ON PlacesAlphabetically USING HASH (PlaceID);
CREATE INDEX IF NOT EXISTS idx_hash_ranking_id ON Ranking USING HASH (UserID);

CREATE INDEX IF NOT EXISTS idx_hash_places_key ON Places USING HASH (Key);
CREATE INDEX IF NOT EXISTS idx_btree_places_name ON Places USING BTREE (Name);
CREATE INDEX IF NOT EXISTS idx_btree_places_description ON Places USING BTREE (Description);
CREATE INDEX IF NOT EXISTS idx_btree_places_location ON Places USING BTREE (Location);

CREATE INDEX IF NOT EXISTS idx_hash_users_login ON Users USING HASH (Login);
CREATE INDEX IF NOT EXISTS idx_hash_users_password ON Users USING HASH (Password);
CREATE INDEX IF NOT EXISTS idx_hash_users_admin ON Users USING HASH (Admin);
CREATE INDEX IF NOT EXISTS idx_btree_users_username ON Users USING BTREE (Username);
CREATE INDEX IF NOT EXISTS idx_btree_users_points ON Users USING BTREE (Points);

CREATE INDEX IF NOT EXISTS idx_hash_comments_user_id ON Comments USING HASH (UserID);
CREATE INDEX IF NOT EXISTS idx_hash_comments_place_id ON Comments USING HASH (PlaceID);
CREATE INDEX IF NOT EXISTS idx_btree_comments_content ON Comments USING BTREE (Content);
CREATE INDEX IF NOT EXISTS idx_btree_comments_time ON Comments USING BTREE (TimeStmp);
CREATE INDEX IF NOT EXISTS idx_btree_comments_likes ON Comments USING BTREE (Likes);

CREATE INDEX IF NOT EXISTS idx_hash_visits_user_id ON Visits USING HASH (UserID);
CREATE INDEX IF NOT EXISTS idx_hash_visits_place_id ON Visits USING HASH (PlaceID);
CREATE INDEX IF NOT EXISTS idx_btree_visits_time ON Visits USING BTREE (TimeStmp);

CREATE INDEX IF NOT EXISTS idx_btree_ranking_username ON Ranking USING BTREE (Username);
CREATE INDEX IF NOT EXISTS idx_btree_ranking_points ON Ranking USING BTREE (Points);

CREATE INDEX IF NOT EXISTS idx_btree_places_alphabetically_name ON PlacesAlphabetically USING BTREE (Name);
CREATE INDEX IF NOT EXISTS idx_btree_places_alphabetically_description ON PlacesAlphabetically USING BTREE (Description);
CREATE INDEX IF NOT EXISTS idx_btree_places_alphabetically_location ON PlacesAlphabetically USING BTREE (Location);

-- 6. TRIGGER

CREATE OR REPLACE FUNCTION internal_onUsersChange() RETURNS TRIGGER
    LANGUAGE plpgsql AS
$$
BEGIN
    REFRESH MATERIALIZED VIEW Ranking;
    RETURN NEW;
END
$$;

CREATE OR REPLACE TRIGGER onUsersChange
    AFTER INSERT OR UPDATE OR DELETE
    ON Users
    FOR EACH STATEMENT
EXECUTE FUNCTION internal_onUsersChange();

CREATE OR REPLACE FUNCTION internal_onPlacesChange() RETURNS TRIGGER
    LANGUAGE plpgsql AS
$$
BEGIN
    REFRESH MATERIALIZED VIEW PlacesAlphabetically;
    RETURN NEW;
END
$$;

CREATE OR REPLACE TRIGGER onPlacesChange
    AFTER INSERT OR UPDATE OR DELETE
    ON Places
    FOR EACH STATEMENT
EXECUTE FUNCTION internal_onPlacesChange();

-- 7. FUNCTIONS

CREATE OR REPLACE FUNCTION F_EXISTS_PLACES(arg_name VARCHAR(100))
    RETURNS TABLE
            (
                ID INT
            )
    LANGUAGE plpgsql
AS
$$
BEGIN
    RETURN QUERY
        SELECT ID
        FROM Places
        WHERE Name = arg_name;
END
$$;

CREATE OR REPLACE FUNCTION F_EXISTS_USERS(arg_username VARCHAR(100))
    RETURNS TABLE
            (
                ID INT
            )
    LANGUAGE plpgsql
AS
$$
BEGIN
    RETURN QUERY
        SELECT ID
        FROM Users
        WHERE Username = arg_username;
END
$$;

CREATE OR REPLACE FUNCTION F_EXISTS_VISITS(arg_user_id INT, arg_place_id INT)
    RETURNS TABLE
            (
                ID INT
            )
    LANGUAGE plpgsql
AS
$$
BEGIN
    RETURN QUERY
        SELECT ID
        FROM Visits
        WHERE UserID = arg_user_id
          AND PlaceID = arg_place_id;
END
$$;

CREATE OR REPLACE FUNCTION F_EXISTS_COMMENTS(arg_user_id INT, arg_place_id INT)
    RETURNS TABLE
            (
                ID       INT,
                Content  VARCHAR(500),
                TimeStmp TIMESTAMP
            )
    LANGUAGE plpgsql
AS
$$
BEGIN
    RETURN QUERY
        SELECT ID, Content, TimeStmp
        FROM Comments
        WHERE UserID = arg_user_id
          AND PlaceID = arg_place_id
        ORDER BY TimeStmp DESC;
END
$$;

---- 7.1. LOGIN API
CREATE OR REPLACE FUNCTION F_POST_LOGIN(arg_login VARCHAR(100), arg_password VARCHAR(100))
    RETURNS TABLE
            (
                ID       INT,
                Username VARCHAR(100),
                Points   INT
            )
    LANGUAGE plpgsql
AS
$$
BEGIN
    RETURN QUERY
        SELECT ID,
               Username,
               Points
        FROM Users
        WHERE Login = arg_login
          AND Password = arg_password;
END
$$;

CREATE OR REPLACE FUNCTION F_POST_REGISTER(arg_username VARCHAR(100), arg_login VARCHAR(100), arg_password VARCHAR(100))
    RETURNS TABLE
            (
                ID       INT,
                Username VARCHAR(100),
                Points   INT
            )
    LANGUAGE plpgsql
AS
$$
BEGIN
    RETURN QUERY
        INSERT INTO Users (Username, Login, Password)
            VALUES (arg_username, arg_login, arg_password)
            RETURNING ID, Username, Points;
END
$$;

---- 7.2. USER API
CREATE OR REPLACE FUNCTION F_GET_PLACES_ID(arg_id INT)
    RETURNS TABLE
            (
                ID          INT,
                Name        VARCHAR(100),
                Description VARCHAR(500),
                Location    VARCHAR(255)
            )
    LANGUAGE plpgsql
AS
$$
BEGIN
    RETURN QUERY
        SELECT ID,
               Name,
               Description,
               Location
        FROM PlacesAlphabetically
        WHERE ID = arg_id;
END
$$;

CREATE OR REPLACE FUNCTION F_GET_PLACES_NAME(arg_name VARCHAR(100))
    RETURNS TABLE
            (
                ID          INT,
                Name        VARCHAR(100),
                Description VARCHAR(500),
                Location    VARCHAR(255)
            )
    LANGUAGE plpgsql
AS
$$
BEGIN
    RETURN QUERY
        SELECT ID,
               Name,
               Description,
               Location
        FROM PlacesAlphabetically
        WHERE Name LIKE '%' || arg_name || '%';
END
$$;

CREATE OR REPLACE FUNCTION F_GET_PLACES_LOCATION(arg_location VARCHAR(255))
    RETURNS TABLE
            (
                ID          INT,
                Name        VARCHAR(100),
                Description VARCHAR(500),
                Location    VARCHAR(255)
            )
    LANGUAGE plpgsql
AS
$$
BEGIN
    RETURN QUERY
        SELECT ID,
               Name,
               Description,
               Location
        FROM PlacesAlphabetically
        WHERE Location LIKE '%' || arg_location || '%';
END
$$;

CREATE OR REPLACE FUNCTION F_GET_PLACES_DESCRIPTION(arg_desc VARCHAR(500))
    RETURNS TABLE
            (
                ID          INT,
                Name        VARCHAR(100),
                Description VARCHAR(500),
                Location    VARCHAR(255)
            )
    LANGUAGE plpgsql
AS
$$
BEGIN
    RETURN QUERY
        SELECT ID,
               Name,
               Description,
               Location
        FROM PlacesAlphabetically
        WHERE Description LIKE '%' || arg_desc || '%';
END
$$;

CREATE OR REPLACE FUNCTION F_GET_USERS_ID(arg_id INT)
    RETURNS TABLE
            (
                ID       INT,
                Username VARCHAR(100),
                Points   INT
            )
    LANGUAGE plpgsql
AS
$$
BEGIN
    RETURN QUERY
        SELECT ID,
               Username,
               Points
        FROM Users
        WHERE ID = arg_id;
END
$$;

CREATE OR REPLACE FUNCTION F_GET_USERS_USERNAME(arg_username VARCHAR(100))
    RETURNS TABLE
            (
                ID       INT,
                Username VARCHAR(100),
                Points   INT
            )
    LANGUAGE plpgsql
AS
$$
BEGIN
    RETURN QUERY
        SELECT ID,
               Username,
               Points
        FROM Users
        WHERE Username LIKE '%' || arg_username || '%';
END
$$;

CREATE OR REPLACE FUNCTION F_GET_COMMENTS(arg_place_id INT)
    RETURNS TABLE
            (
                ID       INT,
                UserID   INT,
                Content  VARCHAR(500),
                TimeStmp TIMESTAMP,
                Likes    INT
            )
    LANGUAGE plpgsql
AS
$$
BEGIN
    RETURN QUERY
        SELECT ID,
               UserID,
               PlaceID,
               Content,
               TimeStmp,
               Likes
        FROM Comments
        WHERE PlaceID = arg_place_id
        ORDER BY TimeStmp DESC;
END
$$;

CREATE OR REPLACE FUNCTION F_GET_VISITS_PLACE(arg_place_id INT)
    RETURNS TABLE
            (
                ID       INT,
                UserID   INT,
                PlaceID  INT,
                TimeStmp TIMESTAMP
            )
    LANGUAGE plpgsql
AS
$$
BEGIN
    RETURN QUERY
        SELECT ID,
               UserID,
               PlaceID,
               TimeStmp
        FROM Visits
        WHERE PlaceID = arg_place_id
        ORDER BY TimeStmp DESC;
END
$$;

CREATE OR REPLACE FUNCTION F_GET_VISITS_USER(arg_user_id INT)
    RETURNS TABLE
            (
                ID       INT,
                UserID   INT,
                PlaceID  INT,
                TimeStmp TIMESTAMP
            )
    LANGUAGE plpgsql
AS
$$
BEGIN
    RETURN QUERY
        SELECT ID,
               UserID,
               PlaceID,
               TimeStmp
        FROM Visits
        WHERE UserID = arg_user_id
        ORDER BY TimeStmp DESC;
END
$$;

CREATE OR REPLACE FUNCTION F_GET_RANKING()
    RETURNS TABLE
            (
                ID       INT,
                Username VARCHAR(100),
                Points   INT
            )
    LANGUAGE plpgsql
AS
$$
BEGIN
    RETURN QUERY
        SELECT ID,
               Username,
               Points
        FROM Ranking;
END
$$;

CREATE OR REPLACE FUNCTION F_POST_VISITS_VALIDATE(arg_key VARCHAR(40))
    RETURNS TABLE
            (
                ID INT
            )
    LANGUAGE plpgsql
AS
$$
BEGIN
    RETURN QUERY
        SELECT ID
        FROM Places
        WHERE Key = arg_key;
END
$$;

CREATE OR REPLACE FUNCTION F_POST_VISITS_INSERT(arg_username VARCHAR(100), arg_place_id INT)
    RETURNS TABLE
            (
                ID       INT,
                UserID   INT,
                PlaceID  INT,
                TimeStmp TIMESTAMP
            )
    LANGUAGE plpgsql
AS
$$
DECLARE
    user_id INT;
BEGIN
    SELECT ID INTO user_id FROM Users WHERE Username = arg_username;
    RETURN QUERY
        INSERT INTO Visits (UserID, PlaceID, TimeStmp)
            VALUES (user_id, arg_place_id, CURRENT_TIMESTAMP)
            RETURNING ID, UserID, PlaceID, TimeStmp;
END
$$;

CREATE OR REPLACE FUNCTION F_POST_COMMENTS_VALIDATE(arg_username VARCHAR(100), arg_place_id INT)
    RETURNS TABLE
            (
                ID INT
            )
    LANGUAGE plpgsql
AS
$$
DECLARE
    user_id INT;
BEGIN
    SELECT ID INTO user_id FROM Users WHERE Username = arg_username;
    RETURN QUERY
        SELECT ID
        FROM VISITS
        WHERE UserID = user_id
          AND PlaceID = arg_place_id;
END
$$;

CREATE OR REPLACE FUNCTION F_POST_COMMENTS_INSERT(arg_username VARCHAR(100), arg_place_id INT, arg_content VARCHAR(500))
    RETURNS TABLE
            (
                ID       INT,
                UserID   INT,
                PlaceID  INT,
                Content  VARCHAR(500),
                TimeStmp TIMESTAMP,
                Likes    INT
            )
    LANGUAGE plpgsql
AS
$$
DECLARE
    user_id INT;
BEGIN
    SELECT ID INTO user_id FROM Users WHERE Username = arg_username;
    RETURN QUERY
        INSERT INTO Comments (UserID, PlaceID, Content)
            VALUES (user_id, arg_place_id, arg_content)
            RETURNING ID, UserID, PlaceID, Content, TimeStmp, Likes;
END
$$;

---- 7.3. ADMIN API
CREATE OR REPLACE FUNCTION F_PUT_PLACES_UPDATE(arg_id INT, arg_name VARCHAR(100), arg_description VARCHAR(500),
                                               arg_location VARCHAR(255), arg_key VARCHAR(40))
    RETURNS TABLE
            (
                ID          INT,
                Name        VARCHAR(100),
                Description VARCHAR(500),
                Location    VARCHAR(255)
            )
    LANGUAGE plpgsql
AS
$$
BEGIN
    RETURN QUERY
        UPDATE Places
            SET Name = arg_name,
                Description = arg_description,
                Location = arg_location,
                Key = arg_key
            WHERE ID = arg_id
            RETURNING ID, Name, Description, Location;
END
$$;

CREATE OR REPLACE FUNCTION F_PUT_PLACES_INSERT(arg_name VARCHAR(100), arg_description VARCHAR(500),
                                               arg_location VARCHAR(255), arg_key VARCHAR(40))
    RETURNS TABLE
            (
                ID          INT,
                Name        VARCHAR(100),
                Description VARCHAR(500),
                Location    VARCHAR(255)
            )
    LANGUAGE plpgsql
AS
$$
BEGIN
    RETURN QUERY
        INSERT INTO Places (Name, Description, Location, Key)
            VALUES (arg_name, arg_description, arg_location, arg_key)
            RETURNING ID, Name, Description, Location;
END
$$;

CREATE OR REPLACE FUNCTION F_DELETE_PLACES(arg_id INT)
    RETURNS TABLE
            (
                ID          INT,
                Name        VARCHAR(100),
                Description VARCHAR(500),
                Location    VARCHAR(255)
            )
    LANGUAGE plpgsql
AS
$$
BEGIN
    RETURN QUERY
        DELETE FROM Places
            WHERE ID = arg_id
            RETURNING ID, Name, Description, Location;
END
$$;

CREATE OR REPLACE FUNCTION F_PUT_USERS_UPDATE(arg_id INT, arg_username VARCHAR(100), arg_login VARCHAR(100),
                                              arg_password VARCHAR(100), arg_admin BOOLEAN, arg_points INT)
    RETURNS TABLE
            (
                ID       INT,
                Username VARCHAR(100),
                Points   INT
            )
    LANGUAGE plpgsql
AS
$$
BEGIN
    RETURN QUERY
        UPDATE Users
            SET Username = arg_username,
                Login = arg_login,
                Password = arg_password,
                Admin = arg_admin,
                Points = arg_points
            WHERE ID = arg_id
            RETURNING ID, Username, Points;
END
$$;

CREATE OR REPLACE FUNCTION F_PUT_USERS_INSERT(arg_username VARCHAR(100), arg_login VARCHAR(100),
                                              arg_password VARCHAR(100), arg_admin BOOLEAN, arg_points INT)
    RETURNS TABLE
            (
                ID       INT,
                Username VARCHAR(100),
                Points   INT
            )
    LANGUAGE plpgsql
AS
$$
BEGIN
    RETURN QUERY
        INSERT INTO Users (Username, Login, Password, Admin, Points)
            VALUES (arg_username, arg_login, arg_password, arg_admin, arg_points)
            RETURNING ID, Username, Points;
END
$$;

CREATE OR REPLACE FUNCTION F_DELETE_USERS(arg_id INT)
    RETURNS TABLE
            (
                ID       INT,
                Username VARCHAR(100),
                Points   INT
            )
    LANGUAGE plpgsql
AS
$$
BEGIN
    RETURN QUERY
        DELETE FROM Users
            WHERE ID = arg_id
            RETURNING ID, Username, Points;
END
$$;

CREATE OR REPLACE FUNCTION F_PUT_VISITS_UPDATE(arg_id INT, arg_user_id INT, arg_place_id INT)
    RETURNS TABLE
            (
                ID       INT,
                UserID   INT,
                PlaceID  INT,
                TimeStmp TIMESTAMP
            )
    LANGUAGE plpgsql
AS
$$
BEGIN
    RETURN QUERY
        UPDATE Visits
            SET UserID = arg_user_id,
                PlaceID = arg_place_id
            WHERE ID = arg_id
            RETURNING ID, UserID, PlaceID, TimeStmp;
END
$$;

CREATE OR REPLACE FUNCTION F_PUT_VISITS_INSERT(arg_user_id INT, arg_place_id INT)
    RETURNS TABLE
            (
                ID       INT,
                UserID   INT,
                PlaceID  INT,
                TimeStmp TIMESTAMP
            )
    LANGUAGE plpgsql
AS
$$
BEGIN
    RETURN QUERY
        INSERT INTO Visits (UserID, PlaceID)
            VALUES (arg_user_id, arg_place_id)
            RETURNING ID, UserID, PlaceID, TimeStmp;
END
$$;

CREATE OR REPLACE FUNCTION F_DELETE_VISITS(arg_id INT)
    RETURNS TABLE
            (
                ID       INT,
                UserID   INT,
                PlaceID  INT,
                TimeStmp TIMESTAMP
            )
    LANGUAGE plpgsql
AS
$$
BEGIN
    RETURN QUERY
        DELETE FROM Visits
            WHERE ID = arg_id
            RETURNING ID, UserID, PlaceID, TimeStmp;
END
$$;

CREATE OR REPLACE FUNCTION F_PUT_COMMENTS_UPDATE(arg_id INT, arg_user_id INT, arg_place_id INT,
                                                 arg_content VARCHAR(500))
    RETURNS TABLE
            (
                ID       INT,
                UserID   INT,
                PlaceID  INT,
                Content  VARCHAR(500),
                TimeStmp TIMESTAMP,
                Likes    INT
            )
    LANGUAGE plpgsql
AS
$$
BEGIN
    RETURN QUERY
        UPDATE Comments
            SET UserID = arg_user_id,
                PlaceID = arg_place_id,
                Content = arg_content
            WHERE ID = arg_id
            RETURNING ID, UserID, PlaceID, Content, TimeStmp, Likes;
END
$$;

CREATE OR REPLACE FUNCTION F_PUT_COMMENTS_INSERT(arg_user_id INT, arg_place_id INT, arg_content VARCHAR(500))
    RETURNS TABLE
            (
                ID       INT,
                UserID   INT,
                PlaceID  INT,
                Content  VARCHAR(500),
                TimeStmp TIMESTAMP,
                Likes    INT
            )
    LANGUAGE plpgsql
AS
$$
BEGIN
    RETURN QUERY
        INSERT INTO Comments (UserID, PlaceID, Content)
            VALUES (arg_user_id, arg_place_id, arg_content)
            RETURNING ID, UserID, PlaceID, Content, TimeStmp, Likes;
END
$$;

CREATE OR REPLACE FUNCTION F_DELETE_COMMENTS(arg_id INT)
    RETURNS TABLE
            (
                ID       INT,
                UserID   INT,
                PlaceID  INT,
                Content  VARCHAR(500),
                TimeStmp TIMESTAMP,
                Likes    INT
            )
    LANGUAGE plpgsql
AS
$$
BEGIN
    RETURN QUERY
        DELETE FROM Comments
            WHERE ID = arg_id
            RETURNING ID, UserID, PlaceID, Content, TimeStmp, Likes;
END
$$;

---- 7.4. AUTH API
CREATE OR REPLACE FUNCTION F_AUTHORIZE(arg_login VARCHAR(100), arg_password VARCHAR(100))
    RETURNS TABLE
            (
                ID       INT,
                Username VARCHAR(100),
                Admin    BOOLEAN,
                Points   INT
            )
    LANGUAGE plpgsql
AS
$$
BEGIN
    RETURN QUERY
        SELECT ID,
               Username,
               Admin,
               Points
        FROM Users
        WHERE Login = arg_login
          AND Password = arg_password;
END
$$;
