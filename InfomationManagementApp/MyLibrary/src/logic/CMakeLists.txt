qt_add_qml_module(LibraryLogic
    STATIC
    URI Logic
    VERSION 1.0
    SOURCES
        bookmanager.h
        bookmanager.cpp
    DEPENDENCIES
        Models
)
target_link_libraries(LibraryLogic PRIVATE Qt6::Core Qt6::Qml LibraryModels)
