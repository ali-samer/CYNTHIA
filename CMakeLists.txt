cmake_minimum_required(VERSION 3.2)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

cmake_policy(SET CMP0042 NEW)
project(CYNTHIA)
include(CheckCXXCompilerFlag)
check_cxx_compiler_flag("-std=gnu++2a" CXX_SUPPORTS_CXX2A)

if(NOT CXX_SUPPORTS_CXX2A)
    message(FATAL_ERROR "The compiler ${CMAKE_CXX_COMPILER} has no C++20 support. Please use a different C++ compiler.")
else ()
endif()
message("compiler found: --------------${CMAKE_CXX_COMPILER}--------------")
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

configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/glad_config.h.in
        ${CMAKE_CURRENT_BINARY_DIR}/glad_config.h
)

set(SRC_FILES "")
set(SOURCE_DIRS
        "${CMAKE_SOURCE_DIR}/Sandbox/src"
        "${CMAKE_SOURCE_DIR}/CYNTHIA/src/CYNTHIA/Core"
        "${CMAKE_SOURCE_DIR}/CYNTHIA/src/CYNTHIA/GUI"
        "${CMAKE_SOURCE_DIR}/CYNTHIA/src/CYNTHIA/Image"
        "${CMAKE_SOURCE_DIR}/CYNTHIA/src/Platform/Mac"
        "${CMAKE_SOURCE_DIR}/CYNTHIA/src/Platform/Windows"
        "${CMAKE_SOURCE_DIR}/CYNTHIA/vendor/imgui"
        "${CMAKE_SOURCE_DIR}/CYNTHIA/vendor/glad/src"
)

foreach(SOURCE_DIR ${SOURCE_DIRS})
    file(GLOB SOURCE_FILES_IN_DIR
            "${SOURCE_DIR}/*.cpp"
            "${SOURCE_DIR}/*.c"
    )
    list(APPEND SRC_FILES ${SOURCE_FILES_IN_DIR})
endforeach()

list(APPEND SRC_FILES
        CYNTHIA/vendor/imgui/backends/imgui_impl_opengl3.cpp
        CYNTHIA/vendor/imgui/backends/imgui_impl_glfw.cpp)


add_compile_definitions(-DCY_WORKSPACE_DIR_PATH="${CMAKE_SOURCE_DIR}/")

add_subdirectory(CYNTHIA/vendor/eigen)
add_subdirectory(CYNTHIA/vendor/glfw)
add_subdirectory(CYNTHIA/src/CYNTHIA/Image)
add_subdirectory(CYNTHIA/vendor/pybind11)


include_directories(${CMAKE_SOURCE_DIR})
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

add_executable(CYNTHIA_EXE ${SRC_FILES})


target_link_libraries(CYNTHIA_EXE
        PRIVATE
        OpenGL::GL
        glfw
        stb_image
)

target_include_directories(CYNTHIA_EXE
        PRIVATE ${CMAKE_CURRENT_BINARY_DIR}
)

