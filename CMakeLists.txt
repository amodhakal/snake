cmake_minimum_required(VERSION 3.29)

project(snake)

set(CMAKE_PREFIX_PATH /opt/homebrew)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)

find_package(raylib)

file(GLOB_RECURSE SNAKE_SRC CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_executable(snake "${SNAKE_SRC}")
target_link_libraries(snake PRIVATE raylib)
