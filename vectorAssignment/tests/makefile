BUILD_DIR:=build

# Contains student code
SUBMISSION_DIR:=submission

# Contain sources for tests
TEST_DIR:=tests

SRC_DIR:=../src

# Contains library utilities designed to
# be portable between different assignment
# test suites
UTILS_DIR:=utils
INCLUDE_DIR:=include

# Specific to the current assignment
ASSIGNMENT_INCLUDE_DIR:=assignment-include
ASSIGNMENT_UTILS_DIR:=assignment-utils

# Two modes:
#
# STUDENT_SOURCES 
# - use the student sources
# - links to the submssion directory
#
# SAMPLE_SUBMISSION
# - use the TA sample solution
# - requires authentication
#
# CREATE_DIR
# - create sample submission directory
#
USE_SUBMISSION:=STUDENT_SOURCES

CXX:=g++
CFLAGS := -std=c++17
CFLAGS += -Wall -pedantic
# work in progress
# CFLAGS += -fsanitize=address
CFLAGS += -I$(INCLUDE_DIR) -I$(ASSIGNMENT_INCLUDE_DIR)
CFLAGS += -I$(SUBMISSION_DIR)

SRC_EXT:=%.cpp %.cc %.cxx

STD_BUILD=$(CXX) $(CFLAGS) $(EXTRA_CXXFLAGS) $(filter $(SRC_EXT) %.o, $^) -o $@
STD_COMPILE=$(STD_BUILD) -c

INCLUDE_HEADERS := $(wildcard $(INCLUDE_DIR)/*.h)
ASSIGNMENT_INCLUDE_HEADERS := $(wildcard  $(ASSIGNMENT_INCLUDE_DIR)/*.h)

# Add more assignment specific utilities here
# Although this will break when linking. Only include here if they are universally needed
ASSIGNMENT_OBJS :=
ASSIGNMENT_OBJS := $(patsubst %, $(ASSIGNMENT_UTILS_DIR)/%, $(ASSIGNMENT_OBJS))

UTILS_OBJS := memhook.o
UTILS_OBJS += xoshiro256.o
UTILS_OBJS += typegen.o

UTILS_OBJS := $(patsubst %,$(UTILS_DIR)/%, $(UTILS_OBJS))

TESTS_SRCS := $(wildcard $(TEST_DIR)/*.cpp)
TESTS := $(patsubst $(TEST_DIR)/%.cpp, %, $(TESTS_SRCS))

SUBMISSION_HEADERS = $(wildcard $(SUBMISSION_DIR)/*.h)
SUBMISSION_OBJS := $(patsubst %.cpp, %.o, $(wildcard $(SUBMISSION_DIR)/*.cpp))
# Ignore main.cpp
SUBMISSION_OBJS := $(filter-out $(SUBMISSION_DIR)/main.o, $(SUBMISSION_OBJS))

EXES := $(patsubst %, $(BUILD_DIR)/%, $(TESTS))

OBJECTS := $(UTILS_OBJS)
OBJECTS += $(ASSIGNMENT_OBJS)
OBJECTS += $(SUBMISSION_OBJS)

HEADERS := $(INCLUDE_HEADERS)
HEADERS += $(ASSIGNMENT_INCLUDE_HEADERS)
HEADERS += $(SUBMISSION_HEADERS)

# Configure automatic clone/cleanup for the sample submission
SS_ASSIGNEMNT_NAME:=assignment-vector
SS_CLONE_LOCATION:=./sample-submissions
SS_GIT_REPO:=git@github.tamu.edu:csce221/sample-submissions.git

SS_SUBMISSION_PATH:=$(SS_CLONE_LOCATION)/$(SS_ASSIGNEMNT_NAME)/$(SUBMISSION_DIR)

all: $(EXES)

ifeq ($(strip $(USE_SUBMISSION)),SAMPLE_SUBMISSION)
$(SS_CLONE_LOCATION):
	$(shell git clone $(SS_GIT_REPO) $(SS_CLONE_LOCATION))

$(SUBMISSION_DIR): $(SS_CLONE_LOCATION)
	$(shell ln -s $(SS_SUBMISSION_PATH) $(SUBMISSION_DIR))
else
ifeq ($(strip $(USE_SUBMISSION)),CREATE_DIR)
$(SUBMISSION_DIR):
	$(shell mkdir -p $(SUBMISSION_DIR))
else
$(SUBMISSION_DIR):
	$(shell ln -s $(SRC_DIR) $(SUBMISSION_DIR))
endif
endif

$(BUILD_DIR):
	$(shell mkdir -p $(BUILD_DIR))

setup-build: $(SUBMISSION_DIR) $(BUILD_DIR)
	@echo "Setting up build directories with" $(USE_SUBMISSION)

debug: EXTRA_CXXFLAGS := -DDEBUG -g
debug: clean all

list:
	@echo $(TESTS)
.phony: list

%.o: %.cpp
	$(STD_COMPILE)

$(BUILD_DIR)/datum_%: $(TEST_DIR)/datum_%.cpp $(OBJECTS) $(HEADERS) $(ASSIGNMENT_UTILS_DIR)/datum_utils.o
	$(STD_BUILD)

$(BUILD_DIR)/vector_%: $(TEST_DIR)/vector_%.cpp $(OBJECTS) $(HEADERS)
	$(STD_BUILD)

RUN_CMD=run

$(RUN_CMD)/%: $(BUILD_DIR)/%
	@$(patsubst $(RUN_CMD)/%, ./$(BUILD_DIR)/%, $@)
.phony: $(RUN_CMD)

run-all: $(patsubst %, $(RUN_CMD)/%, $(TESTS))
.phony: run-all

clean:
	$(RM) $(EXES) $(OBJECTS)

# also cleanup directories including the cloned sample submission
clean-all: clean
	rm -rf $(SUBMISSION_DIR)
	rm -rf $(SS_CLONE_LOCATION)
	rm -rf $(BUILD_DIR)

.phony: clean

