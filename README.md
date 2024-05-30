# UNI_MOBIL_P

### ! Warning !
This should not be deployed in production because of security issues.

## Description
This is the complete back-end for a social app that allows users to share places they've visited, post comments on them, explore other places and track the user ranking.

## Build and deploy
### 0. Requirements
- CMake
- Ninja
- GCC/Clang/MSVC
- PostgreSQL

### 1. Setup database
- Install postgres
- Run `sql/MIGRATE_postgres_001.sql` as postgres
- Run `sql/MIGRATE_mobil_001.sql` as Supervisor (password: Supervisor)

### 2. Build
```bash
$ mkdir build && cd build
$ cmake .. -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_MAKE_PROGRAM=ninja
$ ninja
```

### 3. Run
```bash
$ ./src/uni_mobil_p
```

### 4. Checkout the docs
- [API Documentation - local (run the server first)](http://localhost:8000/swagger/ui)
- [Authentication scheme](https://datatracker.ietf.org/doc/html/rfc7617)
