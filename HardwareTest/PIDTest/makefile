CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra

SRCS := $(wildcard src/*.cpp)
ONOFFCONTROLLER_OBJ := ../../obj/PIDController.o
TIMER_OBJ := ../../obj/Timer.o
PWM_OBJ := ../../obj/PWM.o
HEATINGELEMENT_OBJ := ../../obj/HeatingElement.o
THERMISTOR_OBJ := ../../obj/Thermistor.o
PLOTTER_OBJ := ../../obj/HarryPlotter.o
HEATERCONTROLLER_OBJ := ../../obj/HeaterController.o
OBJS := $(ONOFFCONTROLLER_OBJ) $(TIMER_OBJ) $(PWM_OBJ) $(HEATINGELEMENT_OBJ) $(THERMISTOR_OBJ) $(PLOTTER_OBJ) $(HEATERCONTROLLER_OBJ)
TARGET := bin/PIDTest

INCLUDES := $(addprefix -I, $(wildcard ../../HeaterController/includes))
INCLUDES += $(addprefix -I, $(wildcard ../../PIDController/includes))
INCLUDES += $(addprefix -I, $(wildcard ../../PWM/includes))
INCLUDES += $(addprefix -I, $(wildcard ../../Timer/includes))
INCLUDES += $(addprefix -I, $(wildcard ../../HeatingElement/includes))
INCLUDES += $(addprefix -I, $(wildcard ../../HarryPlotter/includes))
INCLUDES += $(addprefix -I, $(wildcard ../../Thermistor/includes))

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
	$(MAKE) -C ../../HeaterController
	$(MAKE) -C ../../PIDController

clean:
	rm -f $(TARGET) $(OBJS) $(LOCAL_OBJS)

.PHONY: all clean