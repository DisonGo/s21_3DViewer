AUX_SOURCE_DIRECTORY(./src/Controllers ENGINE_SRCS)
AUX_SOURCE_DIRECTORY(./src/Geometry ENGINE_SRCS)
AUX_SOURCE_DIRECTORY(./src/Objects ENGINE_SRCS)
AUX_SOURCE_DIRECTORY(./src/Shaders ENGINE_SRCS)
AUX_SOURCE_DIRECTORY(./src/Parsers ENGINE_SRCS)
set(LIB_NAME engine)
set(ENGINE_HEADER
    includes/buffers.h
    includes/opengl_helper.h
    includes/engine.h
    includes/mesh.h
    includes/camera.h
    includes/EBO.h
    includes/VAO.h
    includes/VBO.h
    includes/shader.h
    includes/ObjParser.h

    includes/Types/Face.h
    includes/Types/FaceVertex.h
    includes/Types/Normal.h
    includes/Types/OBJ.h
    includes/Types/TextureCoord.h   
    includes/Types/Transform.h
    includes/Types/Vertex.h
    includes/Types/VertexColor.h
    includes/Types/VertexData.h
)
add_library(${LIB_NAME} STATIC
    ${ENGINE_SRCS}
    ${ENGINE_HEADER}
)
target_link_libraries(${LIB_NAME} PRIVATE
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::OpenGL
    Qt${QT_VERSION_MAJOR}::OpenGLWidgets
)
target_include_directories(${LIB_NAME} PUBLIC includes)
