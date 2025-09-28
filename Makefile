# Makefile for the OBCpp Onboarding Project

OPENCV_CFLAGS = $(shell pkg-config --cflags opencv4)
OPENCV_LIBS   = $(shell pkg-config --libs opencv4)

CXX = g++
CXXFLAGS = -std=c++20 -Wall -I./deps -I./include -I./build/protos 
LDFLAGS = -lprotobuf -lpthread

BUILD_DIR = build
PROTOS_DIR = protos
PROTO_BUILD_DIR = $(BUILD_DIR)/protos
EXECUTABLE = $(BUILD_DIR)/mission_runner

SOURCES = $(wildcard src/*.cpp src/core/*.cpp src/ticks/*.cpp src/network/*.cpp src/camera/*.cpp src/utilities/*.cpp)

PROTO_HEADER = $(PROTO_BUILD_DIR)/onboarding.pb.h
PROTO_SOURCE = $(PROTO_BUILD_DIR)/onboarding.pb.cc

OBJECTS = $(addprefix $(BUILD_DIR)/, $(notdir $(SOURCES:.cpp=.o)))
OBJECTS += $(PROTO_BUILD_DIR)/onboarding.pb.o

vpath %.cpp src src/core src/ticks src/network src/utilities src/camera

# Build Targets
all: build
build: $(EXECUTABLE)
protos: $(PROTO_HEADER)

$(EXECUTABLE): $(OBJECTS) | $(BUILD_DIR) 
	@echo "Linking..."
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS) $(OPENCV_LIBS)
	@echo "Build complete. Executable is at $(EXECUTABLE)"

$(BUILD_DIR)/%.o: %.cpp $(PROTO_HEADER) | $(BUILD_DIR)
	@echo "Compiling $< -> $@"
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(OPENCV_CFLAGS)

$(PROTO_BUILD_DIR)/%.pb.o: $(PROTO_BUILD_DIR)/%.pb.cc | $(PROTO_BUILD_DIR)
	@echo "Compiling Protobuf source $< -> $@"
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(PROTO_HEADER) $(PROTO_SOURCE): $(PROTOS_DIR)/onboarding.proto | $(PROTO_BUILD_DIR)
	@echo "Generating Protobuf C++ code from $<..."
	protoc -I=$(PROTOS_DIR) --cpp_out=$(PROTO_BUILD_DIR) $<


$(BUILD_DIR) $(PROTO_BUILD_DIR):
	@mkdir -p $@

# Utility Targets
clean:
	@echo "Cleaning up..."
	@rm -rf $(BUILD_DIR)

run: build
	@./$(EXECUTABLE)

.PHONY: all build protos clean run
