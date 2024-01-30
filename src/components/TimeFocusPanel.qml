import QtQuick
import QtQuick.Window
import QtQuick.Controls 6.2
import QtQuick.Layouts
import KeyboardAnalyzer

Item {
    id: root
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
        TimeFocusModel.clear();
        TimeFocusModel.insertRows(0,countTf.text*2);
        var workMs = convert.toMiliseconds(workDurationTf.hours,
                                           workDurationTf.minuts)
        var breakMs = convert.toMiliseconds(breakDurationTf.hours,
                                            breakDurationTf.minuts)

        for (var i = 0; i < countTf.text*2; i+=2) {
            TimeFocusModel.setData(TimeFocusModel.index(i,0),workMs,TimeFocusModel.Duration);
            TimeFocusModel.setData(TimeFocusModel.index(i,0),workMs,TimeFocusModel.RemainingTime);
            TimeFocusModel.setData(TimeFocusModel.index(i,0),0,TimeFocusModel.Completed);
            TimeFocusModel.setData(TimeFocusModel.index(i,0),"work",TimeFocusModel.Type);

            TimeFocusModel.setData(TimeFocusModel.index(i+1,0),breakMs,TimeFocusModel.Duration);
            TimeFocusModel.setData(TimeFocusModel.index(i+1,0),breakMs,TimeFocusModel.RemainingTime);
            TimeFocusModel.setData(TimeFocusModel.index(i+1,0),0,TimeFocusModel.Completed);
            TimeFocusModel.setData(TimeFocusModel.index(i+1,0),"break",TimeFocusModel.Type);


        }
    }
    Component.onCompleted: root.apply()

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
            model: TimeFocusModel
            delegate: Column {
                id: delegate
                Image {
                    sourceSize.height: 100
                    sourceSize.width: 100
                    Component.onCompleted: console.log(remainingTime)
                    source: {
                        if (completed)
                            source: Qt.resolvedUrl("pics/completed")
                        else if (type === "break")
                            source: Qt.resolvedUrl("pics/coffee")
                        else if (type === "work")
                            source: Qt.resolvedUrl("pics/typewriter")
                    }
                    anchors.horizontalCenter: parent.horizontalCenter
                    MouseArea
                    {
                        enabled: (rates.size && completed) ? true:false
                        anchors.fill: parent
                        cursorShape: enabled? Qt.PointingHandCursor : Qt.ArrowCursor
                        onClicked: statsDial.show(rates)
                    }
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
    StatisticsDialog
    {
        id: statsDial
    }
}
