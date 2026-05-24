pragma ComponentBehavior: Bound
import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

RowLayout {
    id: root

    property int currentPage: 1
    property int totalPage: 10

    spacing: 10

    Button {
        id: prevBtn

        Layout.fillHeight: true
        Layout.preferredWidth: height
        text: "Trước"

        onClicked: {}

        font {
            bold: true
            pixelSize: 12
        }
    }
    Rectangle {
        Layout.fillHeight: true
        Layout.fillWidth: true
        color: "transparent"

        border {
            color: "green"
            width: 1
        }
        Text {
            anchors.fill: parent
            horizontalAlignment: Text.AlignHCenter
            text: root.currentPage + " / " + root.totalPage
            verticalAlignment: Text.AlignVCenter

            font {
                pixelSize: 20
            }
        }
    }
    Button {
        id: afterBtn

        Layout.fillHeight: true
        Layout.preferredWidth: height
        text: "Sau"

        onClicked: {}

        font {
            bold: true
            pixelSize: 12
        }
    }
}
