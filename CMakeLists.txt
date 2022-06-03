cmake_minimum_required(VERSION 3.21)
project(projeto C)

set(CMAKE_C_STANDARD 11)

add_executable(projeto main.c structs.h student_ops.c expenses.c imports.h validation.h expenses.h student_ops.h student_list.h student_list.c validation.c)
add_compile_options(-Wall -Wextra)
