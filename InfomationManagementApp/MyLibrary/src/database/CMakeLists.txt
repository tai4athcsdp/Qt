add_library(LibraryDB STATIC
    databasemanager.h
    databasemanager.cpp
    # databaseworker.cpp
)
target_link_libraries(LibraryDB PRIVATE Qt6::Sql Qt6::Core)
target_include_directories(LibraryDB PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
