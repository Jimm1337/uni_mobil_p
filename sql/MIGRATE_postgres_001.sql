CREATE EXTENSION IF NOT EXISTS dblink;

-- 1. ROLES

DO
$do$
    BEGIN
        IF EXISTS (SELECT
                   FROM pg_catalog.pg_roles
                   WHERE rolname = 'Supervisor') THEN

            RAISE NOTICE 'Role "Supervisor" already exists. Skipping.';
        ELSE
            BEGIN
                -- nested block
                CREATE ROLE "Supervisor"
                    WITH LOGIN PASSWORD 'Supervisor'
                    SUPERUSER
                    INHERIT
                    NOCREATEDB
                    NOCREATEROLE
                    NOREPLICATION;
            EXCEPTION
                WHEN duplicate_object THEN
                    RAISE NOTICE 'Role "Supervisor" was just created by a concurrent transaction. Skipping.';
            END;
        END IF;
    END
$do$;

-- 2. DATABASE

DO
$do$
BEGIN
   IF EXISTS (SELECT FROM pg_database WHERE datname = 'mobil_db') THEN
      RAISE NOTICE 'Database "mobil_db" already exists, skipping';
   ELSE
      PERFORM dblink_exec('dbname=' || current_database() || ' user=postgres password=postgres'
                        , 'CREATE DATABASE mobil_db
                  WITH
                  OWNER = "Supervisor"
                  ENCODING = ''UTF8''
                  LC_COLLATE = ''Polish_Poland.1250''
                  LC_CTYPE = ''Polish_Poland.1250''
                  TABLESPACE = pg_default
                  CONNECTION LIMIT = -1');
   END IF;
END
$do$;

-- 3. PRIVILEGES

GRANT ALL PRIVILEGES ON DATABASE mobil_db TO "Supervisor";
