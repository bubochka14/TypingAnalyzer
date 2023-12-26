import QtQuick
import QtQuick.Window
import QtQuick.Controls 6.2
import QtQuick.Layouts
import KeyboardAnalyzer

Item {
    id: root
    property alias model: lModel
    property bool inputFieldsVisible: true
    Item {
        id: convert
        function toMiliseconds(h = 0, m = 0, s = 0, ms = 0) {
            return h * 3600000 + m * 60000 + s * 1000 + ms
        }
        function msToStr(mil) {
            var hours = Math.floor(mil / 3600000)
            var mins = Math.floor(mil % 3600000 / 60000)
            var s = mil % 3600000 % 60000 / 1000
            return hours + "h " + mins + "m " + (s ? (s + "s") : "")
        }
    }
    function apply() {
        lModel.clear()
        console.log(workDurationTf.hours, workDurationTf.minuts)
        var workMs = convert.toMiliseconds(workDurationTf.hours,
                                           workDurationTf.minuts)
        var breakMs = convert.toMiliseconds(breakDurationTf.hours,
                                            breakDurationTf.minuts)

        for (var i = 0; i < countTf.text; i++) {
            lModel.append({
                              "type": "work",
                              "duration": workMs,
                              "remainingTime": workMs,
                              "completed": false,
                              "rates": []

                          })
            lModel.append({
                              "type": "break",
                              "duration": breakMs,
                              "remainingTime": breakMs,
                              "completed": false,
                              "rates": []
                          })
        }
    }
    Component.onCompleted: root.apply()
    ListModel {
        id: lModel
    }

    ColumnLayout {
        id: mainColumn
        anchors.fill: parent
        Row {
            id: repeatCountRow
            visible: inputFieldsVisible
            Layout.alignment: Qt.AlignHCenter
            Label {
                anchors.verticalCenter: parent.verticalCenter
                text: qsTr("Repeat count: ")
            }
            TextField {
                id: countTf
                validator: IntValidator {
                    bottom: 1
                    top: 9
                }
                text: "3"
                onTextChanged: root.apply()
            }
        }
        Row {
            id: workDurationRow
            visible: inputFieldsVisible
            Layout.alignment: Qt.AlignHCenter
            Label {
                anchors.verticalCenter: parent.verticalCenter
                text: qsTr("Work duration: ")
            }
            TextField {
                id: workDurationTf
                property var minuts: text[3] + text[4]
                property var hours: text[0]

                inputMask: "9\\h 99m"
                text: "0h 01m"
                onTextChanged: { minuts = text[3] + text[4] ; hours =text[0]; root.apply()}
            }
        }
        Row {
            id: breakDurationRow
            visible: inputFieldsVisible
            Layout.alignment: Qt.AlignHCenter
            Label {
                anchors.verticalCenter: parent.verticalCenter
                text: qsTr("Break duration: ")
            }
            TextField {
                id: breakDurationTf
                property var minuts: text[3] + text[4]
                property var hours: text[0]
                inputMask: "9\\h 99m"
                text: "0h 01m"
                onTextChanged: { minuts = text[3] + text[4] ; hours =text[0]; root.apply()}
            }
        }
        GridView {
            id: timeMapView
            Layout.fillHeight: true
            Layout.fillWidth: true
            z: -1
            cellHeight: 150
            cellWidth: 140
            model: lModel
            delegate: Column {
                id: delegate
                Image {
                    sourceSize.height: 100
                    sourceSize.width: 100
                    source: {
                        if (completed)
                            source: Qt.resolvedUrl("pics/completed")
                        else if (type === "break")
                            source: Qt.resolvedUrl("pics/coffee")
                        else if (type === "work")
                            source: Qt.resolvedUrl("pics/typewriter")
                    }
                    anchors.horizontalCenter: parent.horizontalCenter
                }
                Text {
                    text: {
                        if(completed)
                            text : "Completed "+type
                        else
                            text : convert.msToStr(remainingTime)
                    } //displays the number of seconds if their number is non-decimal of 60
                    anchors.horizontalCenter: parent.horizontalCenter
                }
            }
        }
    }
}
