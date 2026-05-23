add_library(LibraryDB STATIC
    databasemanager.h
    databasemanager.cpp
    bookrepository.h
    bookrepository.cpp
)
target_link_libraries(LibraryDB PRIVATE Qt6::Core CommonLib PUBLIC Qt6::Sql)
target_include_directories(LibraryDB PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
