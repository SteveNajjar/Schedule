
cmake_minimum_required(VERSION 3.16)

project(GroceryProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(GroceryProject
    FrontEnd/main.cpp
    FrontEnd/MainWindow.cpp
    FrontEnd/MainWindow.h
    BackEnd/source.cpp
    BackEnd/source.h
    BackEnd/Checker.h
    BackEnd/GMC.h
    BackEnd/CourtesyClerk.h
    BackEnd/Helper.h
)

target_compile_definitions(GroceryProject PRIVATE
    QT_FRONTEND_BUILD
)

target_include_directories(GroceryProject PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/FrontEnd"
    "${CMAKE_CURRENT_SOURCE_DIR}/BackEnd"
)

target_link_libraries(GroceryProject PRIVATE Qt6::Widgets)

