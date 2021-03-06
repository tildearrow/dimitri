cmake_minimum_required(VERSION 2.8.12)
project(dimitri)

# copied from RazerGenie
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(version 0.8.1)
set(datadir ${CMAKE_INSTALL_PREFIX}/share/razergenie)

find_package(ECM REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

find_package(Qt5 REQUIRED COMPONENTS DBus LinguistTools Network Xml Widgets)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

include(KDEInstallDirs)
#include(KDECompilerSettings) # this fucking piece of shit breaks my shared library -.-
include(KDECMakeSettings)
include(FeatureSummary)
include(CheckIncludeFiles)

add_subdirectory(RazerGenie/src/libopenrazer)
# end of copy

# actual stuff begins here
include_directories(RazerGenie/src/libopenrazer)

add_executable(dimitrid
src/devices/razer.cpp

src/effects/static.cpp
src/effects/spectrum.cpp
src/effects/wave.cpp

src/log.cpp
src/time.cpp
src/input.cpp
src/device.cpp
src/main.cpp)
target_link_libraries(dimitrid pthread X11 openrazer)
