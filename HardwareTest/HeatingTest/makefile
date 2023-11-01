CXX := g++
CXXFLAGS := -std=c++17 -Wall

SRCS := $(wildcard src/*.cpp)
OBJS := $(patsubst src/%.cpp,../obj/%.o,$(SRCS))
TARGET := bin/HeatingTest

INCLUDES := $(addprefix -I, $(wildcard includes))
INCLUDES += $(addprefix -I, $(wildcard ../../HeatingElement/includes))
INCLUDES += $(addprefix -I, $(wildcard ../../Thermistor/includes))
LIBS := $()

all: modules $(TARGET)

$(TARGET):
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(SRCS) -o $(TARGET) $(LIBS)

modules:
	$(MAKE) -C ../../HeatingElement
	$(MAKE) -C ../../Thermistor

# $(OBJS): ../obj/%.o : src/%.cpp
# 	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(TARGET)

.PHONY: all clean