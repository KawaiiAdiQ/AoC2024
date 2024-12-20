# compiler and flags
CXX = g++
CXXFLAGS = -Wall -Werror -Wextra -g -O2

# Directories
BUILD_DIR = build
INPUT_DIR = in

# Source files
SRC_A = a.cpp
SRC_B = b.cpp

# executables
EXE_A = $(BUILD_DIR)/a
EXE_B = $(BUILD_DIR)/b

# Input files
IN_A = $(INPUT_DIR)/a.txt
IN_B = $(INPUT_DIR)/b.txt

# Targets
all: $(EXE_A) $(EXE_B)

$(EXE_A): $(SRC_A)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(SRC_A) -o $(EXE_A)

$(EXE_B): $(SRC_B)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(SRC_B) -o $(EXE_B)

a: $(EXE_A)
	$(EXE_A) < $(IN_A)

b: $(EXE_B)
	$(EXE_B) < $(IN_B)

clean:
	rm -rf $(BUILD_DIR)/*

.PHONY: all clean