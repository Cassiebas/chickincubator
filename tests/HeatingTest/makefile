CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra

SRCS := $(wildcard src/*.cpp)
PWM_OBJ := ../../obj/PWM.o
HEATING_ELEMENT_OBJ := ../../obj/HeatingElement.o
THERMISTOR_OBJ := ../../obj/Thermistor.o
TIMER_OBJ := ../../obj/Timer.o
HARRY_PLOTTER := ../../obj/HarryPlotter.o
Display := ../../obj/Display.o
PWM := ../../obj/PWM.o
GPIO := ../../obj/GPIO.o
OBJS := $(HEATING_ELEMENT_OBJ) $(THERMISTOR_OBJ) $(TIMER_OBJ) $(PWM) $(HARRY_PLOTTER) $(GPIO)
TARGET := bin/HeatingTest

INCLUDES := $(addprefix -I, $(wildcard includes))
INCLUDES += $(addprefix -I, $(wildcard ../../PWM/includes))
INCLUDES += $(addprefix -I, $(wildcard ../../HeatingElement/includes))
INCLUDES += $(addprefix -I, $(wildcard ../../Thermistor/includes))
INCLUDES += $(addprefix -I, $(wildcard ../../Timer/includes))
INCLUDES += $(addprefix -I, $(wildcard ../../HarryPlotter/includes))
INCLUDES += $(addprefix -I, $(wildcard ../../GPIO/includes))

LIBS := $(addprefix -l, boost_iostreams)
LIBS += $(addprefix -l, boost_system)
LIBS += $(addprefix -l, boost_filesystem)

all: modules $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(SRCS) $^ -o $(TARGET) $(LIBS)

modules:
	$(MAKE) -C ../../Timer
	$(MAKE) -C ../../PWM
	$(MAKE) -C ../../HeatingElement
	$(MAKE) -C ../../Thermistor
	$(MAKE) -C ../../HarryPlotter
	$(MAKE) -C ../../GPIO

clean:
	rm -f $(TARGET) $(OBJS)

.PHONY: all clean