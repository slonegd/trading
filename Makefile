all: clean build run

clean:
	-rm -fR ./build

build:
	mkdir build
	g++ ./src/main.cpp ./src/neuralNet.cpp ./src/neuron.cpp ./src/trainingSet.cpp -std=c++17 -Wall -I. -g -o ./build/a.out

run:
	./build/a.out

fill:
	g++ fill.cpp -std=c++17 -Wall -I. -g
	make run

history:
	curl-config --cflags
	curl-config --libs
	g++ ./historyData/xml.cpp -std=c++17 -Wall -I. -g -lcurl -o ./historyData/history
	./historyData/history


