CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra

SRCS := $(wildcard src/*.cpp)
LOG_OBJ := ../../obj/Log.o
GPIO_OBJ := ../../obj/GPIO.o
ROT_OBJ := ../../obj/RotaryEncoder.o
OBJS := $(LOG_OBJ) $(GPIO_OBJ) $(ROT_OBJ)
TARGET := bin/RotaryTest

INCLUDES := $(addprefix -I, $(wildcard ../../Log/includes))
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
	$(MAKE) -C ../../GPIO
	$(MAKE) -C ../../RotaryEncoder

clean:
	rm -f $(TARGET) $(OBJS) $(LOCAL_OBJS)

.PHONY: all clean