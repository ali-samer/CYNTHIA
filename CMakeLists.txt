cmake_minimum_required(VERSION 3.2)
set(CMAKE_CXX_STANDARD 17)
cmake_policy(SET CMP0042 NEW)
project(CYNTHIA)

find_package(OpenGL REQUIRED)

include(CheckIncludeFile)

check_include_file(malloc/malloc.h HAVE_MALLOC_MALLOC_H)

if(NOT HAVE_MALLOC_MALLOC_H) # TODO: reference when writing package tests in cmake: must remove before releasing project
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


add_subdirectory(CYNTHIA/vendor/eigen)
add_subdirectory(CYNTHIA/vendor/glfw)
add_subdirectory(CYNTHIA/src/CYNTHIA/Image)
add_subdirectory(CYNTHIA/vendor/pybind11)

include_directories(CYNTHIA/include)
include_directories(CYNTHIA/vendor)
include_directories(CYNTHIA/vendor/glfw/include)
include_directories(CYNTHIA/vendor/spdlog/include)
include_directories(CYNTHIA/vendor/glad/include)
include_directories(CYNTHIA/vendor/imgui)

add_compile_definitions(CY_ENABLE_ASSERTS)
add_compile_definitions(CY_ENABLE_USEFUL_MACROS)

if (WIN32)
    add_compile_definitions(CY_ENABLE_ASSERTS_WIN32)
    add_compile_definitions(CY_PLATFORM_WINDOWS)
else ()
    add_compile_definitions(CY_ENABLE_ASSERTS_DARWIN)
    add_compile_definitions(CY_PLATFORM_DARWIN)
endif ()
add_compile_definitions(GL_SILENCE_DEPRECATION) #silence annoying gl deprecation warnings
add_compile_definitions(GLFW_INCLUDE_NONE) #GLAD will complain if GLFW include is enabled

add_executable(CYNTHIA_EXE
        Sandbox/src/SandboxApp.cpp
        CYNTHIA/src/CYNTHIA/Core/Application.cpp
        CYNTHIA/src/CYNTHIA/Core/Log.cpp
        CYNTHIA/src/CYNTHIA/Core/Window.cpp
        CYNTHIA/src/Platform/Mac/MacWindow.cpp
        CYNTHIA/src/Platform/Windows/Win32Window.cpp
        CYNTHIA/src/CYNTHIA/Core/LayerStack.cpp
        CYNTHIA/src/CYNTHIA/Core/Layer.cpp
        CYNTHIA/vendor/glad/src/glad.c
        CYNTHIA/src/CYNTHIA/GUI/ImGuiLayer.cpp
        CYNTHIA/vendor/imgui/imgui.cpp
        CYNTHIA/vendor/imgui/imgui_demo.cpp
        CYNTHIA/vendor/imgui/imgui_draw.cpp
        CYNTHIA/vendor/imgui/imgui_tables.cpp
        CYNTHIA/vendor/imgui/imgui_widgets.cpp
        CYNTHIA/vendor/imgui/backends/imgui_impl_opengl3.cpp
        CYNTHIA/vendor/imgui/backends/imgui_impl_glfw.cpp
        CYNTHIA/src/CYNTHIA/Image/Image.cpp
        CYNTHIA/src/CYNTHIA/EigenUtils/EigenAliases.cpp
        CYNTHIA/src/CYNTHIA/EigenUtils/EigenUtilities.cpp
        CYNTHIA/src/Platform/Windows/WindowsInput.cpp
        CYNTHIA/src/CYNTHIA/GUI/ImGUIBuild.cpp
)


target_link_libraries(CYNTHIA_EXE
        PRIVATE
        OpenGL::GL
        glfw
        stb_image
        )