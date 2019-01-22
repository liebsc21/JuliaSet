cmake_minimum_required(VERSION 2.8.9)
project (JuliaSet)

set(CMAKE_CXX_FLAGS "-O3 -Wall -Wextra -std=c++11")

include_directories (include)
file (GLOB SOURCES "src/*.C")

# for laptop
#find_package(Boost 1.54 COMPONENTS program_options REQUIRED)
# for pktfs
link_directories(/cvmfs/sft.cern.ch/lcg/releases/LCG_94/Boost/1.66.0/x86_64-centos7-gcc62-dbg/lib)
include_directories(/cvmfs/sft.cern.ch/lcg/releases/LCG_94/Boost/1.66.0/x86_64-centos7-gcc62-dbg/include)

add_executable(JuliaSet ${SOURCES})
target_link_libraries(JuliaSet boost_program_options)
