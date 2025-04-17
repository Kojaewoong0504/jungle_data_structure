cmake_minimum_required(VERSION 3.30)
project(c_programing C)

set(CMAKE_C_STANDARD 11)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(${CMAKE_SOURCE_DIR}/include)


add_executable(stackqueue
        include/minunit.h
        Data-Structures-master/Stack_and_Queue/stack.c
        Data-Structures-master/Stack_and_Queue/queue.c
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
        include/binary_tree.h
        test/test_binary_tree.c
        src/binary_tree.c
        include/binary_search_tree.h
        test/test_binary_search_tree.c
        src/binary_search_tree.c
        include/b_tree.h
        test/test_b_tree.c
        src/b_tree.c
)

# 🔗 실행 파일이 라이브러리를 사용할 수 있게 링크
target_link_libraries(main_exec)
target_link_libraries(test_linkedlist)
target_link_libraries(stackqueue)