add_executable(AppTests test_main.cpp)
target_link_libraries(AppTests PRIVATE
    GTest::gtest_main
    LibraryLogic
    LibraryDB
    Qt6::Core
)

include(GoogleTest)
gtest_discover_tests(AppTests)
