cmake_minimum_required(VERSION 3.16)

project(LibrarySystem VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(QT_QML_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/qt/qml")
set(QT_QML_GENERATE_QMLLS_INI ON)

# 1. Tìm Qt
find_package(Qt6 REQUIRED COMPONENTS Core Quick Sql)
qt_policy(SET QTP0004 NEW)

# 2. Tải Google Test (GTest)
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.14.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# 3. Tạo Target thực thi trước (Đổi tên để tránh trùng với tên QML module/Project)
set(MAIN_APP_EXE "MyLibraryApp")

add_executable(${MAIN_APP_EXE}
    main.cpp
)

# 4. Thêm QML Module vào Target đã tạo
# RESOURCE_PREFIX định nghĩa đường dẫn trong qrc. URI định nghĩa namespace.
qt_add_qml_module(${MAIN_APP_EXE}
    URI LibraryApp
    VERSION 1.0
    RESOURCE_PREFIX /qt/qml
    QML_FILES
        qml/Main.qml
        qml/AllBookScreen.qml qml/AppIndicator.qml qml/CustomLabel.qml qml/MultiPageTable.qml qml/TextButton.qml
        qml/SideBar.qml
    RESOURCES
        assets/icons/ic_home.svg
        assets/icons/ic_settings.svg
        assets/icons/ic_book.svg
        assets/images/app_bkg.png
        assets/images/app_bkg2.png
)

# 5. Thêm các lớp logic (Tạm thời gom vào đây hoặc dùng subdirectories)
add_subdirectory(src/database)
add_subdirectory(src/logic)
add_subdirectory(src/models)
add_subdirectory(src/controllers)

# 6. Bật Unit Test
enable_testing()
add_subdirectory(tests)

# 7. Liên kết thư viện
target_link_libraries(${MAIN_APP_EXE} PRIVATE
    Qt6::Core
    Qt6::Quick
    Qt6::Sql
    LibraryDB
    LibraryLogicplugin
    LibraryModels
    ControllerLibplugin

)
