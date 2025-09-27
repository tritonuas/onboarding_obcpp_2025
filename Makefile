# Makefile for the OBCpp Onboarding Project

CXX = g++
CXXFLAGS = -std=c++20 -Wall -I./deps -I./include -I./build/protos
LDFLAGS = -lprotobuf -lpthread

# gtest configs
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
GTEST_PREFIX ?= $(shell brew --prefix)/opt/googletest
GTEST_INCLUDE ?= $(GTEST_PREFIX)/include
GTEST_LIB_DIR ?= $(GTEST_PREFIX)/lib
else
# In the devcontainer, headers are in /usr/include and libs in /usr/local/lib
GTEST_INCLUDE ?= /usr/include
GTEST_LIB_DIR ?= /usr/local/lib
endif
GTEST_LDFLAGS = -L$(GTEST_LIB_DIR) -lgtest -lpthread

BUILD_DIR = build
PROTOS_DIR = protos
PROTO_BUILD_DIR = $(BUILD_DIR)/protos
TEST_BUILD_DIR = $(BUILD_DIR)/tests
EXECUTABLE = $(BUILD_DIR)/mission_runner

SOURCES = $(wildcard src/*.cpp src/core/*.cpp src/ticks/*.cpp src/network/*.cpp)

PROTO_HEADER = $(PROTO_BUILD_DIR)/onboarding.pb.h
PROTO_SOURCE = $(PROTO_BUILD_DIR)/onboarding.pb.cc

OBJECTS = $(addprefix $(BUILD_DIR)/, $(notdir $(SOURCES:.cpp=.o)))
OBJECTS += $(PROTO_BUILD_DIR)/onboarding.pb.o
NON_MAIN_OBJECTS = $(filter-out $(BUILD_DIR)/main.o, $(OBJECTS))

vpath %.cpp src src/core src/ticks src/network

# Build Targets
all: build
build: $(EXECUTABLE)
protos: $(PROTO_HEADER)

TEST_SOURCES = $(wildcard tests/unit/*.cpp)
TEST_OBJECTS = $(addprefix $(TEST_BUILD_DIR)/, $(notdir $(TEST_SOURCES:.cpp=.test.o)))
TEST_EXECUTABLE = $(TEST_BUILD_DIR)/unit_tests

# Integration test program(s)
INTEG_SOURCES = $(wildcard tests/integration/*.cpp)
INTEG_OBJECTS = $(addprefix $(TEST_BUILD_DIR)/, $(notdir $(INTEG_SOURCES:.cpp=.it.o)))
INTEG_BINARIES = $(addprefix $(TEST_BUILD_DIR)/, $(notdir $(INTEG_SOURCES:.cpp=)))

test: $(TEST_EXECUTABLE)
	@echo "Running unit tests..."
	@$(TEST_EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) | $(BUILD_DIR)
	@echo "Linking..."
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)
	@echo "Build complete. Executable is at $(EXECUTABLE)"

$(BUILD_DIR)/%.o: %.cpp $(PROTO_HEADER) | $(BUILD_DIR)
	@echo "Compiling $< -> $@"
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TEST_BUILD_DIR)/%.test.o: tests/unit/%.cpp | $(TEST_BUILD_DIR)
	@echo "Compiling test $< -> $@"
	$(CXX) $(CXXFLAGS) -I$(GTEST_INCLUDE) -c $< -o $@

$(TEST_BUILD_DIR)/%.it.o: tests/integration/%.cpp | $(TEST_BUILD_DIR)
	@echo "Compiling integration $< -> $@"
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TEST_EXECUTABLE): $(TEST_OBJECTS) $(NON_MAIN_OBJECTS) | $(TEST_BUILD_DIR) $(BUILD_DIR)
	@echo "Linking unit tests..."
	$(CXX) $(CXXFLAGS) -o $@ $(NON_MAIN_OBJECTS) $(TEST_OBJECTS) $(GTEST_LDFLAGS) $(LDFLAGS)
	@echo "Unit test binary is at $(TEST_EXECUTABLE)"

# Build all integration binaries
integration: $(INTEG_BINARIES)
	@echo "Integration binaries are in $(TEST_BUILD_DIR)"

# Pattern rule to link integration programs against non-main objects
$(TEST_BUILD_DIR)/%: $(TEST_BUILD_DIR)/%.it.o $(NON_MAIN_OBJECTS) | $(TEST_BUILD_DIR) $(BUILD_DIR)
	@echo "Linking integration $@..."
	$(CXX) $(CXXFLAGS) -o $@ $(NON_MAIN_OBJECTS) $< $(LDFLAGS)

$(PROTO_BUILD_DIR)/%.pb.o: $(PROTO_BUILD_DIR)/%.pb.cc | $(PROTO_BUILD_DIR)
	@echo "Compiling Protobuf source $< -> $@"
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(PROTO_HEADER) $(PROTO_SOURCE): $(PROTOS_DIR)/onboarding.proto | $(PROTO_BUILD_DIR)
	@echo "Generating Protobuf C++ code from $<..."
	protoc -I=$(PROTOS_DIR) --cpp_out=$(PROTO_BUILD_DIR) $<


$(BUILD_DIR) $(PROTO_BUILD_DIR) $(TEST_BUILD_DIR):
	@mkdir -p $@

# Utility Targets
clean:
	@echo "Cleaning up..."
	@rm -rf $(BUILD_DIR)

run: build
	@./$(EXECUTABLE)

.PHONY: all build protos clean run