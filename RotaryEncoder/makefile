CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wconversion -Wextra

SRCS := $(wildcard src/*.cpp)
OBJS := $(patsubst src/%.cpp,../obj/%.o,$(SRCS))
TARGET := ChickenIncubator

INCLUDES := $(addprefix -I, $(wildcard includes))
INCLUDES += $(addprefix -I, $(wildcard ../GPIO/includes))
INCLUDES += $(addprefix -I, $(wildcard ../Log/includes))

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