CXX := g++
CXXFLAGS := -std=c++17 -Wall
TARGET := ../bin/HardwareTest

MAIN_SOURCE = $(wildcard src/*.cpp)
MAIN_OBJECT = $(patsubst src/%.cpp,obj/%.o,$(MAIN_SOURCE))

# Find all header directories recursively
HEADER_DIRS := $(shell find . -type d -name includes)
INCLUDES := $(addprefix -I, $(HEADER_DIRS))

all: subdirs $(TARGET)

# Simple for loop that only executes a make -C all command when a makefile is detected
subdirs:
	@for dir in */; do \
		if [ -f "$$dir/makefile" ]; then \
			$(MAKE) -C $$dir --no-print-directory; \
		fi \
	done

# To link all .o files with the binary we just use obj/* minus the main.o otherwise it will be doubly linked.
$(TARGET): $(MAIN_OBJECT)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(MAIN_OBJECT) $(filter-out $(MAIN_OBJECT), $(wildcard obj/*.o))

# To compile main.cpp to main.o
obj/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Clean
clean:
	rm -f $(TARGET) $(wildcard obj/*.o)

.PHONY: all clean ChickIncubator