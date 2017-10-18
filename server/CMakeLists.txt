cmake_minimum_required(VERSION 2.6)
project(testserver)

add_executable(testserver main.cpp Server.cpp Client.cpp Socket.cpp)

install(TARGETS testserver RUNTIME DESTINATION bin)
