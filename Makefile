CC=gcc
CXX=g++
RM=rm -f
CPPFLAGS= -I $(DOGAN_INCLUDE_DIR) -I $(GENERAL_INCLUDE_DIR)

GENERAL_INCLUDE_DIR=include
DOGAN_SRC_DIR=dogan/src
DOGAN_INCLUDE_DIR=dogan/include
DOGAN_BUILD_DIR=build

DOGAN_SRCS=$(wildcard $(DOGAN_SRC_DIR)/*.cpp)
DOGAN_OBJS=$(patsubst $(DOGAN_SRC_DIR)/%.cpp, $(DOGAN_BUILD_DIR)/%.o, $(DOGAN_SRCS))
DOGAN_TARGET=dogan.exe

$(shell mkdir -p $(DOGAN_BUILD_DIR))

all: dogan

dogan: $(DOGAN_OBJS)
	$(CXX) $(CPPFLAGS) -Wall -o $(DOGAN_TARGET) $(DOGAN_OBJS)

$(DOGAN_BUILD_DIR)/%.o: $(DOGAN_SRC_DIR)/%.cpp
	$(CXX) $(CPPFLAGS) -Wall -c $< -o $@

clean: 
	$(RM) $(DOGAN_OBJS) $(DOGAN_TARGET)