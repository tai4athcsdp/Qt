
qt_add_qml_module(ControllerLib
    STATIC
    URI Controller
    VERSION 1.0
    SOURCES
        screencontroller.h
        screencontroller.cpp
)
target_link_libraries(ControllerLib PRIVATE Qt6::Core Qt6::Qml)
target_include_directories(ControllerLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
