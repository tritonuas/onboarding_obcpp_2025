# Makefile for the OBCpp Tick Tutorial

OPENCV_CFLAGS = $(shell pkg-config --cflags opencv4)
OPENCV_LIBS   = $(shell pkg-config --libs opencv4)

CXX = g++
CXXFLAGS = -std=c++17 -Wall -I./include $(OPENCV_CFLAGS)
BUILD_DIR = build
EXECUTABLE = $(BUILD_DIR)/mission_runner

SOURCES = $(wildcard src/*.cpp src/core/*.cpp src/ticks/*.cpp src/utilities/*.cpp src/camera/*.cpp)
OBJECTS = $(addprefix $(BUILD_DIR)/, $(notdir $(SOURCES:.cpp=.o)))

vpath %.cpp src src/core src/ticks src/camera src/utilities


# Build Targets 

# Default
all: $(EXECUTABLE) 

$(EXECUTABLE): $(OBJECTS) | $(BUILD_DIR)
	@echo "Linking..."
	$(CXX) $(CXXFLAGS) -o $(EXECUTABLE) $(OBJECTS) $(OPENCV_LIBS)
	@echo "Build complete. Executable is at $(EXECUTABLE)"

$(BUILD_DIR)/%.o: %.cpp | $(BUILD_DIR)
	@echo "Compiling $< -> $@"
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

# Will clear build directory
clean:
	@echo "Cleaning up..."
	@rm -rf $(BUILD_DIR)/*

run: all
	@./$(EXECUTABLE)

.PHONY: all clean 
