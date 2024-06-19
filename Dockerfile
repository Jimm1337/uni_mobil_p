FROM ubuntu:24.04

# setup packages
USER root

RUN apt-get update && apt-get upgrade -y
RUN apt-get install -y curl wget git
RUN curl -fsSL https://deb.nodesource.com/setup_20.x | bash -
RUN apt-get install -y nodejs
RUN apt-get install -y gcc ninja-build cmake npm node-vue postgresql libpq-dev

# build backend
RUN mkdir build
WORKDIR /build

RUN cmake .. -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_MAKE_PROGRAM=ninja
RUN ninja

# setup database
WORKDIR /

USER postgres
RUN psql -c "ALTER USER postgres WITH PASSWORD 'postgres';"

USER root
RUN export PGPASSWORD=postgres
RUN psql -h localhost -U postgres -a -q -f sql/MIGRATE_postgres_001.sql
RUN export PGPASSWORD=Supervisor
RUN psql -h localhost -d mobil_db -U Supervisor -a -q -f sql/MIGRATE_mobil_001.sql

# build frontend
WORKDIR /front
RUN npm install
RUN npm i vue@3.2.26

# run backend in background
WORKDIR /build
RUN ./uni_mobil_p-exe &

# run frontend
WORKDIR /front
ENTRYPOINT ["npm", "run", "serve"]
