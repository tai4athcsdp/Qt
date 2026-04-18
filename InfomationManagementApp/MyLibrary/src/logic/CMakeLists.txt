add_library(LibraryLogic STATIC
    # librarysystem.cpp
)
target_link_libraries(LibraryLogic PRIVATE Qt6::Core LibraryDB)
target_include_directories(LibraryLogic PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
