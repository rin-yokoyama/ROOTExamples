﻿# CMakeList.txt for the ROOTExamples project
# CMake version 3 is required
cmake_minimum_required (VERSION 3.0 FATAL_ERROR)
project(ROOTExamples CXX)

# Add in CMAKE_PREFIX_PATH the installation prefix for ROOT 
list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})
# You need to add COMPONENTS according to what you want to do.
find_package(ROOT REQUIRED COMPONENTS Core RIO Net Hist Tree Proof)
# Include ROOT cmake macros
include(${ROOT_USE_FILE})

# Set the default install prefix to [source_dir]/install
# (You usually don't want to install this project to /usr/local/)
set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/install CACHE PATH "install dir" FORCE)

add_subdirectory(ProofTreeAnalysis)
add_subdirectory(RDataFrameAnalysis)
add_subdirectory(share)
