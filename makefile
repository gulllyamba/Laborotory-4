CXX = g++

CXXFLAGS = -Wall -Wextra -std=c++23

SRC_DIR = src
UI_DIR = $(SRC_DIR)/UI
TEST_DIR = $(SRC_DIR)/tests
SPEED_DIR = $(SRC_DIR)/SpeedTest

INC = $(SRC_DIR)/main.cpp
OBJ = $(INC:.cpp=.o)
TARGET = main

UI_INC = $(UI_DIR)/UI.cpp
UI_OBJ = $(UI_INC:.cpp=.o)
UI_TARGET = ui

TEST_INC = $(TEST_DIR)/test.cpp
TEST_OBJ = $(TEST_INC:.cpp=.o)
TEST_TARGET = test

SPEDD_INC = $(SPEED_DIR)/speed.cpp
SPEED_OBJ = $(SPEDD_INC:.cpp=.o)
SPEED_TARGET = speed

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $@

$(UI_TARGET): $(UI_OBJ)
	$(CXX) $(UI_OBJ) -o $@

$(TEST_TARGET): $(TEST_OBJ)
	$(CXX) $(TEST_OBJ) -o $@

$(SPEED_TARGET): $(SPEED_OBJ)
	$(CXX) $(SPEED_OBJ) -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f src/UI/*.o
	rm -f src/tests/*.o
	rm -f src/SpeedTest/*.o
	rm -f src/*.o
	rm -f main
	rm -f ui
	rm -f test
	rm -f speed