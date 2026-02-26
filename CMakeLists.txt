cmake_minimum_required(VERSION 3.20)
project(prefix_tools LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(prefix_tools INTERFACE)
add_library(prefix_tools::prefix_tools ALIAS prefix_tools)

target_include_directories(prefix_tools INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

if (MSVC)
  target_compile_options(prefix_tools INTERFACE /W4 /permissive-)
else()
  target_compile_options(prefix_tools INTERFACE -Wall -Wextra -Wpedantic)
endif()

include(CTest)
enable_testing()

add_executable(prefix_tools_basic_test tests/test_basic.cpp)
target_link_libraries(prefix_tools_basic_test PRIVATE prefix_tools::prefix_tools)
add_test(NAME prefix_tools.basic COMMAND prefix_tools_basic_test)
