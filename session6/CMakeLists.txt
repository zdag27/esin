cmake_minimum_required(VERSION 3.14)
project(session6)

set(CMAKE_CXX_STANDARD 14)

add_executable(session6 main.cpp call_registry.cpp call_registry.hpp call_registry.rep phone.cpp phone.hpp phone.rep util.hpp error.hpp)