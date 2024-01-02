CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -pthread

SRCS := $(wildcard src/*.cpp)
MOTOR_OBJ := ../../obj/Motor.o
TIMER_OBJ := ../../obj/Timer.o
OBJS := $(MOTOR_OBJ) $(TIMER_OBJ)
TARGET := bin/MotorTest

INCLUDES := $(addprefix -I, $(wildcard ../../Motor/includes))
INCLUDES += $(addprefix -I, $(wildcard ../../Timer/includes))

all: modules $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(SRCS) $^ -o $(TARGET) $(LIBS)

modules:
	$(MAKE) -C ../../Motor
	$(MAKE) -C ../../Timer

clean:
	rm -f $(TARGET) $(OBJS) $(LOCAL_OBJS)

.PHONY: all clean