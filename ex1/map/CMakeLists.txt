cmake_minimum_required(VERSION 3.0.0)
project(EX1 VERSION 0.1.0 LANGUAGES C)

# If you want to see "under the hood" of CMake, uncomment this:
set(CMAKE_VERBOSE_MAKEFILE ON)

# Define variables containing compiler flags for gcc
set(MTM_FLAGS_DEBUG "-std=c99 --pedantic-errors -Wall -Werror -g")
set(MTM_FLAGS_RELEASE "${MTM_FLAGS_DEBUG} -DNDEBUG")
# Set the flags for gcc
set(CMAKE_C_FLAGS ${MTM_FLAGS_RELEASE})

# Add the names of your source files here
set(MAP_C_FILES
        map.c
        DLLNode.c
        LinkedList.c
        )
set(TEST_C_FILES
        test/ListTests.c)

add_executable(map ${MAP_C_FILES} ${TEST_C_FILES})


