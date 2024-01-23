CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra

SRCS := $(wildcard src/*.cpp)
OBJS := ../../obj/OnOffController.o
OBJS += ../../obj/Log.o
OBJS += ../../obj/Timer.o
OBJS += ../../obj/PWM.o
OBJS += ../../obj/HeatingElement.o
OBJS += ../../obj/Thermistor.o
OBJS += ../../obj/HarryPlotter.o
OBJS += ../../obj/HeaterController.o
OBJS += ../../obj/GPIO.o
TARGET := bin/OnOffTest

INCLUDES := $(addprefix -I, $(wildcard ../../Log/includes))
INCLUDES += $(addprefix -I, $(wildcard ../../HeaterController/includes))
INCLUDES += $(addprefix -I, $(wildcard ../../OnOffController/includes))
INCLUDES += $(addprefix -I, $(wildcard ../../PWM/includes))
INCLUDES += $(addprefix -I, $(wildcard ../../Timer/includes))
INCLUDES += $(addprefix -I, $(wildcard ../../HeatingElement/includes))
INCLUDES += $(addprefix -I, $(wildcard ../../HarryPlotter/includes))
INCLUDES += $(addprefix -I, $(wildcard ../../Thermistor/includes))
INCLUDES += $(addprefix -I, $(wildcard ../../GPIO/includes))

LIBS := -DBOOST_LOG_DYN_LINK
LIBS += $(addprefix -l, boost_iostreams)
LIBS += $(addprefix -l, boost_system)
LIBS += $(addprefix -l, boost_thread)
LIBS += $(addprefix -l, boost_filesystem)
LIBS += $(addprefix -p, thread)
LIBS += $(addprefix -l, boost_log)
LIBS += $(addprefix -l, boost_log_setup)

all: modules $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(SRCS) $^ -o $(TARGET) $(LIBS)

modules:
	$(MAKE) -C ../../Timer
	$(MAKE) -C ../../Log
	$(MAKE) -C ../../PWM
	$(MAKE) -C ../../HeatingElement
	$(MAKE) -C ../../Thermistor
	$(MAKE) -C ../../HarryPlotter
	$(MAKE) -C ../../HeaterController
	$(MAKE) -C ../../OnOffController
	$(MAKE) -C ../../GPIO

clean:
	rm -f $(TARGET) $(OBJS) $(LOCAL_OBJS)

.PHONY: all clean