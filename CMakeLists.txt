cmake_minimum_required(VERSION 3.15)

project(Vampire LANGUAGES CXX)

# Require C++11 and disable extensions for all targets
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Define the main executable target and specify sources.
add_executable(vampire
    src/main/main.cpp
    src/main/version.cpp
    src/main/command.cpp
    src/main/githash.cpp
    src/main/initialise_variables.cpp
    src/main/material.cpp)

target_include_directories(vampire PRIVATE hdr)

add_subdirectory(src/anisotropy)
add_subdirectory(src/cells)
add_subdirectory(src/config)
add_subdirectory(src/constants)
add_subdirectory(src/create)
add_subdirectory(src/data)
add_subdirectory(src/dipole)
add_subdirectory(src/environment)
add_subdirectory(src/exchange)
add_subdirectory(src/gpu)
add_subdirectory(src/hamr)
add_subdirectory(src/hierarchical)
add_subdirectory(src/ltmp)
add_subdirectory(src/micromagnetic)
add_subdirectory(src/montecarlo)
add_subdirectory(src/mpi)
add_subdirectory(src/neighbours)
add_subdirectory(src/program)
add_subdirectory(src/qvoronoi)
add_subdirectory(src/random)
add_subdirectory(src/simulate)
add_subdirectory(src/spintorque)
add_subdirectory(src/spintransport)
add_subdirectory(src/statistics)
add_subdirectory(src/unitcell)
add_subdirectory(src/utility)
add_subdirectory(src/vio)

#add_subdirectory(src/cuda)
#add_subdirectory(src/opencl)

# Compiler specific flags and options,
# see: https://stackoverflow.com/questions/10046114/in-cmake-how-can-i-test-if-the-compiler-is-clang
# and: https://cmake.org/cmake/help/latest/variable/CMAKE_LANG_COMPILER_ID.html
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(WARNING_FLAGS -Wall)
    set(OPT_FLAGS "")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(WARNING_FLAGS /Wall)
    set(OPT_FLAGS "")
    # On MSVC we need to define _USE_MATH_DEFINES to get macros like M_PI
    target_compile_definitions(vampire PRIVATE _USE_MATH_DEFINES)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
    set(WARNING_FLAGS -Wall)
    set(OPT_FLAGS "")
endif()

# Set warning options.
target_compile_options(vampire PRIVATE ${WARNING_FLAGS})

# Set optimization options.
target_compile_options(vampire PRIVATE $<$<OR:$<CONFIG:Release>,$<CONFIG:RelWithDebInfo>>:${OPT_FLAGS}>)

if(WIN32)
    target_compile_definitions(vampire PRIVATE WIN_COMPILE)
endif()

# Define installation rules.
# Use GNU installation layout, i.e. 'bin', 'lib', 'include', ... folders.
include(GNUInstallDirs)
install(TARGETS vampire)
