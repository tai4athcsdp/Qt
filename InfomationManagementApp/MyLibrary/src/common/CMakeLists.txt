qt_add_qml_module(CommonLib
    STATIC
    URI Common
    VERSION 1.0
    SOURCES
        book.h
)
target_link_libraries(CommonLib PRIVATE Qt6::Core Qt6::Qml)
target_include_directories(CommonLib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
