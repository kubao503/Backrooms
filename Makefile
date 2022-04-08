CXX = g++

all: link compile

link: main.o camera.o object.o
	$(CXX) main.o camera.o object.o -o main -L src/lib -l sfml-graphics -l sfml-window -l sfml-system -l box2d

compile: main.o camera.o object.o

main.o: main.cpp camera.h object.h
	$(CXX) -I src/include -c main.cpp

camera.o: camera.cpp camera.h object.h
	$(CXX) -I src/include -c camera.cpp

object.o: object.cpp object.h camera.h
	$(CXX) -I src/include -c object.cpp

clean:
	rm -r *.o main.exe