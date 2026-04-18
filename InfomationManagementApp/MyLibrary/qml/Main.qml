import QtQuick
import QtQuick.Layouts


Window {
    id: root
    width: 1920
    height: 1080
    visible: true
    flags: Qt.Window | Qt.WindowFullscreenButtonHint
    visibility: Window.FullScreen
    title: qsTr("MY LIBRARY")

    ColumnLayout {
        anchors.fill: parent
        spacing: 0
        Item {
            id: appHeader
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.preferredHeight: 0.05
            CustomLabel {
                id: appName
                text: "QLTV"
                height: appHeader.height
                labelPointSize: 15
                labelBackGroundColor: "#dad7cd"
            }

            TextButton {
                id: exitButton
                text: "Thoát"
                width: appHeader.width * 0.05
                height: appHeader.height
                anchors.right: appHeader.right
                onClicked: {
                    root.close()
                }
            }
        }

        Rectangle {
            id: appContent
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.preferredHeight: 0.9
            border {
                color: "green"
                width: 1
            }

            Loader {
                anchors.fill: parent
                sourceComponent: AllBookScreen {

                }
            }


        }

        Rectangle {
            id: appFooter
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.preferredHeight: 0.05
            border {
                color: "green"
                width: 1
            }
        }


    }


}
