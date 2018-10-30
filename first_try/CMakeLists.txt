cmake_minimum_required(VERSION 2.8.9)
project (firsttry)

macro(use_cxx11)
  if (CMAKE_VERSION VERSION_LESS "3.1")
    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
      set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
    endif ()
  else ()
    set (CMAKE_CXX_STANDARD 11)
  endif ()
endmacro(use_cxx11)

use_cxx11()

#set (CMAKE_CXX_STANDARD 11)
include_directories (include)
file (GLOB SOURCES "src/*.C")

#find_package(Boost 1.54 COMPONENTS program_options REQUIRED)
add_executable(first_try ${SOURCES})
target_link_libraries(first_try boost_program_options)
