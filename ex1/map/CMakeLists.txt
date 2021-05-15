cmake_minimum_required(VERSION 3.19)
project(map C)

set(CMAKE_C_STANDARD 99)

add_executable(map main.c DLLNode.h DLLNode.c)