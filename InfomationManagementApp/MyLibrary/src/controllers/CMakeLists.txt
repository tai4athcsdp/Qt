
qt_add_library(ControllerLib STATIC)
qt_add_qml_module(ControllerLib
    URI Controller
    VERSION 1.0
    RESOURCE_PREFIX /qt/qml
    SOURCES
        screencontroller.h
        screencontroller.cpp
)
target_link_libraries(ControllerLib PRIVATE Qt6::Core Qt6::Qml)
