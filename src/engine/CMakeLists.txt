
AUX_SOURCE_DIRECTORY(./src/EngineObjects ENGINE_SRCS)
AUX_SOURCE_DIRECTORY(./src/GL_Objects ENGINE_SRCS)
AUX_SOURCE_DIRECTORY(./src/Shaders ENGINE_SRCS)
AUX_SOURCE_DIRECTORY(./src/Parsers ENGINE_SRCS)
AUX_SOURCE_DIRECTORY(./src/Strategies/Import ENGINE_SRCS)
AUX_SOURCE_DIRECTORY(./src/Spacers ENGINE_SRCS)
AUX_SOURCE_DIRECTORY(./src ENGINE_SRCS)
set(LIB_NAME engine)
set(ENGINE_HEADER
    includes/Engine.h
    includes/DrawConfig.h
    includes/E/Mesh.h
    includes/E/Camera.h
    includes/E/EObject.h
    includes/E/Transform.h
    includes/E/Object3D.h
    includes/E/EObjectItemModel.h
    includes/E/EObjectTreeItem.h
    
    includes/GL/GLObject.h
    includes/GL/GLArray.h
    includes/GL/GLBuffer.h
    includes/GL/EBO.h
    includes/GL/VBO.h
    includes/GL/VAO.h

    includes/Strategies/Import/ImportStrategy.h
    includes/Strategies/Import/OBJImportStrategy.h
    includes/Strategies/Import/OBJImportStandartStrategy.h
    includes/Strategies/Import/OBJImportTriangleStrategy.h
    includes/Strategies/Import/OBJImportWireframeStrategy.h

    includes/Spacers/CameraSpacer.h
    includes/Spacers/DrawConfigSpacer.h
    includes/Spacers/TransformSpacer.h

    includes/Shaders/Program.h
    includes/Shaders/Shader.h
    includes/Shaders/VertexShader.h
    includes/Shaders/FragmentShader.h

    includes/Parsers/BaseParser.h
    includes/Parsers/EdgeParser.h
    includes/Parsers/OBJParser.h
    includes/Parsers/TriangleParser.h

    includes/Types/Face.h
    includes/Types/FaceVertex.h
    includes/Types/Normal.h
    includes/Types/OBJ.h
    includes/Types/TriangleOBJ.h
    includes/Types/EdgeOBJ.h
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
