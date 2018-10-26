# my
cmake_minimum_required(VERSION 2.8.9)
project (firsttry)

find_package(Boost 1.54 COMPONENTS program_options REQUIRED)
add_executable(first_try first_try.C)
SET(liblist boost_program_options)
#target_link_libraries(first_try Boost::program_options)
target_link_libraries(first_try ${liblist})

## Wojtek
#include_directories (
#    include
#    /home/sebastian/boost/boost_1_61_0/boost
#)
#
#link_directories(
#    /home/sebastian/boost/boost_1_61_0/libs
#)
#    
#add_executable(first_try first_try.C)
#
#target_link_libraries(
#    boost_program_options
#)

#cmake_minimum_required(VERSION 2.8)
#set(Boost_INCLUDE_DIR /usr/lib/x86_64-linux-gnu)
#find_package(Boost COMPONENTS system filesystem REQUIRED)
#include_directories(${Boost_INCLUDE_DIR})
#link_directories(${Boost_LIBRARY_DIR})
#
#add_executable(first_try first_try.C)
#target_link_libraries( first_try ${Boost_LIBRARIES} )
