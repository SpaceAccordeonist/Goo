cmake_minimum_required(VERSION 3.15)
project(Goo)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules/SFML/lib/cmake/SFML
        ${CMAKE_MODULE_PATH})
set(CMAKE_CXX_STANDARD 14)

add_executable(Goo main.cpp Game.cpp)

set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML COMPONENTS graphics window system)
target_link_libraries(Goo sfml-graphics sfml-window sfml-system )