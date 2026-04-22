import QtQuick
import Controller

Window {
    id: root

    flags: Qt.Window | Qt.WindowFullscreenButtonHint
    height: 1080
    title: qsTr("THƯ VIỆN SÁCH")
    visibility: Window.Windowed
    visible: true
    width: 1920

    Image {
        id: appBkg

        anchors.fill: parent
        fillMode: Image.PreserveAspectFit
        source: Qt.resolvedUrl("qrc:/qt/qml/LibraryApp/assets/images/app_bkg.png")
    }
    SideBar {
        id: sideBar

    }
    Loader {
        id: contentLoader

        function getSource(): url {
            let url = Qt.resolvedUrl("");
            switch (ScreenController.currentScreen) {
            case (ScreenController.ScreenId.Home):
                break;
            case (ScreenController.ScreenId.AllBook):
                url = Qt.resolvedUrl("qrc:/qt/qml/LibraryApp/qml/AllBookScreen.qml");
                break;
            case (ScreenController.ScreenId.Setting):
                break;
            }
            return url;
        }

        source: getSource()

        anchors {
            bottom: parent.bottom
            left: sideBar.right
            right: parent.right
            top: parent.top
        }
    }
}
