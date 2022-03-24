cmake_minimum_required(VERSION 3.8)
project(Goo)

set(SFML_DIR ${CMAKE_SOURCE_DIR}/cmake/modules/SFML/lib/cmake/SFML)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules/SFML/lib/cmake/SFML) #${CMAKE_MODULE_PATH})
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -std=c++11)

set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML 2.5.1 REQUIRED COMPONENTS graphics window system )

add_executable(Goo main.cpp Game.cpp)

target_link_libraries(Goo sfml-graphics sfml-window sfml-system)