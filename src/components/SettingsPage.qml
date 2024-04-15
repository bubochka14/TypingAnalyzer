import QtQuick
import QtQuick.Window
import QtQuick.Controls 6.2
import QtQuick.Layouts
import KeyboardAnalyzer

Page {
    id: root
    property list<AbstractAppSetting> appSettings: settingsPage.settings
    padding: 15
    ListView {
        anchors.fill: parent
        model: appSettings
        delegate: RowLayout {
            id: delegateRow
            Layout.alignment: Qt.AlignVCenter
            spacing: 10
            Text {
                id: nameTxt
                text: name
            }
            Component.onCompleted: delegateRow.children.push(appSettings[index].getContent())
        }
    }
}
