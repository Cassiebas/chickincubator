CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra

SRCS := $(wildcard src/*.cpp)
OBJS := ../../obj/Log.o
OBJS += ../../obj/SSD1306.o
OBJS += ../../obj/Display.o
OBJS += ../../obj/BootScreen.o
OBJS += ../../obj/SettingsScreen.o
OBJS += ../../obj/HomeScreen.o
OBJS += ../../obj/UI.o
OBJS += ../../obj/GPIO.o
OBJS += ../../obj/RotaryEncoder.o
TARGET := bin/UITest

INCLUDES := $(addprefix -I, $(wildcard ../../Log/includes))
INCLUDES += $(addprefix -I, $(wildcard ../../Display/includes))
INCLUDES += $(addprefix -I, $(wildcard ../../UI/includes))
INCLUDES += $(addprefix -I, $(wildcard ../../GPIO/includes))
INCLUDES += $(addprefix -I, $(wildcard ../../RotaryEncoder/includes))

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
	$(MAKE) -C ../../Log
	$(MAKE) -C ../../Display
	$(MAKE) -C ../../UI
	$(MAKE) -C ../../GPIO
	$(MAKE) -C ../../RotaryEncoder

clean:
	rm -f $(TARGET) $(OBJS) $(LOCAL_OBJS)

.PHONY: all clean