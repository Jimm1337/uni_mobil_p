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
    ID INT NOT NULL PRIMARY KEY DEFAULT nextval('genid'),
    Name VARCHAR(100) NOT NULL UNIQUE,
    Description VARCHAR(500),
    Location VARCHAR(255) NOT NULL,
    Key VARCHAR(40) NOT NULL UNIQUE
);

CREATE TABLE IF NOT EXISTS Users
(
    ID INT NOT NULL PRIMARY KEY DEFAULT nextval('genid'),
    Username VARCHAR(100) NOT NULL UNIQUE,
    Login VARCHAR(100) NOT NULL UNIQUE,
    Password VARCHAR(100) NOT NULL,
    Admin BOOLEAN NOT NULL DEFAULT FALSE,
    Points INT NOT NULL DEFAULT 0
);

CREATE TABLE IF NOT EXISTS Comments
(
    ID INT NOT NULL PRIMARY KEY DEFAULT nextval('genid'),
    UserID INT NOT NULL REFERENCES Users(ID),
    PlaceID INT NOT NULL REFERENCES Places(ID),
    Content VARCHAR(500) NOT NULL,
    Time TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,
    Likes INT NOT NULL DEFAULT 0
);

CREATE TABLE IF NOT EXISTS Visits
(
    ID INT NOT NULL PRIMARY KEY DEFAULT nextval('genid'),
    UserID INT NOT NULL REFERENCES Users(ID),
    PlaceID INT NOT NULL REFERENCES Places(ID),
    Time TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP
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
VALUES
       ('Admin 0', 'admin0', 'admin', TRUE),
       ('Example User 0', 'example-user-0', 'example-password-0', FALSE),
       ('Example User 1', 'example-user-1', 'example-password-1', FALSE),
       ('Example User 2', 'example-user-2', 'example-password-2', FALSE),
       ('Example User 3', 'example-user-3', 'example-password-3', FALSE),
       ('Example User 4', 'example-user-4', 'example-password-4', FALSE)
ON CONFLICT (ID) DO NOTHING;

INSERT INTO Comments (UserID, PlaceID, Content)
VALUES
       (6, 0, 'Example comment 0'),
       (7, 0, 'Example comment 1'),
       (8, 0, 'Example comment 2'),
       (9, 0, 'Example comment 3'),
       (10, 0, 'Example comment 4')
ON CONFLICT (ID) DO NOTHING;

INSERT INTO Visits (UserID, PlaceID)
VALUES
       (6, 1),
       (7, 1),
       (8, 1),
       (9, 1),
       (10, 1)
ON CONFLICT (ID) DO NOTHING;

-- 4. VIEW

CREATE MATERIALIZED VIEW IF NOT EXISTS Ranking AS
SELECT
    ID AS UserID,
    Username,
    Points
FROM Users
ORDER BY Points DESC;

CREATE MATERIALIZED VIEW IF NOT EXISTS PlacesAlphabetically AS
SELECT
    ID AS PlaceID,
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
CREATE INDEX IF NOT EXISTS idx_btree_comments_time ON Comments USING BTREE (Time);
CREATE INDEX IF NOT EXISTS idx_btree_comments_likes ON Comments USING BTREE (Likes);

CREATE INDEX IF NOT EXISTS idx_hash_visits_user_id ON Visits USING HASH (UserID);
CREATE INDEX IF NOT EXISTS idx_hash_visits_place_id ON Visits USING HASH (PlaceID);
CREATE INDEX IF NOT EXISTS idx_btree_visits_time ON Visits USING BTREE (Time);

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

CREATE TRIGGER onUsersChange
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

CREATE TRIGGER onPlacesChange
    AFTER INSERT OR UPDATE OR DELETE
    ON Places
    FOR EACH STATEMENT
    EXECUTE FUNCTION internal_onPlacesChange();
