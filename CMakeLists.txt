cmake_minimum_required(VERSION 3.1)

project(SolarSystemOpenGL CXX)

# Finding Packages
find_package(SDL REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

# Warnings
include(cmake/CompilerWarnings.cmake)
add_library(project_warnings INTERFACE)
set_project_warnings(project_warnings)

# Program
add_executable(solarSystem "")
target_sources(solarSystem
    PRIVATE
        src/exo1.cpp
)

# Dependencies
add_subdirectory(lib)
target_link_libraries(solarSystem
    PRIVATE
        glm
        glimac
        SDL
        OpenGL
        GLEW
)