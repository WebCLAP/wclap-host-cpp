cmake_minimum_required(VERSION 3.28)

add_library(wclap-cpp INTERFACE)
set_target_properties(wclap-cpp PROPERTIES INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/include)