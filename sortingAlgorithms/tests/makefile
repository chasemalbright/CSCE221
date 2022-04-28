# Include the TA configuration if it exists
-include ta_config

# Build directory
BUILD_DIR?=build
# Contain sources for tests
TEST_DIR?=tests
# Source directory
SRC_DIR?=../src

# Contains library utilities designed to
# be portable between different assignment
# test suites
UTILS_DIR?=utils
INCLUDE_DIR?=include

# Specific to the current assignment
ASSIGNMENT_INCLUDE_DIR?=assignment-include
ASSIGNMENT_UTILS_DIR?=assignment-utils

DEBUG_FLAGS := -DDEBUG -g

CXX?=g++
CFLAGS ?=
CFLAGS += -std=c++17
CFLAGS += -Wall -pedantic
CFLAGS += $(DEBUG_FLAGS)
# work in progress
# CFLAGS += -fsanitize=address
CFLAGS += -I$(INCLUDE_DIR) -I$(ASSIGNMENT_INCLUDE_DIR)
CFLAGS += -I$(SRC_DIR)

# Add more assignment specific utilities here
# Although this will break when linking. Only include here if they are universally needed
ASSIGNMENT_OBJS :=

UTILS_OBJS := memhook.o
UTILS_OBJS += xoshiro256.o
UTILS_OBJS += typegen.o

##########################################################################################

SRC_EXT:=%.cpp %.cc %.cxx

STD_BUILD=$(CXX) $(CFLAGS) $(EXTRA_CXXFLAGS) $(filter $(SRC_EXT) %.o, $^) -o $@
STD_COMPILE=$(STD_BUILD) -c

## UTILS ##

INCLUDE_HEADERS := $(wildcard $(INCLUDE_DIR)/*.h)
UTILS_OBJS := $(patsubst %,$(UTILS_DIR)/%, $(UTILS_OBJS))

## TESTS ##

TESTS_SRCS := $(wildcard $(TEST_DIR)/*.cpp)
TESTS := $(patsubst $(TEST_DIR)/%.cpp, %, $(TESTS_SRCS))

## SRC ##

SRC_HEADERS = $(wildcard $(SRC_DIR)/*.h)
SRC_OBJS := $(patsubst %.cpp, %.o, $(wildcard $(SRC_DIR)/*.cpp))
# Ignore main.cpp
SRC_OBJS := $(filter-out $(SRC_DIR)/main.o, $(SRC_OBJS))

EXES = $(patsubst %, $(BUILD_DIR)/%, $(TESTS))

## ASSIGNMENT ##

ASSIGNMENT_INCLUDE_HEADERS := $(wildcard  $(ASSIGNMENT_INCLUDE_DIR)/*.h)
ASSIGNMENT_OBJS := $(patsubst %, $(ASSIGNMENT_UTILS_DIR)/%, $(ASSIGNMENT_OBJS))

## BUILD ##

OBJECTS := $(UTILS_OBJS)
OBJECTS += $(ASSIGNMENT_OBJS)
OBJECTS += $(SRC_OBJS)

HEADERS := $(INCLUDE_HEADERS)
HEADERS += $(ASSIGNMENT_INCLUDE_HEADERS)
HEADERS += $(SRC_HEADERS)

build-all all: $(EXES)

$(BUILD_DIR):
	$(shell mkdir -p $(BUILD_DIR))

list:
	@echo $(TESTS)
.PHONY: list

%.o: %.cpp
	$(STD_COMPILE)

RUN_CMDS := $(patsubst %, run/%, $(TESTS))

run/%: $(BUILD_DIR)/%
	@$(patsubst run/%, ./$(BUILD_DIR)/%, $@)

run-all: $(RUN_CMDS)

clean:
	$(RM) $(EXES) $(OBJECTS)
	$(shell rm -rf $(BUILD_DIR))
.PHONY: clean

## ASSIGNMENT-SPECIFIC BUILD PROCESSES ##

$(BUILD_DIR)/%: $(TEST_DIR)/%.cpp $(OBJECTS) $(HEADERS) $(BUILD_DIR)
	$(STD_BUILD)
