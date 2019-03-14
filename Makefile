image:
	docker build -t rapid-random-tree .

docker-build:
	docker run -v $(PWD):/usr/src/app rapid-random-tree:latest make build

build:
	g++ src/main.cpp \
		-std=c++11 \
		-pthread \
		-lSDL2 \
		-o rapid-random-tree
