CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra

SRCS := $(wildcard src/*.cpp)
DISPLAY := ../../obj/Display.o
OBJS := $(DISPLAY)
TARGET := bin/DisplayTest

INCLUDES := $(addprefix -I, $(wildcard includes))
INCLUDES += $(addprefix -I, $(wildcard ../../Display/includes))

# LIBS := $(addprefix -l, boost_iostreams)
# LIBS += $(addprefix -l, boost_system)
# LIBS += $(addprefix -l, boost_filesystem)

all: modules $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(SRCS) $^ -o $(TARGET) $(LIBS)

modules:
	$(MAKE) -C ../../Display

clean:
	rm -f $(TARGET) $(OBJS)

.PHONY: all clean