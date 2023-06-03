cmake_minimum_required(VERSION 3.5)

project(PaintTest VERSION 0.1 LANGUAGES CXX)

#set(CMAKE_PREFIX_PATH C:/Qt/6.5.0/mingw_64)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

add_subdirectory(./library)
add_subdirectory(./app)
