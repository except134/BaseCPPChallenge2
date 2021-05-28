cmake_minimum_required(VERSION 2.8)
project(Challenge2)

if(MSVC)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
endif(MSVC)

file(GLOB SRC_FILES "*.cpp" "*.h")
add_executable(challenge2 ${SRC_FILES})
