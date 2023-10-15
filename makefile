# Define the project name and sources
PROJECT_NAME = ChickIncubator
SOURCES = $(wildcard src/*.cpp)
OBJECTS = $(patsubst src/%.cpp,obj/%.o,$(SOURCES))

# Define compiler and flags
CXX = g++
CXXFLAGS = -std=c++17

# Find all header directories recursively
HEADER_DIRS := $(shell find . -type d -name includes)
OBJECT_DIRS := $(patsubst %includes, %obj,$(HEADER_DIRS))
INCLUDES := $(addprefix -I, $(HEADER_DIRS))

# Define class folders
CLASS_FOLDERS := $(wildcard */)
CLASS_TARGETS := $(patsubst %,%/$(%), $(CLASS_FOLDERS))
CLASS_OBJECTS := $(wildcard $(OBJECT_DIRS)/*.o)

# Main target
all: $(CLASS_TARGETS) $(PROJECT_NAME)

$(CLASS_FOLDERS):
	$(MAKE) -C $@

$(PROJECT_NAME): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $^ -o bin/$(PROJECT_NAME)

obj/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf bin/$(PROJECT_NAME) $(OBJECTS)
	for dir in $(CLASS_FOLDERS); do \
		$(MAKE) -C $$dir clean; \
	done

.PHONY: all clean