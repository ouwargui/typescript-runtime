cmake_minimum_required(VERSION 3.31)

project(typescript_runtime C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/src/*.c ${PROJECT_SOURCE_DIR}/src/lib/*.c)
add_executable(typescript_runtime ${SOURCES})

target_compile_options(typescript_runtime PRIVATE
  -Wall
  -Wextra
  -Wpedantic
  -g
)
