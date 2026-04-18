import QtQuick
import QtQuick.Layouts

Column {
    id: listBookScreenColumn
    anchors {
        fill: parent
        margins: 10
    }
    spacing: 0

    CustomLabel {
        id: listBookScreenTitle
        text: "Quản lý sách"
        labelPointSize: 13
    }

    Item {
        width: listBookScreenColumn.width
        height: 10
    }

    AppIndicator {id: indicator}

    Item {
        width: listBookScreenColumn.width
        height: 10
    }

    MultiPageTable {
        width: listBookScreenColumn.width
        height: listBookScreenColumn.height - 10 * 2 - listBookScreenTitle.height - indicator.height
        tableName: "Tất cả sách"
    }





}
