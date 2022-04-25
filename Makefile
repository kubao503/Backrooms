CXX = g++
# -fsanitize=undefined	- clang needed ?
CXX_FLAGS = -g -Wall -Wextra -pedantic -Werror -std=c++2a

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
	$(CXX) $(CXX_FLAGS) $(OBJS) -o $(BIN)/$(EXECUTABLE) -L$(LIB) $(LIBRARIES)

compile: $(OBJS)

$(BIN)/%.o: $(SRC)/%.cpp $(HEADERS)
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) -c $< -o $@

clean:
	rm -r $(BIN)/*