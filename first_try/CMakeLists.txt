cmake_minimum_required(VERSION 2.8.9)
project (firsttry)

include_directories (include)
file (GLOB SOURCES "src/*.C")

#find_package(Boost 1.54 COMPONENTS program_options REQUIRED)
add_executable(first_try ${SOURCES})
target_link_libraries(first_try boost_program_options)
