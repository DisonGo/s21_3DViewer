AUX_SOURCE_DIRECTORY(./tests TEST_SOURCES)
add_executable(TESTING
    ${TEST_SOURCES}
)
AUX_SOURCE_DIRECTORY(./src VIEWER_SRCS)
file(GLOB_RECURSE VIEWER_HEADERS
    includes/*.h
)

target_link_libraries(TESTING
    engine
    godison
    GTest::gtest_main
    Qt${QT_VERSION_MAJOR}::Gui
)
include(GoogleTest)
gtest_discover_tests(TESTING)
add_test(NAME TestMyCode COMMAND TestMyCode)
