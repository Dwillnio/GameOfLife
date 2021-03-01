cmake_minimum_required(VERSION 3.5)

project(GameOfLife LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Widgets Charts REQUIRED)

include_directories(
    .
)

add_executable(GameOfLife
    main.cpp

    game.cpp
    game.h

    window.cpp
    window.h

    rule.cpp
    rule.h
)

target_link_libraries(GameOfLife Qt5::Widgets Qt5::Charts)
