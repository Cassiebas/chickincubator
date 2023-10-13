CXX = g++

CXXFLAGS = -std=c++17 -Wall

SRCS = $(wildcard "src/*.cpp")

TARGET = $(subst .cpp,,$(SRCS))

INCLUDES = $(wildcard "includes/*.hpp")

all: $(TARGET)
$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)