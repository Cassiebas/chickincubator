CXX := g++
CC := gcc
CXXFLAGS := -std=c++17 -Wall -Wconversion -Wextra
CFLAGS := -Wall -Wconversion -Wextra

# Include both .cpp and .c files
CPP_SRCS := $(wildcard src/*.cpp)
C_SRCS := $(wildcard src/*.c)

CPP_OBJS := $(patsubst src/%.cpp,../obj/%.o,$(CPP_SRCS))
C_OBJS := $(patsubst src/%.c,../obj/%.o,$(C_SRCS))

TARGET := ChickenIncubator
INCLUDES := $(addprefix -I, $(wildcard includes))

all: $(CPP_OBJS) $(C_OBJS)

$(CPP_OBJS): ../obj/%.o : src/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(C_OBJS): ../obj/%.o : src/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(CPP_OBJS) $(C_OBJS)

.PHONY: all clean
