cmake_minimum_required(VERSION 3.18)

set(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(BUILD_DIR ${CMAKE_CURRENT_BINARY_DIR})
set(EXTERN_DIR ${ROOT_DIR}/Extern)
set(SCRIPTS_DIR ${ROOT_DIR}/CMake)
set(SAMPLE_PLUGINS_DIR ${ROOT_DIR}/Samples)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

project(Source2Py LANGUAGES CXX)

include("${SCRIPTS_DIR}/Python.cmake")
include("${SCRIPTS_DIR}/Source2SDK.cmake")
include("${SCRIPTS_DIR}/Metamod.cmake")

file(GLOB SOURCE2PY_SRCS 
	"Source2Py/src/*.cpp"
	"Source2Py/src/*.h"
)

add_library(Source2Py SHARED ${SOURCE2PY_SRCS})
target_include_directories(Source2Py PRIVATE
	${SOURCE2SDK_INCLUDE_DIRS}
	${METAMOD_INCLUDE_DIRS}
	${EXTERN_DIR}/pybind11/include
	${Python3_INCLUDE_DIRS}
)
target_link_libraries(Source2Py PRIVATE
	Source2SDK
	Metamod
	${Python3_LIBRARIES}
)
set_target_properties(Source2Py PROPERTIES
	OUTPUT_NAME "Source2Py"
	PREFIX ""
)

include("${SCRIPTS_DIR}/Package.cmake")