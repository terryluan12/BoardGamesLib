CC=gcc
CXX=g++
RM=rm -f
# CPPFLAGS=-g -Wall  $(shell root-config --cflags)
# LDFLAGS=-g $(shell root-config --ldflags)
# LDLIBS=$(shell root-config --libs)

DOGAN_SRC_DIR=dogan
DOGAN_BUILD_DIR=build

DOGAN_SRCS=$(wildcard $(DOGAN_SRC_DIR)/*.cpp)
DOGAN_OBJS=$(patsubst $(DOGAN_SRC_DIR)/%.cpp, $(DOGAN_BUILD_DIR)/%.o, $(DOGAN_SRCS))

$(shell mkdir -p $(DOGAN_BUILD_DIR))

all: dogan

dogan: $(DOGAN_OBJS)
	$(CXX) -o dogan.exe $(DOGAN_OBJS)

$(DOGAN_BUILD_DIR)/%.o: $(DOGAN_SRC_DIR)/%.cpp
	$(CXX) -c $< -o $@

clean: $(RM) $(DOGAN_OBJS) dogan