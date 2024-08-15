# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -Wextra -Wpedantic -std=c++11

# SFML flags
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system
SFML_INCLUDE = /path/to/sfml/include
SFML_LIBDIR = /path/to/sfml/lib

# Target executable
TARGET = tree_demo

# Source files
SRCS = Demo.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Default target
all: $(TARGET)

# Build the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) -L$(SFML_LIBDIR) $(SFML_LIBS)

# Compile .cpp files to .o files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -I$(SFML_INCLUDE) -c $< -o $@

# Clean up build files
clean:
	rm -f $(TARGET) $(OBJS)

# Run the demo
run: $(TARGET)
	./$(TARGET)
