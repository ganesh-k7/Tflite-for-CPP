cmake_minimum_required(VERSION 3.17)

# Set the OpenCV directory explicitly
set(OpenCV_DIR "/usr/lib/x86_64-linux-gnu/cmake/opencv4")

# Print debug information to verify paths
message(STATUS "OpenCV_DIR is set to: ${OpenCV_DIR}")
find_package(OpenCV REQUIRED)
message(STATUS "OpenCV_INCLUDE_DIRS: ${OpenCV_INCLUDE_DIRS}")
message(STATUS "OpenCV_LIBS: ${OpenCV_LIBS}")

include_directories(${OpenCV_INCLUDE_DIRS})

project(TFLite)

set(CMAKE_CXX_STANDARD 14)

# Include directories for TensorFlow Lite and Flatbuffers
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/tflite-dist/include/)

# Link to TensorFlow Lite library
ADD_LIBRARY(tensorflowlite SHARED IMPORTED)
set_property(TARGET tensorflowlite PROPERTY IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/tflite-dist/libs/libtensorflowlite.so)

# Define the executable
add_executable(TFLite main.cpp)

# Link TensorFlow Lite and OpenCV libraries to the executable
target_link_libraries(TFLite tensorflowlite ${OpenCV_LIBS})

# Add a custom target to clean the `build` directory
add_custom_target(clean_build
    COMMAND ${CMAKE_COMMAND} -E rm -rf ${CMAKE_BINARY_DIR}/*
    COMMENT "Cleaning up build directory"
)

