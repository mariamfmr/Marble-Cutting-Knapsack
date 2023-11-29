CXX = g++
CXXFLAGS = -g -std=c++11 -O3 -Wall
LDFLAGS = -lm
TARGET = cutboardchrono

# List all input files in the tests folder
INPUT_FILES = $(wildcard tests/*.in)

# Create a list of corresponding output files
OUTPUT_FILES = $(patsubst %.in, %.out, $(INPUT_FILES))

# Default target
all: $(TARGET) run_tests

# Compile the main program
$(TARGET): cutboardchrono.cpp
	$(CXX) $(CXXFLAGS) $< -o $@ $(LDFLAGS)

# Rule to run the program on each input file
run_tests: $(OUTPUT_FILES)

# Rule to create output file for each input file
%.out: %.in $(TARGET)
	./$(TARGET) < $< > $@

# Clean up compiled files and generated output files
clean:
	rm -f $(TARGET) $(OUTPUT_FILES)
