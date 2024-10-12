CC=gcc
CXX=g++
RM=rm -f

DOGAN_SRC_DIR=dogan
DOGAN_BUILD_DIR=build

DOGAN_SRCS=$(wildcard $(DOGAN_SRC_DIR)/*.cpp)
DOGAN_OBJS=$(patsubst $(DOGAN_SRC_DIR)/%.cpp, $(DOGAN_BUILD_DIR)/%.o, $(DOGAN_SRCS))
DOGAN_TARGET=dogan.exe

$(shell mkdir -p $(DOGAN_BUILD_DIR))

all: dogan

dogan: $(DOGAN_OBJS)
	$(CXX) -o $(DOGAN_TARGET) $(DOGAN_OBJS)

$(DOGAN_BUILD_DIR)/%.o: $(DOGAN_SRC_DIR)/%.cpp
	$(CXX) -c $< -o $@

clean: 
	$(RM) $(DOGAN_OBJS) $(DOGAN_TARGET)