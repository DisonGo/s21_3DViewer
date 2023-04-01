AUX_SOURCE_DIRECTORY(./src OBJ_PARSER_SRCS)
set(LIB_NAME obj_parser)
set(OBJ_PARSER_HEADER
    includes/obj_parser.h
    includes/parser_types.h
    includes/sub_functions.h
)
add_library(${LIB_NAME} STATIC
    ${OBJ_PARSER_SRCS}
    ${OBJ_PARSER_HEADER}
)
target_include_directories(${LIB_NAME} PUBLIC includes)
