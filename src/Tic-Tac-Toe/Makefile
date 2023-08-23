# Compiler settings
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic

# Directories
SRC_DIR = .
TEST_DIR = .
BUILD_DIR = ./build

# Main program settings
MAIN_SRC = $(wildcard $(SRC_DIR)/main.cpp $(TEST_DIR)/board.cpp $(TEST_DIR)/player.cpp)
MAIN_OBJ = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(MAIN_SRC))
MAIN_TARGET = $(BUILD_DIR)/main

# Unit test program settings
TEST_SRC = $(wildcard $(TEST_DIR)/unit_test.cpp $(TEST_DIR)/board.cpp $(TEST_DIR)/player.cpp)
TEST_OBJ = $(patsubst $(TEST_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(TEST_SRC))
TEST_TARGET = $(BUILD_DIR)/test

# Clean function
RM = rm -rf

.PHONY: all clean

all: $(MAIN_TARGET) $(TEST_TARGET)

$(MAIN_TARGET): $(MAIN_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(TEST_TARGET): $(TEST_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(TEST_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) $(BUILD_DIR)/*.o $(MAIN_TARGET) $(TEST_TARGET)