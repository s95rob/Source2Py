# Check if Python environment variables have been set

find_package(Python3 COMPONENTS Interpreter Development)

if (NOT DEFINED Python3_Development_FOUND)
	message(FATAL_ERROR "Please make sure Python3 (including development artifacts) installed correctly on your system!")
else()
	message(STATUS "Linking Python ${Python3_VERSION}")
endif()