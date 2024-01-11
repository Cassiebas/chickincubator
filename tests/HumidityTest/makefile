CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra

SRCS := $(wildcard src/*.cpp)
HUMIDITY_OBJ := ../../obj/Humidity.o
OBJS := $(HUMIDITY_OBJ)
TARGET := bin/HumidityTest

INCLUDES := $(addprefix -I, $(wildcard ../../HumiditySensor/includes))

all: modules $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(SRCS) $^ -o $(TARGET) $(LIBS)

modules:
	$(MAKE) -C ../../HumiditySensor

clean:
	rm -f $(TARGET) $(OBJS) $(LOCAL_OBJS)

.PHONY: all clean