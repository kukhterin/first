cmake_minimum_required(VERSION 2.6)
project(myfifo)

add_executable(myfifo main.cpp NamedPipe.cpp Worker.cpp)

install(TARGETS myfifo RUNTIME DESTINATION bin)
