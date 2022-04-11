CXX = g++

all: link compile

link: camera.o object.o player.o userio.o shapes.o main.o
	$(CXX) camera.o object.o player.o userio.o shapes.o main.o -o main -L src/lib -l sfml-graphics -l sfml-window -l sfml-system -l box2d

compile: main.o camera.o object.o player.o userio.o shapes.o

main.o: main.cpp camera.h object.h player.h userio.h
	$(CXX) -I src/include -c main.cpp

camera.o: camera.cpp camera.h userio.h shapes.h
	$(CXX) -I src/include -c camera.cpp

object.o: object.cpp object.h shapes.h
	$(CXX) -I src/include -c object.cpp

player.o: player.cpp player.h object.h userio.h
	$(CXX) -I src/include -c player.cpp

userio.o: userio.cpp userio.h object.h shapes.h
	$(CXX) -I src/include -c userio.cpp

shapes.o: shapes.cpp shapes.h
	$(CXX) -I src/include -c shapes.cpp

clean:
	rm -r *.o main.exe