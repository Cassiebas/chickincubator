MAKEFILES = $(shell find . -mindepth 1 -type f -name makefile)
SUBDIRS  := $(filter-out ./,$(dir $(MAKEFILES)))

CXX = g++

CXXFLAGS = -std=c++17 -Wall

SRCS := $(wildcard "src/*.cpp")

TARGET = bin/ChickenIncubator

INCLUDES := $(wildcard "includes/*.hpp")

SUBOBJS := $(wildcard "*/obj/*.o")

all: $(TARGET)
	for dir in $(SUBDIRS); do \
		make -C $$dir all; \
	done
$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)