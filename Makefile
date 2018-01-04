all: clean build run

clean:
	-rm -fR ./a.out

build:

	g++ main.cpp net.cpp neuron.cpp trainingSet.cpp -std=c++17 -Wall -I. -g

run:
	./a.out

fill:
	g++ fill.cpp -std=c++17 -Wall -I. -g
	make run

history:
	curl-config --cflags
	curl-config --libs
	g++ ./historyData/xml.cpp -std=c++17 -Wall -I. -g -lcurl -o ./historyData/history
	./historyData/history


