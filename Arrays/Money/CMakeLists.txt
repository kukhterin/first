cmake_minimum_required(VERSION 2.6)
project(money)

add_executable(money main.cpp)

install(TARGETS money RUNTIME DESTINATION bin)
