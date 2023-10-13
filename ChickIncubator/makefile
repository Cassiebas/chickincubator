CXX := g++
CXXFLAGS := -std=c++17 -Wall

SRCS := $(wildcard src/*.cpp)
OBJS := $(SRCS:.cpp=.o)
TARGET := ChickenIncubator

INCLUDES := $(wildcard includes/*.hpp)

all: $(OBJS)

$(OBJS): $(SRCS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

.PHONY: all clean