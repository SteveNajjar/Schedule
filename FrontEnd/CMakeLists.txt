cmake_minimum_required(VERSION 3.31)

project(GroceryProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_PREFIX_PATH "/opt/homebrew/opt/qtbase")

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(GroceryProject
    main.cpp
    MainWindow.cpp
    MainWindow.h
)

target_link_libraries(GroceryProject PRIVATE Qt6::Widgets)