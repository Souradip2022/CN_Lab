cmake_minimum_required(VERSION 3.28)
project(CN C)

set(CMAKE_C_STANDARD 11)

add_executable(1.1 Lab_01/1.1.c)
add_executable(1.2 Lab_01/1.2.c)
add_executable(1.3 Lab_01/1.3.c)
add_executable(1.4 Lab_01/1.4.c)
add_executable(1.5 Lab_01/1.5.c)

add_executable(2.1 Lab_02/2.1.c)
add_executable(2.2 Lab_02/2.2.c)

add_executable(tcp_client Lab_02/tcp_client.c)
add_executable(tcp_server Lab_02/tcp_server.c)
add_executable(udp_client Lab_03/udp_client.c)
add_executable(udp_server Lab_03/udp_server.c)

add_executable(chat_client Lab_04/chat_client.c)
add_executable(chat_server Lab_04/chat_server.c)
add_executable(sort_client Lab_04/sort_client.c)
add_executable(sort_server Lab_04/sort_server.c)

add_executable(file_transfer_server Lab_05/file_transfer_server.c)
add_executable(client Lab_05/file_download_client.c)

