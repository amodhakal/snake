cmake_minimum_required(VERSION 3.29)

project(snake)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)

# include(FetchContent)
# FetchContent_Declare(
#         raylib
#         GIT_REPOSITORY https://github.com/raysan5/raylib.git
#         GIT_TAG 5.5 
# )

# FetchContent_MakeAvailable(raylib)

set(CMAKE_PREFIX_PATH /opt/homebrew)
find_package(raylib 3.0 REQUIRED)


file(GLOB_RECURSE SNAKE_SRC CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_executable(snake "${SNAKE_SRC}")

target_include_directories(snake PRIVATE ${raylib_SOURCE_DIR}/src)
target_link_libraries(snake PRIVATE raylib)
