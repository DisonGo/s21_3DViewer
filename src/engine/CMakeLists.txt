
AUX_SOURCE_DIRECTORY(./src/EngineObjects ENGINE_SRCS)
AUX_SOURCE_DIRECTORY(./src/GL_Objects ENGINE_SRCS)
AUX_SOURCE_DIRECTORY(./src/Shaders ENGINE_SRCS)
AUX_SOURCE_DIRECTORY(./src/Parsers ENGINE_SRCS)
AUX_SOURCE_DIRECTORY(./src/Spacers ENGINE_SRCS)
AUX_SOURCE_DIRECTORY(./src ENGINE_SRCS)
set(LIB_NAME engine)
set(ENGINE_HEADER
    includes/Engine.h
    includes/E/Mesh.h
    includes/E/Camera.h
    includes/E/EObject.h
    includes/E/Transform.h
    includes/E/Object3D.h

    includes/GL/GLObject.h
    includes/GL/GLArray.h
    includes/GL/GLBuffer.h
    includes/GL/EBO.h
    includes/GL/VBO.h
    includes/GL/VAO.h

    includes/Spacers/CameraSpacer.h

    includes/Shader.h
    includes/ObjParser.h

    includes/Types/Face.h
    includes/Types/FaceVertex.h
    includes/Types/Normal.h
    includes/Types/OBJ.h
    includes/Types/TextureCoord.h   
    includes/Types/TriangleFace.h
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
