CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

# Set the C++ standard
SET(CMAKE_CXX_STANDARD 17)

# Name of the project
PROJECT(GraphAlgorithms)

# Get the list of all files.
FILE(GLOB_RECURSE SOURCES "src/*.cpp")
FILE(GLOB_RECURSE HEADERS "src/*.h" "src/*.hpp" "src/*.tcc")

# Set the executable.
ADD_EXECUTABLE(${CMAKE_PROJECT_NAME} ${SOURCES} ${HEADERS})

# OS specific options and libraries
IF(MSVC)
    # Set Warning Level 4
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
ELSE()
	# Enable all pedantic warnings.
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic")
ENDIF()
