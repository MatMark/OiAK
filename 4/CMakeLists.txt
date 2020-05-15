cmake_minimum_required(VERSION 3.16)
project(4 C)

set(CMAKE_C_STANDARD 11)

add_executable(4 main.c my_vectors.c my_vectors.h SIMD.c SIMD.h SISD.c SISD.h result_saver.c result_saver.h)