CXX = g++
# -fsanitize=undefined	- clang needed ?
CXX_FLAGS = -g -Wall -Wextra -pedantic -Werror -std=c++2a

BIN = bin
SRC = src
INCLUDE = include
LIB = lib
LIBRARIES = -lbox2d -lsfml-graphics -lsfml-window -lsfml-system

DIR = mains

CATCH = catch

MAIN = main
TEST = tests

MAIN_OBJ = $(BIN)/$(DIR)/$(MAIN).o
TEST_OBJ = $(BIN)/$(DIR)/$(TEST).o
CATCH_DIR = $(TEST)/catch2

SRCS = $(wildcard $(SRC)/*.cpp)							# source files in src/
OBJS = $(patsubst $(SRC)/%.cpp,$(BIN)/%.o,$(SRCS))		# obj files in bin/
HEADERS = $(INCLUDE)/*									# header files in include/

all: compile link tests

link: $(OBJS) $(MAIN_OBJ)
	$(CXX) $(CXX_FLAGS) $(OBJS) $(MAIN_OBJ) -o $(BIN)/$(MAIN) -L$(LIB) $(LIBRARIES)

tests:	$(OBJS) $(TEST_OBJ)
	$(CXX) $(CXX_FLAGS) $(OBJS) $(TEST_OBJ) -o $(BIN)/$(TEST) -L$(LIB) $(LIBRARIES)

compile: $(OBJS) $(MAIN_OBJ) $(TEST_OBJ)

$(BIN)/%.o: $(SRC)/%.cpp $(HEADERS)
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) -c $< -o $@							# compiles all .o files from .cpp files in src/
	
$(MAIN_OBJ): $(MAIN)/$(MAIN).cpp $(HEADERS) $(BIN)/$(DIR)
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) -c $< -o $@

$(TEST_OBJ): $(TEST)/$(TEST).cpp $(HEADERS) $(CATCH_DIR)/$(CATCH).hpp $(BIN)/$(DIR)
	echo "Test object files."
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) -I$(CATCH_DIR) -c $< -o $@

$(BIN)/$(DIR):
	mkdir $(BIN)/$(DIR)

clean:
	rm -r $(BIN)/*