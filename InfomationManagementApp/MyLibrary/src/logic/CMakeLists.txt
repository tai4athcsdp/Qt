qt_add_library(LibraryLogic STATIC)

set_target_properties(LibraryLogic PROPERTIES AUTOMOC ON)

qt_add_qml_module(LibraryLogic
    URI Logic
    VERSION 1.0
    RESOURCE_PREFIX /qt/qml
    SOURCES
        bookmanager.h
        bookmanager.cpp
    DEPENDENCIES
        Models

)
target_link_libraries(LibraryLogic PRIVATE Qt6::Core Qt6::Qml LibraryModels)
target_include_directories(LibraryLogic PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
