CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra

SRCS := $(wildcard src/*.cpp)
DISPLAY := ../../obj/Display.o
SSD1306 := ../../obj/SSD1306.o
OBJS := $(DISPLAY) $(SSD1306)
TARGET := bin/DisplayTest

INCLUDES := $(addprefix -I, $(wildcard ../../Display/includes))

all: modules $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(SRCS) $^ -o $(TARGET) $(LIBS)

modules:
	$(MAKE) -C ../../Display

clean:
	rm -f $(TARGET) $(OBJS)

.PHONY: all clean