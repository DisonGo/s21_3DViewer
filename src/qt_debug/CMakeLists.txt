AUX_SOURCE_DIRECTORY(./src VIEWER_SRCS)
set(VIEWER_HEADERS
    includes/openglcontroller.h
    includes/geometryengine.h
    includes/mainwindow.h
    includes/shader.h
)
set(VIEWER_UIS
    UI/mainwindow.ui
)
set(CMAKE_AUTOUIC_SEARCH_PATHS ./UI)
set(PROJECT_SOURCES
    ${VIEWER_SRCS}
    ${VIEWER_HEADERS}
    ${VIEWER_UIS}
)

set(shaders_resource_files
    "vshader.glsl"
    "fshader.glsl"
)


if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(3D_Viewer
        MANUAL_FINALIZATION
        MACOSX_BUNDLE   
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(3D_Viewer SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(3D_Viewer
            ${PROJECT_SOURCES}
        )
    endif() 
endif()
qt6_add_resources(3D_Viewer "shaders"
    PREFIX
        "/"
    FILES
        ${shaders_resource_files}
)
target_link_libraries(3D_Viewer PUBLIC
    renderer
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::OpenGL
    Qt${QT_VERSION_MAJOR}::OpenGLWidgets
)

target_include_directories(3D_Viewer PUBLIC 
    ./includes
)
set_target_properties(3D_Viewer PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    WIN32_EXECUTABLE TRUE
)
