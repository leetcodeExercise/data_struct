cmake_minimum_required (VERSION 3.8)
# SET(CMAKE_BUILD_TYPE "Release")
project(test)
FILE(GLOB SOURCE_1 "${CMAKE_SOURCE_DIR}/main.cpp")
FILE(GLOB SOURCE_2 "${CMAKE_SOURCE_DIR}/src/*.cpp")
INCLUDE_DIRECTORIES("${CMAKE_SOURCE_DIR}/src/*.h")
SET(CMAKE_CXX_STANDARD 20)
add_executable (${PROJECT_NAME} ${SOURCE_1} ${SOURCE_2})
