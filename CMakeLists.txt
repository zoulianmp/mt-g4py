# - Top-level CMakeLists.txt for Geant4Py

cmake_minimum_required(VERSION 2.6)

#------------------------------------------------------------------------------
project(Geant4Py)
#------------------------------------------------------------------------------
# installation prefixes for libraries
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})

# debug mode
set(DEBUG FALSE CACHE BOOL "Debug Mode (Debug On)")

#------------------------------------------------------------------------------
# Do not edit below
#------------------------------------------------------------------------------
# cmake modules
set(CMAKE_MODULE_PATH
    ${PROJECT_SOURCE_DIR}/cmake/Modules
    ${CMAKE_MODULE_PATH})

include(SetInstallPath)

# Begin --> added by zoulian

set (GEANT4_INSTALL "/home/zoulian/Geant4/Geant4Install")

set(G4_Configfile "${GEANT4_INSTALL}/lib/Geant4-10.2.0/Geant4Config.cmake")

set(G4_Usefile "${GEANT4_INSTALL}/lib/Geant4-10.2.0/UseGeant4.cmake")

Set(CMAKE_INSTALL_LIBDIR  "/home/zoulian/Geant4/g4py-install" CACHE STRING "Root dir for pyg4 lib install ")


# End --> added by zoulian

# searching packages...
find_package(Geant4 REQUIRED)
find_package(PythonInterp REQUIRED)
find_package(PythonLibs REQUIRED)
find_package(Boost)
find_package(XercesC)
find_package(ROOT)

#if(NOT GEANT4_FOUND)
#  message(FATAL_ERROR "NOT Found Geant4.")
#endif()


# Begin --> added by zoulian

#----------------------------------------------------------------------------
# Setup Geant4 include directories and compile definitions
# Setup include directory for this project
#


include(${G4_Usefile})

include_directories(${PROJECT_SOURCE_DIR}/include)


# End --> added by zoulian



#------------------------------------------------------------------------------
# parameters for building
message(STATUS "--------------------------------------------------------")
message(STATUS "Parameters for building")

# build options
if(NOT CMAKE_BUILD_TYPE)
  if(DEBUG)
    set(CMAKE_BUILD_TYPE "Debug")
  else()
    set(CMAKE_BUILD_TYPE "RelWithDebInfo")
  endif()
endif()
message(STATUS "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
message(STATUS "CMAKE_CXX_COMPILER: ${CMAKE_CXX_COMPILER}")

message(STATUS "CMAKE_INSTALL_PREFIX: ${CMAKE_INSTALL_PREFIX}")
message(STATUS "--------------------------------------------------------")

#------------------------------------------------------------------------------
# add subdiretories...

# adding sub directories to the project
# libraries
add_subdirectory(source)
add_subdirectory(site-modules)

# examples
add_subdirectory(examples)

# tests
add_subdirectory(tests EXCLUDE_FROM_ALL)

