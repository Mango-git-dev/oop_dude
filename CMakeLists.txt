cmake_minimum_required(VERSION 3.10)
project(QuanLyXe VERSION 1.0 LANGUAGES CXX)

# Set C++ Standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(
    src/model
    src/view
    src/controller
    src/data
    src/exception
)

# Collect all source files
file(GLOB_RECURSE SOURCES 
    "src/model/*.cpp"
    "src/view/*.cpp"
    "src/controller/*.cpp"
    "src/data/*.cpp"
)

# Define executable
add_executable(QuanLyXe main.cpp ${SOURCES})
