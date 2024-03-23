cmake_minimum_required(VERSION 3.28.0)
project(Interpol VERSION 0.1.0 LANGUAGES C CXX)
include("vcpkg.cmake")

file(GLOB_RECURSE SOURCES "src/*.hpp")

add_executable(Interpol ${SOURCES} "src/Interpol.cpp")

find_package(muparser CONFIG REQUIRED)
target_link_libraries(Interpol PRIVATE muparser::muparser)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Interpol PROPERTY CXX_STANDARD 20)
endif()