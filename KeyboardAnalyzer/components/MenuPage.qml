import QtQuick
import QtQuick.Controls

import QtQuick.Layouts

Drawer {
    id: root
    signal freeModeSelected()
    signal timeFocusSelected()
    signal settingsClicked()
    Page {
        id: page
        anchors.fill:parent
        ColumnLayout {
            id: cLayout
            anchors.topMargin: 30
            anchors.top:parent.top
            anchors.right: parent.right
            anchors.left: parent.left
            Button {
                Layout.fillWidth: true
                text: qsTr("Time Focus")
                onClicked: root.timeFocusSelected()
            }
            Button {
                Layout.fillWidth: true
                text: qsTr("Free mode")
                onClicked: root.freeModeSelected()
            }
            Button {
                Layout.fillWidth: true
                text: qsTr("Settings")
                onClicked: root.settingsClicked()
            }
        }
    }
}
