CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wconversion -Wextra -pthread

SRCS := $(wildcard src/*.cpp)
OBJS := $(patsubst src/%.cpp,../obj/%.o,$(SRCS))
TARGET := EggIncubator

INCLUDES := $(addprefix -I, $(wildcard includes))
INCLUDES += $(addprefix -I, $(wildcard ../Timer/includes))
INCLUDES += $(addprefix -I, $(wildcard ../PWM/includes))

all: $(OBJS)

$(OBJS): ../obj/%.o : src/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)

.PHONY: all clean