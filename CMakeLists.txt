cmake_minimum_required(VERSION 3.30)
project(c_programing C)

set(CMAKE_C_STANDARD 11)

add_library(c_programing STATIC library.c
        main.c
        pointer_study/pointer_study1.c)

# 모든 .c 파일을 재귀적으로 수집
file(GLOB_RECURSE ALL_SRC_FILES
        "${CMAKE_SOURCE_DIR}/Data-Structures-master/*.c"
)

# 하나의 실행 파일로 만들기 (모든 파일 포함)
add_executable(main_all ${ALL_SRC_FILES})