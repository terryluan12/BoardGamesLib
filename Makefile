CC=gcc
CXX=g++
RM=rm -f
CPPFLAGS= -I $(DOGAN_INCLUDE_DIR) -I $(GEN_INCLUDE_DIR)

GEN_SRC_DIR=src
GEN_INCLUDE_DIR=include
GEN_BUILD_DIR=build

DOGAN_SRC_DIR=dogan/src
DOGAN_INCLUDE_DIR=dogan/include
DOGAN_BUILD_DIR=build/dogan

DOGAN_SRCS=$(wildcard $(DOGAN_SRC_DIR)/*.cpp)
GEN_SRCS=$(wildcard $(GEN_SRC_DIR)/*.cpp)

DOGAN_OBJS=$(patsubst $(DOGAN_SRC_DIR)/%.cpp, $(DOGAN_BUILD_DIR)/%.o, $(DOGAN_SRCS))
GEN_OBJS=$(patsubst $(GEN_SRC_DIR)/%.cpp, $(GEN_BUILD_DIR)/%.o, $(GEN_SRCS))

DOGAN_HEADERS = $(wildcard $(DOGAN_INCLUDE_DIR)/*.h)
GENERAL_HEADERS = $(wildcard $(GEN_INCLUDE_DIR)/*.h)

DOGAN_TARGET=dogan.exe

all: $(DOGAN_TARGET)

$(GEN_BUILD_DIR):
	@mkdir -p $(DOGAN_BUILD_DIR)

$(DOGAN_BUILD_DIR):
	@mkdir -p $(DOGAN_BUILD_DIR)

$(DOGAN_TARGET): $(DOGAN_OBJS) $(GEN_OBJS)
	$(CXX) $(CPPFLAGS) -Wall -o $(DOGAN_TARGET) $(DOGAN_OBJS) $(GEN_OBJS)

$(DOGAN_BUILD_DIR)/%.o: $(DOGAN_SRC_DIR)/%.cpp  | $(DOGAN_BUILD_DIR)
	$(CXX) $(CPPFLAGS) -Wall -c $< -o $@

$(GEN_BUILD_DIR)/%.o: $(GEN_SRC_DIR)/%.cpp  | $(GEN_BUILD_DIR)
	$(CXX) $(CPPFLAGS) -Wall -c $< -o $@

clean: 
	$(RM) $(DOGAN_OBJS) $(GEN_OBJS) $(DOGAN_TARGET)

format:
	clang-format -i $(DOGAN_SRCS) $(GEN_SRCS) $(DOGAN_HEADERS) $(GENERAL_HEADERS)

.PHONY: all clean