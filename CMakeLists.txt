cmake_minimum_required(VERSION 3.28.0)
project(Interpol VERSION 0.1.0 LANGUAGES C CXX)
include("vcpkg.cmake")

file(GLOB_RECURSE SOURCES "src/*.hpp")

add_executable(Interpol ${SOURCES} "src/Interpol.cpp")

find_package(muparser CONFIG REQUIRED)
find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
find_package(implot CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(ImGui-SFML CONFIG REQUIRED)
target_link_libraries(Interpol PRIVATE muparser::muparser sfml-system sfml-graphics sfml-window  ImGui-SFML::ImGui-SFML imgui::imgui implot::implot)


set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/Fonts")
set(DESTINATION_DIR ${CMAKE_BINARY_DIR})
file(COPY ${SOURCE_DIR} DESTINATION "${DESTINATION_DIR}")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Interpol PROPERTY CXX_STANDARD 20)
endif()