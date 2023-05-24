# minimum CMake version required
cmake_minimum_required(VERSION 3.15)

# Project name, version and description
project("OMG-game" VERSION 0.1 DESCRIPTION "Course")

# Set C++ version
set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

# Include all cpp and h files
file(GLOB_RECURSE SRC src/*.cpp include/*.h)

# Add executable
add_executable(${PROJECT_NAME} ${SRC})

# Include libraries
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libs/include/)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/)

target_link_libraries(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/libs/win-x64/minifb.lib)
target_link_libraries(${PROJECT_NAME} kernel32 user32 shell32 dxgi d3d11 ole32 gdi32 winmm opengl32)
