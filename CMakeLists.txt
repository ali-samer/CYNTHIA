cmake_minimum_required( VERSION 3.2 )
set( CMAKE_CXX_STANDARD 17 )
project( CYNTHIA )


include_directories( CYNTHIA/include )
include_directories( CYNTHIA/vendor/spdlog/include )

add_executable( CYNTHIA
                Sandbox/src/SandboxApp.cpp
                CYNTHIA/src/CYNTHIA/Core/Application.cpp
                CYNTHIA/src/CYNTHIA/Core/Log.cpp
                )
