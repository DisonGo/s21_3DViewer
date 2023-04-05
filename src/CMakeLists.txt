cmake_minimum_required(VERSION 3.16)

project(3D_Viewer VERSION 1.0.0 LANGUAGES CXX C)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../exe)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets OpenGL OpenGLWidgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets OpenGL OpenGLWidgets)


add_subdirectory(qt_app)
add_subdirectory(obj_parser)
add_subdirectory(engine)
add_subdirectory(transforms)
add_subdirectory(gifImage)

#C:\gits\3D_Viewer\src\CMakeLists.txt:14: error: Found package configuration file: D:/Qt/qtbase/lib/cmake/Qt6/Qt6Config.cmake but it set Qt6_FOUND to FALSE so package "Qt6" is considered to be NOT FOUND.  Reason given by package: Failed to find required Qt component "GifImage". Expected Config file at "D:/Qt/qtbase/lib/cmake/Qt6GifImage/Qt6GifImageConfig.cmake" does NOT exist
