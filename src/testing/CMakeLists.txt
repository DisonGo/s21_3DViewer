AUX_SOURCE_DIRECTORY(./ TEST_SOURCES)
add_executable(TESTING
    ${TEST_SOURCES}
)
target_link_libraries(TESTING
    godison
    Qt${QT_VERSION_MAJOR}::Gui
)
# set_target_properties(TESTING PROPERTIES
#     # WIN32_EXECUTABLE TRUE
# )