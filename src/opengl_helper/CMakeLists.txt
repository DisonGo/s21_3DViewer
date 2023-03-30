AUX_SOURCE_DIRECTORY(./src OPENGL_HELPER_SRCS)
set(LIB_NAME opengl_helper)
set(OPENGL_HELPER_HEADER
    includes/Buffers.h
    includes/opengl_helper.h
    includes/EBO.h
    includes/VAO.h
    includes/VBO.h
    includes/shader.h
)
add_library(${LIB_NAME} STATIC
    ${OPENGL_HELPER_SRCS}
    ${OPENGL_HELPER_HEADER}
)
target_link_libraries(${LIB_NAME} PRIVATE
    Qt${QT_VERSION_MAJOR}::OpenGL
)
target_include_directories(${LIB_NAME} PUBLIC includes)
