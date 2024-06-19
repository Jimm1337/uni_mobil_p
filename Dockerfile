FROM ubuntu:24.04
USER root

# setup packages
RUN apt-get update && apt-get upgrade -y
RUN apt-get install -y gcc ninja-build cmake npm nodejs node-vue postgresql libpq-dev curl wget git
RUN curl -fsSL https://deb.nodesource.com/setup_20.x | bash -
RUN apt-get install -y nodejs

# copy files
COPY . files

# build backend
WORKDIR /files
RUN cmake . -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_MAKE_PROGRAM=ninja
RUN ninja

# build frontend
WORKDIR /files/front
RUN npm install
RUN npm i vue@3.2.26

# run backend in background
WORKDIR /files
RUN ./uni_mobil_p-exe &

# run frontend
WORKDIR /files/front
ENTRYPOINT ["npm", "run", "serve"]
