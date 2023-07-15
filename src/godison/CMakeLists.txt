set(LIB_NAME godison)
AUX_SOURCE_DIRECTORY(./src GODISON_SRCS)
set(GODISON_HEADERS
  includes/godison/Shapes.h
  includes/godison/Point.h
  includes/godison/Types.h
  includes/godison/Matrices.h
  includes/godison/Vectors.h
)
add_library(${LIB_NAME} STATIC
    ${GODISON_SRCS}
    ${GODISON_HEADERS}
)
target_include_directories(${LIB_NAME} PUBLIC includes)