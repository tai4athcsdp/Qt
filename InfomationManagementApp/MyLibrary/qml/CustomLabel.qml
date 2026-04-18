import QtQuick
import QtQuick.Controls

Label {
    id: root

    property color labelBackGroundColor: "transparent"//"#dad7cd"
    property int labelPointSize: 12
    property bool isBoldLabel: true

    verticalAlignment: Text.AlignVCenter
    horizontalAlignment: Text.AlignHCenter
    background: Rectangle {
        color: root.labelBackGroundColor
    }
    font {
        pointSize: root.labelPointSize
        bold: root.isBoldLabel
    }
}
