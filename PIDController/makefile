CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wconversion -Wextra -pthread

SRCS := $(wildcard src/*.cpp)
OBJS := $(patsubst src/%.cpp,../obj/%.o,$(SRCS))
TARGET := EggIncubator

INCLUDES := $(addprefix -I, $(wildcard includes))
INCLUDES += $(addprefix -I, $(wildcard ../PWM/includes))
INCLUDES += $(addprefix -I, $(wildcard ../HeaterController/includes))
INCLUDES += $(addprefix -I, $(wildcard ../Timer/includes))
INCLUDES += $(addprefix -I, $(wildcard ../HeatingElement/includes))
INCLUDES += $(addprefix -I, $(wildcard ../HarryPlotter/includes))
INCLUDES += $(addprefix -I, $(wildcard ../Thermistor/includes))
INCLUDES += $(addprefix -I, $(wildcard ../Log/includes))
INCLUDES += $(addprefix -I, $(wildcard ../GPIO/includes))

LIBS := -DBOOST_LOG_DYN_LINK
LIBS += $(addprefix -l, boost_iostreams)
LIBS += $(addprefix -l, boost_system)
LIBS += $(addprefix -l, boost_thread)
LIBS += $(addprefix -l, boost_filesystem)
LIBS += $(addprefix -p, thread)
LIBS += $(addprefix -l, boost_log)
LIBS += $(addprefix -l, boost_log_setup)

all: $(OBJS)

$(OBJS): ../obj/%.o : src/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@ $(LIBS)

clean:
	rm -f $(OBJS)

.PHONY: all clean