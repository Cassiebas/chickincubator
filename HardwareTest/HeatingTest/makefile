CXX := g++
CXXFLAGS := -std=c++17 -Wall

SRCS := $(wildcard src/*.cpp)
HEATING_ELEMENT_OBJ := ../../obj/HeatingElement.o
THERMISTOR_OBJ := ../../obj/Thermistor.o
TIMER_OBJ := ../../obj/Timer.o
LOCAL_OBJS := $(patsubst src/%.cpp,../../obj/%.o,$(SRCS))
OBJS := $(HEATING_ELEMENT_OBJ) $(THERMISTOR_OBJ) $(TIMER_OBJ) $(LOCAL_OBJS)
TARGET := bin/HeatingTest

INCLUDES := $(addprefix -I, $(wildcard includes))
INCLUDES += $(addprefix -I, $(wildcard ../../HeatingElement/includes))
INCLUDES += $(addprefix -I, $(wildcard ../../Thermistor/includes))
INCLUDES += $(addprefix -I, $(wildcard ../../Timer/includes))

LIBS := $()

all: modules $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $^ -o $@ $(LIBS)

$(LOCAL_OBJS): ../../obj/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

modules:
	$(MAKE) -C ../../HeatingElement
	$(MAKE) -C ../../Thermistor
	$(MAKE) -C ../../Timer

clean:
	rm -f $(TARGET) ../../obj/HeatingElement.o ../../obj/Thermistor.o ../../obj/Timer.o $(LOCAL_OBJS)

.PHONY: all clean