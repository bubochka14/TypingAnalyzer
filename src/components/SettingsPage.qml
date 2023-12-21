import QtQuick
import QtQuick.Window
import QtQuick.Controls 6.2
import QtQuick.Layouts

MainWindowPage{
    id: root
    name: "Setting"
    iconSource: Qt.resolvedUrl("icons/settings")

    padding:15
    ColumnLayout
    {
        anchors.left:parent.left
        anchors.right: parent.right
        id:cLayout
        spacing:10
        RowLayout{
            spacing:20
            Layout.fillWidth: true
            Label
            {
                text: qsTr("Keyboard sounds volume")
                Layout.alignment: Qt.AlignLeft


            }

            Slider
            {
                id: slider
                value:100
                from: 0
                to: 100
                stepSize: 5
                Layout.alignment: Qt.AlignRight
            }
            Label
            {
                text:slider.value
            }
        }
        RowLayout {
            spacing:20
            Layout.fillWidth: true

            Label
            {
                text: qsTr("Language")
                Layout.alignment: Qt.AlignLeft


            }
            ComboBox
            {
                model:["English","Russian"]
                Layout.alignment: Qt.AlignRight

            }
        }
        Label
        {
            text: ":)"
        }
    }
}
