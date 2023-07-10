AUX_SOURCE_DIRECTORY(./DrawConfig WIDGETS_SRCS)
AUX_SOURCE_DIRECTORY(./CameraConfig WIDGETS_SRCS)
AUX_SOURCE_DIRECTORY(./TransformConfig WIDGETS_SRCS)
AUX_SOURCE_DIRECTORY(./MeshConfig WIDGETS_SRCS)
AUX_SOURCE_DIRECTORY(./Object3DConfig WIDGETS_SRCS)
AUX_SOURCE_DIRECTORY(./ WIDGETS_SRCS)
set(LIB_NAME widgets)
set(CMAKE_AUTOUIC_SEARCH_PATHS ./UI)
set(WIDGETS_HEADER
    includes/DrawConfig/DrawConfigView.h
    includes/MeshConfig/MeshConfigView.h
    includes/CameraConfig/CameraConfigView.h
    includes/Object3DConfig/Object3DConfigView.h
    includes/TransformConfig/TransformConfigView.h
    includes/TripletWidget.h
)
set(WIDGETS_UIS
    UI/TripletWidget.ui
    UI/Object3DConfigView.ui
    UI/MeshConfigView.ui
    UI/DrawConfigView.ui
    UI/CameraConfigView.ui
    UI/TransformConfigView.ui
)
add_library(${LIB_NAME} SHARED
    ${WIDGETS_UIS}
    ${WIDGETS_SRCS}
    ${WIDGETS_HEADER}
)
target_link_libraries(${LIB_NAME} PRIVATE
    engine
    Qt${QT_VERSION_MAJOR}::Widgets
)
target_include_directories(${LIB_NAME} PUBLIC includes)
