FROM gcc:latest

RUN apt-get update && \
	apt-get install libsdl2-dev -y

COPY . /usr/src/app
WORKDIR /usr/src/app
