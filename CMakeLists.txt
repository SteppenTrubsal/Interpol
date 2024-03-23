cmake_minimum_required(VERSION 3.28.0)
project(Interpol VERSION 0.1.0 LANGUAGES C CXX)


file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.hpp")

add_executable(Interpol ${SOURCES})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Interpol PROPERTY CXX_STANDARD 20)
endif()