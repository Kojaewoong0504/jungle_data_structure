cmake_minimum_required(VERSION 3.30)
project(c_programing C)

set(CMAKE_C_STANDARD 11)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_library(linkedlist STATIC
        src/linkedlist.c
)

# 🔹 main 실행용
add_executable(main_exec
        main.c
)

# 🔹 테스트 실행용 (minunit 기반)
add_executable(test_linkedlist
        test/test_linkedlist.c
        include/minunit.h
        include/stack.h
        test/test_stack.c
        src/stack.c
        include/queue.h
        test/test_queue.c
        src/queue.c
)

# 🔗 실행 파일이 라이브러리를 사용할 수 있게 링크
target_link_libraries(main_exec linkedlist)
target_link_libraries(test_linkedlist linkedlist)