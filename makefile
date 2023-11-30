CXX = g++
CXXFLAGS = -g -std=c++11 -O3 -Wall
LDFLAGS = -lm
TARGET = cutboardchrono

# List all input files in the tests folder
INPUT_FILES = $(wildcard tests/*.in)

# Create a list of corresponding output files
OUTPUT_FILES = $(patsubst %.in, %.out, $(INPUT_FILES))

# Default target
all: $(TARGET) $(OUTPUT_FILES)

# Compile the main program
$(TARGET): cutboardchrono.cpp
	$(CXX) $(CXXFLAGS) $< -o $@ $(LDFLAGS)

# Rule to run the program on each input file and redirect the output to .out files
%.out: %.in $(TARGET)
	./$(TARGET) < $< > $@ 2>&1

# Clean up compiled files and generated output files
clean:
	rm -f $(TARGET) $(OUTPUT_FILES)
