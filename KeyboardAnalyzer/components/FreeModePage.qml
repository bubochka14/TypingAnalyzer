import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Page {
    id: root
    states:[
        State{
            name: "stopped"; when: pauseBtn.pressed  || finishBtn.pressed
            PropertyChanges { target: startBtn; enabled: true }
            PropertyChanges { target: pauseBtn; enabled: false }
            PropertyChanges { target: finishBtn; enabled: false }
        },
        State{
            name: "enrolling"; when: startBtn.pressed
            PropertyChanges { target: startBtn; enabled: false }
            PropertyChanges { target: pauseBtn; enabled: true }
            PropertyChanges { target: finishBtn; enabled: true }
        }

    ]
    ColumnLayout {
        anchors.fill: parent
        WPMChart {
            Layout.fillHeight: true
            Layout.fillWidth: true
            id: chart
        } Row{
            Layout.alignment: Qt.AlignHCenter
            Button {
                id: startBtn
                text: qsTr("Start")
            }
            Button{
                id: pauseBtn
                enabled: false
                text: qsTr("Pause")
            }
            Button{
                id: finishBtn
                enabled: false
                text: qsTr("Finish")
            }
        }
    }
}
