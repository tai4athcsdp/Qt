import QtQuick
import QtQuick.Layouts
import Logic

Rectangle {
    id: root

    anchors.fill: parent
    color: Qt.color("#f6f8f9")

    ColumnLayout {
        id: screenLayout

        anchors.centerIn: root
        height: root.height
        spacing: 10
        width: root.width - 40

        Rectangle {
            id: screenTitleContainer

            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.preferredHeight: 0.1
            color: "transparent"
            opacity: 0.5

            border {
                color: "green"
                width: 1
            }
            CustomLabel {
                id: screenTitle

                anchors.verticalCenter: parent.verticalCenter
                labelPointSize: 18
                text: qsTr("Tất cả sách")
            }
        }
        Rectangle {
            id: filterArea

            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.preferredHeight: 0.1
            color: "red"
            opacity: 0.5

            border {
                color: "green"
                width: 1
            }
        }
        Rectangle {
            id: allBookTableArea

            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.preferredHeight: 0.7
            color: Qt.color("transparent")
            radius: 10

            border {
                color: "green"
                width: 1
            }
            ListView {
                id: allBookListView

                clip: true
                headerPositioning: ListView.OverlayHeader
                model: BookManager.bookModel
                spacing: 0

                delegate: Rectangle {
                    id: allBookDele

                    required property string author
                    required property int bookId
                    required property string title

                    color: Qt.color("transparent")
                    height: 50
                    opacity: 0.5
                    width: parent.width

                    border {
                        color: "red"
                        width: 1
                    }
                    RowLayout {
                        anchors.fill: parent

                        CustomLabel {
                            id: titleLabel

                            Layout.alignment: Qt.AlignHCenter
                            Layout.fillWidth: true
                            Layout.preferredWidth: 1
                            isBoldLabel: true
                            text: allBookDele.title
                        }
                        CustomLabel {
                            id: authorLabel

                            Layout.alignment: Qt.AlignHCenter
                            Layout.fillWidth: true
                            Layout.preferredWidth: 0.3
                            isBoldLabel: true
                            text: allBookDele.author
                        }
                    }
                }
                header: Rectangle {
                    color: Qt.color("#e3f2f5")
                    height: 50
                    width: parent.width
                    z: 3

                    RowLayout {
                        anchors.fill: parent

                        Repeater {
                            id: headerRepeater

                            model: [
                                {
                                    name: qsTr("Tiêu đề"),
                                    widthRatio: 1
                                },
                                {
                                    name: qsTr("Tác giả"),
                                    widthRatio: 0.3
                                }
                            ]

                            delegate: CustomLabel {
                                required property string name
                                required property double widthRatio

                                Layout.alignment: Qt.AlignHCenter
                                Layout.fillWidth: true
                                Layout.preferredWidth: widthRatio
                                isBoldLabel: true
                                text: name
                            }
                        }
                    }
                }

                anchors {
                    fill: parent
                    margins: 5
                }
            }
        }
        Rectangle {
            id: pageNaviArea

            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.preferredHeight: 0.1
            color: "red"
            opacity: 0.5

            border {
                color: "green"
                width: 1
            }
        }
    }
}
