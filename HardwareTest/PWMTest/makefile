CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra

SRCS := $(wildcard src/*.cpp)
# MOTOR_OBJ := ../../obj/Motor.o
# TIMER_OBJ := ../../obj/Timer.o
# OBJS := $(MOTOR_OBJ) $(TIMER_OBJ)
TARGET := bin/PWMTest

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(SRCS) $^ -o $(TARGET) $(LIBS)

clean:
	rm -f $(TARGET) $(OBJS) $(LOCAL_OBJS)

.PHONY: all clean