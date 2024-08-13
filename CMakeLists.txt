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
add_executable(tcp_client Lab_03/tcp_client.c)
add_executable(tcp_server Lab_03/tcp_server.c)
add_executable(udp_client Lab_04/udp_client.c)
add_executable(udp_server Lab_04/udp_server.c)

