cmake_minimum_required(VERSION 3.19)
project(TestingFunctionsIndividually C)

set(CMAKE_C_STANDARD 99)

add_executable(TestingFunctionsIndividually main.c ../chess/strUtils.c)