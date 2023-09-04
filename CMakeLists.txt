cmake_minimum_required(VERSION 3.2)
set(CMAKE_CXX_STANDARD 17)
project(CYNTHIA)

find_package(OpenGL REQUIRED)

include(CheckIncludeFile)

check_include_file(malloc/malloc.h HAVE_MALLOC_MALLOC_H)

if(NOT HAVE_MALLOC_MALLOC_H)
    find_path(MALLOC_INCLUDE_DIR malloc.h)
    message(STATUS "Attempting to find malloc.h")
    if(MALLOC_INCLUDE_DIR)
        message(STATUS "malloc.h located in ${MALLOC_INCLUDE_DIR} - Success")
        include_directories(${MALLOC_INCLUDE_DIR})
        return()
    else()
        message(FATAL_ERROR "Could not find malloc/malloc.h")
    endif()
endif()



add_subdirectory(CYNTHIA/vendor/glfw)
include_directories(CYNTHIA/include)
include_directories(CYNTHIA/vendor/glfw/include)
include_directories(CYNTHIA/vendor/spdlog/include)

add_compile_definitions(CY_ENABLE_ASSERTS)
add_compile_definitions(CY_ENABLE_USEFUL_MACROS)

if (WIN32)
    add_compile_definitions(CY_ENABLE_ASSERTS_WIN32)
else ()
    add_compile_definitions(CY_ENABLE_ASSERTS_DARWIN)
endif ()


add_executable(CYNTHIA_EXE
        Sandbox/src/SandboxApp.cpp
        CYNTHIA/src/CYNTHIA/Core/Application.cpp
        CYNTHIA/src/CYNTHIA/Core/Log.cpp
        CYNTHIA/src/CYNTHIA/Core/Window.cpp
        CYNTHIA/src/Platform/MacWindow.cpp
        CYNTHIA/src/Platform/Win32Window.cpp
        CYNTHIA/src/CYNTHIA/Core/LayerStack.cpp
        CYNTHIA/src/CYNTHIA/Core/Layer.cpp)


target_link_libraries(CYNTHIA_EXE
        PRIVATE
        OpenGL::GL
        glfw
        )