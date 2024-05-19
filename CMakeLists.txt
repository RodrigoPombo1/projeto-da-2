cmake_minimum_required(VERSION 3.26)
project(projeto_da_2)

set(CMAKE_CXX_STANDARD 17)

add_executable(projeto_da_2 main.cpp
        source/menu.cpp
        source/menu.h
        source/request.cpp
        source/request.h
        source/csv_reader.cpp
        source/csv_reader.h
        source/node.h
        source/node.cpp
)

include_directories(source)
