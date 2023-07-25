cmake_minimum_required(VERSION 3.16)

project(3D_Viewer VERSION 1.0.0 LANGUAGES CXX C)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../exe)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()
set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")


find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets OpenGL OpenGLWidgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets OpenGL OpenGLWidgets)


add_subdirectory(qt_app)
add_subdirectory(engine)
add_subdirectory(gifImage)
add_subdirectory(widgets)
add_subdirectory(godison)
add_subdirectory(testing)

