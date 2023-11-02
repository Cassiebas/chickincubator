CXX := g++
CXXFLAGS := -std=c++17 -Wall

SRCS := $(wildcard src/*.cpp)
HEATING_ELEMENT_OBJ := ../../obj/HeatingElement.o
THERMISTOR_OBJ := ../../obj/Thermistor.o
TIMER_OBJ := ../../obj/Timer.o
HARRY_PLOTTER := ../../obj/HarryPlotter.o
LOCAL_OBJS := $(patsubst src/%.cpp,../../obj/%.o,$(SRCS))
OBJS := $(HEATING_ELEMENT_OBJ) $(THERMISTOR_OBJ) $(TIMER_OBJ) $(HARRY_PLOTTER) $(LOCAL_OBJS)
TARGET := bin/HeatingTest

INCLUDES := $(addprefix -I, $(wildcard includes))
INCLUDES += $(addprefix -I, $(wildcard ../../HeatingElement/includes))
INCLUDES += $(addprefix -I, $(wildcard ../../Thermistor/includes))
INCLUDES += $(addprefix -I, $(wildcard ../../Timer/includes))
INCLUDES += $(addprefix -I, $(wildcard ../../HarryPlotter/includes))

LIBS := $(addprefix -l, boost_iostreams)
LIBS += $(addprefix -l, boost_system)
LIBS += $(addprefix -l, boost_filesystem)

all: modules $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $^ -o $@ $(LIBS)

$(LOCAL_OBJS): ../../obj/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

modules:
	$(MAKE) -C ../../HeatingElement
	$(MAKE) -C ../../Thermistor
	$(MAKE) -C ../../Timer
	$(MAKE) -C ../../HarryPlotter

clean:
	rm -f $(TARGET) ../../obj/HeatingElement.o ../../obj/Thermistor.o ../../obj/Timer.o $(LOCAL_OBJS)

.PHONY: all clean