cmake_minimum_required(VERSION 3.11)


project(memory-mapped_files_demo)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

 
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_C_STANDARD 17)

include_directories("${CMAKE_SOURCE_DIR}")


add_executable(mmfd ${CMAKE_CURRENT_SOURCE_DIR}/mmfd.c)
add_executable(pipe_demo ${CMAKE_CURRENT_SOURCE_DIR}/pipe_demo.c)
add_executable(mkfifo_demo ${CMAKE_CURRENT_SOURCE_DIR}/mkfifo_demo.c)
add_executable(mkfifo_read_demo ${CMAKE_CURRENT_SOURCE_DIR}/mkfifo_read_demo.c)
add_executable(mkfifo_write_demo ${CMAKE_CURRENT_SOURCE_DIR}/mkfifo_write_demo.c)
add_executable(shared_memory_demo ${CMAKE_CURRENT_SOURCE_DIR}/shared_memory_demo.c)
add_executable(signal_demo ${CMAKE_CURRENT_SOURCE_DIR}/signal_demo.c)
add_executable(msg_queue_demo ${CMAKE_CURRENT_SOURCE_DIR}/msg_queue_demo.c)
add_executable(msg_queue_read_demo ${CMAKE_CURRENT_SOURCE_DIR}/msg_queue_read_demo.c)
add_executable(msg_queue_write_demo ${CMAKE_CURRENT_SOURCE_DIR}/msg_queue_write_demo.c)
add_executable(semaphore_demo ${CMAKE_CURRENT_SOURCE_DIR}/semaphore_demo.c)
add_executable(semaphore_consumer_demo ${CMAKE_CURRENT_SOURCE_DIR}/semaphore_consumer_demo.c)
add_executable(semaphore_creator_demo ${CMAKE_CURRENT_SOURCE_DIR}/semaphore_creator_demo.c)
add_executable(socket_client_demo ${CMAKE_CURRENT_SOURCE_DIR}/socket_client_demo.c)
add_executable(socket_server_demo ${CMAKE_CURRENT_SOURCE_DIR}/socket_server_demo.c)






