cmake_minimum_required(VERSION 3.15)

project(Utilities)

#
# -----------------------------------------
#

# Check if variable is set, otherwise set to default
if(NOT RELATIVE_BUILD_FOLDER)
	set(RELATIVE_BUILD_FOLDER build)
endif()
if(NOT CMAKE_INSTALL_PREFIX)
	set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR})
endif()
if(NOT RELATIVE_INSTALL_FOLDER)
	set(RELATIVE_INSTALL_FOLDER lib)
endif()

# Set output paths
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/${RELATIVE_BUILD_FOLDER}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/${RELATIVE_BUILD_FOLDER}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/${RELATIVE_BUILD_FOLDER}")

# Link to the output path
link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

# Add core as subdir, core contains the library
add_subdirectory(core)
add_subdirectory(UnitTests)


