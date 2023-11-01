CXX := g++
CXXFLAGS := -std=c++17 -Wall

SRCS := $(wildcard src/*.cpp)
HEATING_ELEMENT_OBJ := ../../obj/HeatingElement.o
THERMISTOR_OBJ := ../../obj/Thermistor.o
LOCAL_OBJS := $(patsubst src/%.cpp,../../obj/%.o,$(SRCS))
OBJS := $(HEATING_ELEMENT_OBJ) $(THERMISTOR_OBJ) $(LOCAL_OBJS)
TARGET := bin/HeatingTest

INCLUDES := $(addprefix -I, $(wildcard includes))
INCLUDES += $(addprefix -I, $(wildcard ../../HeatingElement/includes))
INCLUDES += $(addprefix -I, $(wildcard ../../Thermistor/includes))
LIBS := $()

all: modules $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $^ -o $@ $(LIBS)

$(LOCAL_OBJS): ../../obj/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

modules:
	$(MAKE) -C ../../HeatingElement
	$(MAKE) -C ../../Thermistor

clean:
	rm -f $(TARGET) ../../obj/HeatingElement.o ../../obj/Thermistor.o $(LOCAL_OBJS)

.PHONY: all clean