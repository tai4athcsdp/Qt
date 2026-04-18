add_library(LibraryModels STATIC
    # bookmodel.cpp
)
target_link_libraries(LibraryModels PRIVATE Qt6::Core Qt6::Quick LibraryLogic)
target_include_directories(LibraryModels PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
