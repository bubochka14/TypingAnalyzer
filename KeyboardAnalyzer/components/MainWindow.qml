import QtQuick
import QtQuick.Window
import QtQuick.Controls 6.2
import QtQuick.Layouts
import "components_ui"

ApplicationWindow {
    id: root
    header: Rectangle {
        id: header
        height:50
        MenuButton
        {
            id:menuBtn
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            onClicked: drawer.open()
        }
        Component.onCompleted:
        {
            console.log(typeof TimeFocusModel)
        }
    }

    background: Rectangle {
        color: "grey"
    }
    MenuPage {
        id: drawer
        width: root.width * 0.4
        height: root.height
        onTimeFocusSelected: stack.currentIndex =0
        onFreeModeSelected: stack.currentIndex =1
        onSettingsClicked: stack.currentIndex =2
    }
    StackLayout {
        id: stack
        anchors.fill: parent
        ColumnLayout {
            Row {
                Label {
                    text: qsTr("Repeat count: ")
                }
                TextField
                {
                    id: countTf
                    placeholderText: "4"
                    validator: IntValidator{bottom:0; top: 9}
                }
            }
            Row {
                Label {
                    text: qsTr("Work duration: ")
                }
                TextField
                {
                    id: workDurationTf
                    placeholderText: "00:00"
                    inputMask: "99:99"
                }
            }
            Row {
                Label {
                    text: qsTr("Break duration: ")
                }
                TextField
                {
                    id: breakDurationTf
                    placeholderText: "00:00"
                    inputMask: "99:99"
                }
            }
            Button{
                id: okButton
                text: qsTr("Accept")
            }

            Typewriter {
                height:200
                width: 200

            }
        }
       FreeModePage
       {
           id:freeModePage
       }
    }
}
