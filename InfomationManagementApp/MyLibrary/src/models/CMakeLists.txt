qt_add_library(LibraryModels STATIC)

qt_add_qml_module(LibraryModels
    URI Models
    VERSION 1.0
    RESOURCE_PREFIX /qt/qml
    SOURCES
        bookmodel.h
        bookmodel.cpp
)

target_link_libraries(LibraryModels PRIVATE Qt6::Core Qt6::Quick)
target_include_directories(LibraryModels PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
