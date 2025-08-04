# Author: mardonet
# Date: 2025-08-03

# Makefile for the flying-toasters project

# Compiler and flags
CXX := g++
CXXFLAGS := -Wall -g

# Libraries
LDLIBS := -lglut -lGL -lGLU

# Target executable
TARGET := flying-toasters

# Source files
SRCS := main.cpp

# Object files
OBJS := $(SRCS:.cpp=.o)

# Default target
all: $(TARGET)

# Link the program
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LDLIBS)

# Compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET)
