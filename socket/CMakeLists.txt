cmake_minimum_required(VERSION 3.20)

project(cir2_socket2)

set (CMAKE_CXX_STANDARD 17)
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_RELEASE_LIBS ON)

if(MSVC)
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
    add_compile_definitions(_WIN32_WINNT=0x0501)
    set(Boost_USE_STATIC_RUNTIME ON)
    add_compile_options($<$<CONFIG:Release>:/MT> # Runtime library: Multi-threaded
                      $<$<CONFIG:Debug>:/MTd> # Runtime library: Multi-threaded Debug
                      )
    set(Boost_DIR "C:/tools/Boost/lib/cmake/Boost-1.80.0")
elseif(MSVC)
    set(Boost_DIR /usr/local/lib/cmake/Boost-1.80.0)
endif (MSVC)

find_package(Boost 1.80.0 COMPONENTS system thread regex serialization REQUIRED)
#include_directories(${Boost_INCLUDE_DIRS} ../thread)
#link_directories(${Boost_LIBRARY_DIRS})

set(socket_src socket.cpp socket_tools.cpp)
add_executable(socket ${socket_src})
target_link_libraries (socket LINK_PUBLIC customer ${Boost_LIBRARIES})