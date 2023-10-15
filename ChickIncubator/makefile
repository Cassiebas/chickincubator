# Define the class name and sources
CLASS_NAME = ChickIncubator
SOURCES = $(wildcard src/*.cpp)
OBJECTS = $(patsubst src/%.cpp,../obj/%.o,$(SOURCES))

# Define compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -I./includes

# Main target
all: $(CLASS_NAME)

obj/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm $(OBJECTS)

.PHONY: all clean