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
set(CURRENT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_CXX_FLAGS "-Wall -Wextra -DMYPATH=${CMAKE_SOURCE_DIR}")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
# add_definitions(-DSTB_IMAGE_IMPLEMENTATION)
#-DMYPATH=" ${CMAKE_SOURCE_DIR}
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
FetchContent_Declare(
  godison
  GIT_REPOSITORY https://github.com/DisonGo/godison.git
  GIT_TAG        main
)
FetchContent_MakeAvailable(godison)
enable_testing()
include_directories(${GTEST_INCLUDE_DIR})
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets OpenGL OpenGLWidgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets OpenGL OpenGLWidgets)


add_subdirectory(3D_Viewer)
add_subdirectory(engine)
add_subdirectory(gifImage)
add_subdirectory(widgets)
add_subdirectory(testing)
add_subdirectory(soil)

