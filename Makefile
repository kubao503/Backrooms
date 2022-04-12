CXX = g++
# -fsanitize=undefined	- clang needed ?
FLAGS = -Wall -Wextra -pedantic -Werror -std=c++2a

all: link compile

link: myWorld.o camera.o object.o player.o userio.o shapes.o main.o
	$(CXX) $(FLAGS) myWorld.o camera.o object.o player.o userio.o shapes.o main.o -o main -L src/lib -l sfml-graphics -l sfml-window -l sfml-system -l box2d

compile: main.o camera.o object.o player.o userio.o shapes.o myWorld.o

main.o: main.cpp camera.h object.h player.h userio.h myWorld.h
	$(CXX) $(FLAGS) -I src/include -c main.cpp

camera.o: camera.cpp camera.h userio.h shapes.h myWorld.h constants.h
	$(CXX) $(FLAGS) -I src/include -c camera.cpp

object.o: object.cpp object.h shapes.h myWorld.h myBody.h
	$(CXX) $(FLAGS) -I src/include -c object.cpp

player.o: player.cpp player.h object.h userio.h myWorld.h
	$(CXX) $(FLAGS) -I src/include -c player.cpp

userio.o: userio.cpp userio.h object.h shapes.h
	$(CXX) $(FLAGS) -I src/include -c userio.cpp

shapes.o: shapes.cpp shapes.h
	$(CXX) $(FLAGS) -I src/include -c shapes.cpp

myWorld.o: myWorld.cpp myWorld.h myBody.h
	$(CXX) $(FLAGS) -I src/include -c myWorld.cpp

clean:
	rm -r *.o main.exe