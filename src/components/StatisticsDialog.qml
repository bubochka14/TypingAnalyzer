import QtQuick
import QtQuick.Window
import QtQuick.Controls 6.2
import QtQuick.Layouts
import KeyboardAnalyzer

Dialog {
    id: root
    width: 400
    height: 500
    function show(rates) {
        stats.rates = rates
        root.show()
    }
    ColumnLayout {
        anchors.fill: parent
        WpmStatistics {
            Layout.fillHeight: true
            Layout.fillWidth: true
            id: stats
        }
        Button {
            text: qsTr("Awesome!")
            focus: true
            onClicked: root.close()
        }
    }
}
