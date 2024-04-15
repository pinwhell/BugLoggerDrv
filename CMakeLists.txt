cmake_minimum_required(VERSION 3.15)

project(BugLoggerDrv)

include_directories(include)

add_compile_options(-O3)

add_subdirectory(vendor)
add_subdirectory(src)