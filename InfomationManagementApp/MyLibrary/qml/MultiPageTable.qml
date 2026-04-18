import QtQuick.Layouts
import QtQuick

Rectangle {
    id: root
    property bool hasTableName: true
    property string tableName: ""
    property real tableNameHeightRatio: hasTableName ? 0.05 : 0
    property real tableFooterRatio: 0.05
    property real tableContentRatio: 1 - tableNameHeightRatio - tableFooterRatio
    border {
        color: "green"
        width: 1
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        CustomLabel {
            id: tableName
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.preferredHeight: root.tableNameHeightRatio
            text: root.tableName
        }

        ListView {
            id: tableContent
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.preferredHeight: root.tableContentRatio
            model: 1
            delegate: Rectangle {
                width: tableContent.width
                height: tableContent.height
                color: "red"
                opacity: 0.3
            }
        }

        Rectangle {
            id: tableFooter
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.preferredHeight: root.tableFooterRatio
            border {
                color: "red"
                width: 1
            }
        }

    }
}
