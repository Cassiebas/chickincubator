CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra

SRCS := $(wildcard src/*.cpp)
DISPLAY := ../../obj/Display.o
OBJS := $(DISPLAY)
TARGET := bin/DisplayTest

INCLUDES := $(addprefix -I, $(wildcard includes))
INCLUDES += $(addprefix -I, $(wildcard ../../Display/includes))

all: modules $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(SRCS) $^ -o $(TARGET) $(LIBS)

modules:
	$(MAKE) -C ../../Display

clean:
	rm -f $(TARGET) $(OBJS)

.PHONY: all clean