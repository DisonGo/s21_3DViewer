set(LIB_NAME SOIL)
AUX_SOURCE_DIRECTORY(./src SOIL_SRCS)
AUX_SOURCE_DIRECTORY(./src/original SOIL_SRCS)
file(GLOB_RECURSE SOIL_HEADERS
    includes/*.h
)
add_library(${LIB_NAME} STATIC
    ${SOIL_SRCS}
    ${SOIL_HEADERS}
)
target_link_libraries(SOIL ${OPENGL_LIBRARIES})
target_include_directories(${LIB_NAME} PUBLIC includes)