CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra

SRCS := $(wildcard src/*.cpp)
OBJS := ../../obj/GPIO.o
OBJS += ../../obj/Timer.o
OBJS += ../../obj/Log.o
OBJS += ../../obj/RotaryEncoder.o
TARGET := bin/RotaryTest

INCLUDES := $(addprefix -I, $(wildcard ../../Timer/includes))
INCLUDES += $(addprefix -I, $(wildcard ../../Log/includes))
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
	$(MAKE) -C ../../Timer
	$(MAKE) -C ../../GPIO
	$(MAKE) -C ../../RotaryEncoder

clean:
	rm -f $(TARGET) $(OBJS) $(LOCAL_OBJS)

.PHONY: all clean