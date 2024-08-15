# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -Wextra -Wpedantic -std=c++11

# SFML flags
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system
SFML_INCLUDE = /path/to/sfml/include
SFML_LIBDIR = /path/to/sfml/lib

# Target executables
TARGET = tree_demo
TEST_TARGET = test

# Source files
SRCS = Demo.cpp
TEST_SRCS = test.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)
TEST_OBJS = $(TEST_SRCS:.cpp=.o)

# Default target
all: $(TARGET)

# Build the main executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) -L$(SFML_LIBDIR) $(SFML_LIBS)

# Build the test executable
$(TEST_TARGET): $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) $(TEST_OBJS) -L$(SFML_LIBDIR) $(SFML_LIBS)

# Compile .cpp files to .o files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -I$(SFML_INCLUDE) -c $< -o $@

# Clean up build files
clean:
	rm -f $(TARGET) $(TEST_TARGET) $(OBJS) $(TEST_OBJS)

# Run the demo
run: $(TARGET)
	./$(TARGET)


