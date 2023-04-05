AUX_SOURCE_DIRECTORY(./src GIF_IMAGE_SRCS)
AUX_SOURCE_DIRECTORY(./3rdParty/giflib GIF_IMAGE_SRCS)
set(LIB_NAME QtGifImage_)
set(GIF_IMAGE_HEADER
    includes/qgifglobal.h
    includes/qgifimage.h
    includes/qgifimage_p.h
)
add_library(${LIB_NAME} SHARED
    ${GIF_IMAGE_SRCS}
    ${GIF_IMAGE_HEADER}
)
target_link_libraries(${LIB_NAME} PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
)
# set_target_properties(${LIB_NAME} PROPERTIES PUBLIC_HEADER includes/qgifimage.)
target_include_directories(${LIB_NAME} PUBLIC includes)
target_include_directories(${LIB_NAME} PRIVATE 3rdParty/giflib)
#include(GNUInstallDirs)
