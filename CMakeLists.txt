cmake_minimum_required(VERSION 3.15)

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
target_compile_features(solarSystem PUBLIC cxx_std_14) # For std::make_unique
target_include_directories(solarSystem PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
target_sources(solarSystem
    PRIVATE
        src/App.cpp
        src/Engine.cpp
        src/RenderEngine.cpp
        src/PhysicsEngine.cpp
        src/GLManager.cpp
        src/SolarSphereObject.cpp
        src/Star.cpp
        src/Camera.cpp
        src/CameraController.cpp
        src/View.cpp
)


# Dependencies
add_subdirectory(lib)
target_link_libraries(solarSystem
    PRIVATE
        project_warnings
        glm
        glimac
        SDL
        OpenGL
        GLEW
)