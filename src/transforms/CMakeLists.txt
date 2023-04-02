AUX_SOURCE_DIRECTORY(./src TRANSFORMS_SRCS)
set(LIB_NAME transforms)
set(TRANSFORMS_HEADER
    includes/transforms.h
)
add_library(${LIB_NAME} STATIC
    ${TRANSFORMS_SRCS}
    ${TRANSFORMS_HEADER}
)
target_include_directories(${LIB_NAME} PUBLIC includes)
