cmake_minimum_required(VERSION 3.22)
project(PATHYS)

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_RELEASE_LIBS ON)

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_RELEASE_LIBS ON)

if(MSVC)
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
    set(Boost_USE_STATIC_RUNTIME ON)
    set(Boost_DIR "lib/Boost/lib/cmake/Boost-1.80.0")

elseif(MSVC)
    set(Boost_DIR lib/Boost/lib/cmake/Boost-1.80.0)
endif (MSVC)

find_package(Boost 1.80.0 COMPONENTS json serialization REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

set(Qt6_DIR C:/Qt/6.4.1/msvc2019_64/lib/cmake/Qt6)
set(Qt6GuiTools_DIR C:/Qt/6.4.1/msvc2019_64/lib/cmake/Qt6GuiTools)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
qt_standard_project_setup()

add_executable(PATHYS main.cpp classes/Compte.cpp classes/Compte.h classes/Client.cpp classes/Client.h)

target_link_libraries (PATHYS LINK_PUBLIC ${Boost_LIBRARIES})
target_link_libraries (PATHYS PRIVATE Qt6::Widgets)