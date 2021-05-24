project(ex1 LANGUAGES C)
set(CMAKE_C_STANDARD 99)
set(MTM_FLAGS_DEBUG "-std=c99 --pedantic-errors -Wall -Werror")
set(MTM_FLAGS_RELEASE "${MTM_FLAGS_DEBUG} -DNDEBUG")
set(CMAKE_C_FLAGS "${MTM_FLAGS_RELEASE}")


link_directories(.)
add_executable(ex1 main.c)
target_link_libraries(ex1 libmap.a)