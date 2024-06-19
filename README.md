# UNI_MOBIL_P

### ! Warning !
This should not be deployed in production because of security issues.

## Description
This is the complete social app that allows users to share places they've visited, post comments on them, explore other places and track the user ranking.

## Build and deploy
### 1. Setup database
- Install postgres
- Run `sql/MIGRATE_postgres_001.sql` as postgres once
- Run `sql/MIGRATE_mobil_001.sql` as Supervisor (password: Supervisor) once

### 2. Docker
- Install docker
```bash
# docker build -t uni_mobil_p .
# docker run -p 8080:8080 --expose 5432 uni_mobil_p
```

## Docs
- [Authentication scheme](https://datatracker.ietf.org/doc/html/rfc7617)
