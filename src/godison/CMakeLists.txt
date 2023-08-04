set(LIB_NAME godison)
AUX_SOURCE_DIRECTORY(./src GODISON_SRCS)
file(GLOB_RECURSE GODISON_HEADERS
    includes/*.h
)
add_library(${LIB_NAME} STATIC
    ${GODISON_SRCS}
    ${GODISON_HEADERS}
)
target_include_directories(${LIB_NAME} PUBLIC includes)