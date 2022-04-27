CXX = clang++
CXX_FLAGS = -I /usr/local/Cellar/sfml/2.5.1_1/include/ -I /usr/local/Cellar/box2d/2.4.1/include/ -fsanitize=undefined -g -Wall -Wextra -pedantic -Werror -std=c++2a

BIN = bin
SRC = src
INCLUDE = include
LIB = lib
LIBRARIES = -lbox2d -lsfml-graphics -lsfml-window -lsfml-system
EXECUTABLE = main

SRCS = $(wildcard $(SRC)/*.cpp)
OBJS = $(patsubst $(SRC)/%.cpp,$(BIN)/%.o,$(SRCS))
HEADERS = $(INCLUDE)/*

all: compile link

link: $(OBJS)
	$(CXX) $(CXX_FLAGS) $(OBJS) -o $(BIN)/$(EXECUTABLE) $(LIBRARIES)

compile: $(OBJS)

$(BIN)/%.o: $(SRC)/%.cpp $(HEADERS)
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) -c $< -o $@

clean:
	rm -r $(BIN)/*