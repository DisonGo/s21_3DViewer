AUX_SOURCE_DIRECTORY(./src CALC_SRCS)
set(CALC_HEADERS
    include/mainframe.h
    include/styleloader.h
    include/graphcontroler.h
)
set(CALC_UIS
    UI/mainframe.ui
)
set(CALC_RES
    resources/style.qss
    resources/resources.qrc
)
set(CMAKE_AUTOUIC_SEARCH_PATHS ./UI)
set(PROJECT_SOURCES
    ${CALC_SRCS}
    ${CALC_HEADERS}
    ${CALC_UIS}
    ${CALC_RES}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(SmartCalc_QT
        MANUAL_FINALIZATION
        MACOSX_BUNDLE   
        ${SmartCalc_QT_ICON}
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(SmartCalc_QT SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(SmartCalc_QT
            ${PROJECT_SOURCES}
        )
    endif() 
endif()

target_link_libraries(SmartCalc_QT PUBLIC
    polish_notation
    custom_plot
    credit
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Charts
    Qt${QT_VERSION_MAJOR}::PrintSupport
)

target_include_directories(SmartCalc_QT PUBLIC 
    ./include
)
set_target_properties(SmartCalc_QT PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    WIN32_EXECUTABLE TRUE
)
