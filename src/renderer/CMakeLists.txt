AUX_SOURCE_DIRECTORY(./src RENDERER_SRCS)
set(LIB_NAME renderer)
set(RENDERER_HEADER
    includes/obj_parser.h
    includes/parser_types.h
    includes/points_parser.h
    includes/vertex_parser.h
)
add_library(${LIB_NAME} STATIC
    ${RENDERER_SRCS}
    ${RENDERER_HEADER}
)
target_include_directories(${LIB_NAME} PUBLIC includes)
