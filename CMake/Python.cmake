# Check if Python vars have been set in CLI

message(STATUS "Checking if Python paths have been set...")

if (NOT DEFINED PYTHON_INCLUDE_DIR)
	message(FATAL_ERROR "Please provide Python include directory as CMake argument! Usage: -DPYTHON_INCLUDE_DIR=/path/to/python/include")
else()
	message(STATUS "PYTHON_INCLUDE_DIR=${PYTHON_INCLUDE_DIR}")
endif()

if (NOT DEFINED PYTHON_LIB_DIR)
	message(FATAL_ERROR "Please provide Python lib directory as CMake argument! Usage: -DPYTHON_LIB_DIR=/path/to/python/lib")
else()
	message(STATUS "PYTHON_LIB_DIR=${PYTHON_LIB_DIR}")
endif()

if (NOT DEFINED PYTHON_LIB)
	message(FATAL_ERROR "Please provide Python library as CMake argument! Usage -DPYTHON_LIB=python3.11")
else()
	message(STATUS "PYTHON_LIB=${PYTHON_LIB}")
endif()

message(STATUS "Python OK!")