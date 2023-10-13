CXX := g++
CXXFLAGS := -std=c++17 -Wall

CHICKINC_SRCS := $(wildcard ChickIncubator/src/*.cpp)
CHICKINC_OBJS := $(CHICKINC_SRCS:.cpp=.o)

MAIN_SRCS := $(wildcard src/*.cpp)
MAIN_OBJS := $(MAIN_SRCS:.cpp=.o)

TARGET := bin/ChickenIncubator

INCLUDES := $(wildcard ChickIncubator/includes/*.hpp)

all: ChickIncubator $(TARGET)

$(TARGET): $(MAIN_OBJS) $(CHICKINC_OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(MAIN_OBJS) $(CHICKINC_OBJS)

ChickIncubator:
	make -C ChickIncubator all

clean:
	rm -f $(TARGET) $(MAIN_OBJS) $(CHICKINC_OBJS)

.PHONY: all clean ChickIncubator