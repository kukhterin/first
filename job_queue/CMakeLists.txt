cmake_minimum_required(VERSION 2.6)
project(jobqueue)

find_package(OpenSSL)

add_executable(jobqueue main.cpp Queue.cpp md5.cpp mutex_switcher.cpp put_get_file.cpp)

target_link_libraries(jobqueue ${OPENSSL_LIBRARIES})

install(TARGETS jobqueue RUNTIME DESTINATION bin)
