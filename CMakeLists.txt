cmake_minimum_required(VERSION 3.2)
set(CMAKE_CXX_STANDARD 17)
project(CYNTHIA)

find_package(OpenGL REQUIRED)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)

add_subdirectory(CYNTHIA/vendor/glfw)
include_directories(CYNTHIA/include)
include_directories(CYNTHIA/vendor/glfw/include)
include_directories(CYNTHIA/vendor/spdlog/include)

add_executable(CYNTHIA
        Sandbox/src/SandboxApp.cpp
        CYNTHIA/src/CYNTHIA/Core/Application.cpp
        CYNTHIA/src/CYNTHIA/Core/Log.cpp
        )



target_link_libraries(CYNTHIA
        PRIVATE
        OpenGL::GL
        glfw
        )