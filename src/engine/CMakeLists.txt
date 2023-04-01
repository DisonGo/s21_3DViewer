AUX_SOURCE_DIRECTORY(./src/Controllers ENGINE_SRCS)
AUX_SOURCE_DIRECTORY(./src/Geometry ENGINE_SRCS)
AUX_SOURCE_DIRECTORY(./src/Objects ENGINE_SRCS)
AUX_SOURCE_DIRECTORY(./src/Shaders ENGINE_SRCS)
set(LIB_NAME engine)
set(ENGINE_HEADER
    includes/buffers.h
    includes/opengl_helper.h
    includes/engine.h
    includes/camera.h
    includes/EBO.h
    includes/VAO.h
    includes/VBO.h
    includes/shader.h
)
add_library(${LIB_NAME} STATIC
    ${ENGINE_SRCS}
    ${ENGINE_HEADER}
)
target_link_libraries(${LIB_NAME} PRIVATE
    obj_parser
    Qt${QT_VERSION_MAJOR}::OpenGL
    Qt${QT_VERSION_MAJOR}::OpenGLWidgets
)
target_include_directories(${LIB_NAME} PUBLIC includes)
