cmake_minimum_required (VERSION 3.2) #最低要求的CMake版本
project(main_c) # 项目名称
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
set(CMAKE_C_COMPILER)
include_directories(includes)
add_executable(main ./src/main.c)
