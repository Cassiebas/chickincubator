CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wconversion -Wextra

SRCS := $(wildcard src/*.cpp)
OBJS := $(patsubst src/%.cpp,../obj/%.o,$(SRCS))
TARGET := EggIncubator

INCLUDES := $(addprefix -I, $(wildcard includes))
INCLUDES += $(addprefix -I, $(wildcard ../GPIO/includes))

all: $(OBJS)

$(OBJS): ../obj/%.o : src/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)

.PHONY: all clean