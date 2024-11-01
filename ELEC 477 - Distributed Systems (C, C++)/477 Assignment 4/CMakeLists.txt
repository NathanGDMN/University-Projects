#
#

project(assign4 LANGUAGES C CXX)
cmake_minimum_required(VERSION 3.16)

# specify location of custom installed cyclone location
if(UNIX AND NOT APPLE)
    set(LINUX TRUE)
endif()

if(LINUX)
    message(STATUS ">>> Linux")
    set (CMAKE_PREFIX_PATH /opt/cyclone_cplusapi/lib/cmake;/opt/cyclone/lib/cmake)
endif()
if(APPLE)
    message(STATUS ">>> Mac OS")
    set(CMAKE_PREFIX_PATH /Users/dean/Teaching/477/DDS/install/lib/cmake)
    LIST(APPEND CMAKE_PROGRAM_PATH  "/Users/dean/Teaching/477/DDS/install/bin")
endif()

# CXX standard at least 
set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

if(NOT TARGET CycloneDDS-CXX::ddscxx)
  find_package(CycloneDDS-CXX REQUIRED)
endif()

# generation of code from idl files. One line per type
idlcxx_generate(TARGET statedata FILES statekey.idl WARNINGS no-implicit-extensibility)

add_executable(flights flights.cpp aircraft.cpp)
add_executable(subscriber subscriber.cpp)

# Link both executables to idl data type library and ddscxx.
target_link_libraries(flights CycloneDDS-CXX::ddscxx statedata)
target_link_libraries(subscriber CycloneDDS-CXX::ddscxx statedata)

set_property(TARGET flights PROPERTY CXX_STANDARD ${cyclonedds_cpp_std_to_use})
set_property(TARGET subscriber PROPERTY CXX_STANDARD ${cyclonedds_cpp_std_to_use})
