import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

import Controller as Controller

Rectangle {
    id: root

    enum BtnId {
        HOME,
        ALLBOOK,
        SETTING
    }

    color: Qt.color("#163d44")
    height: parent.height
    width: parent.width / 6

    ColumnLayout {
        id: layout

        anchors.centerIn: root
        height: implicitHeight
        spacing: 10
        width: root.width

        Repeater {
            id: listBtnRepeater

            delegate: Button {
                id: btnDelegate

                required property int btnId
                required property string iconSrc
                required property string name

                Layout.fillWidth: true
                Layout.preferredHeight: 50
                text: btnDelegate.name

                onClicked: internal.handleBtnClicked(btnId)

                font {
                    bold: true
                    pixelSize: 18
                }
                icon {
                    height: btnDelegate.height * 3 / 4
                    source: Qt.resolvedUrl(btnDelegate.iconSrc)
                    width: height
                }
            }
            model: ListModel {
                ListElement {
                    btnId: SideBar.BtnId.HOME
                    iconSrc: "qrc:/qt/qml/LibraryApp/assets/icons/ic_home.svg"
                    name: qsTr("Trang chủ")
                }
                ListElement {
                    btnId: SideBar.BtnId.ALLBOOK
                    iconSrc: "qrc:/qt/qml/LibraryApp/assets/icons/ic_book.svg"
                    name: qsTr("Tất cả sách")
                }
                ListElement {
                    btnId: SideBar.BtnId.SETTING
                    iconSrc: "qrc:/qt/qml/LibraryApp/assets/icons/ic_settings.svg"
                    name: qsTr("Cài đặt")
                }
            }
        }
    }
    QtObject {
        id: internal

        function handleBtnClicked(btnId: int): void {
            switch (btnId) {
            case SideBar.BtnId.HOME:
                Controller.ScreenController.changeCurrentScreen(Controller.ScreenController.ScreenId.Home);
                break;
            case SideBar.BtnId.ALLBOOK:
                Controller.ScreenController.changeCurrentScreen(Controller.ScreenController.ScreenId.AllBook);
                break;
            case SideBar.BtnId.SETTING:
                Controller.ScreenController.changeCurrentScreen(Controller.ScreenController.ScreenId.Setting);
                break;
            default:
                break;
            }
        }
    }
}
