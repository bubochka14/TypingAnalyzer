import QtQuick
import QtQuick.Window
import QtQuick.Controls 6.2
import QtQuick.Layouts
import KeyboardAnalyzer
import QtMultimedia
MainWindowPage {
    id: root
    property int updateInterval: 1000
    property string currentPeriodType
    property list<typingRate> rates
    onRatesChanged:{console.log("new",rates)}
    function start()
    {
        updateTimer.start();
        TypingAnalyzer.start()
    }
    function stop()
    {

    }
    name: "Time Focus Page"
    iconSource: Qt.resolvedUrl("pics/coffee")
    padding: 20
    //states named as TimeFocusPanel periods excluding started and nonStarted
    states: [
        State{
            name: "started"
            PropertyChanges {target: tfPanel;inputFieldsVisible: false}
            PropertyChanges {target: acceptBtn;enabled: false}
            PropertyChanges {target: stopBtn;enabled: true}
            StateChangeScript {name: "startScript";script: {updateTimer.start(); analyzer.start()}}
        },
        State {
            name: "break"
            PropertyChanges {target: tfPanel; inputFieldsVisible: false}
            PropertyChanges {target: acceptBtn;enabled: false}
            PropertyChanges {target: stopBtn;enabled: true}
            StateChangeScript {name: "breakScript";script:{
                    analyzer.stop();
                    sp.enabled = false;
                    stDialog.show(root.rates)
                    periodChangeSound.play();

                }
            }
        },
        State {
            name: "work"
            PropertyChanges {target: tfPanel; inputFieldsVisible: false}
            PropertyChanges {target: acceptBtn;enabled: false}
            PropertyChanges {target: stopBtn;enabled: true}
            StateChangeScript {name: "workScript";script: {
                    analyzer.reset();
                    analyzer.start();
                    root.rates = [];
                    stDialog.close();
                    sp.enabled = true;
                    periodChangeSound.play()}
            }
        },
        State {
            name: "notStarted"
            PropertyChanges {target: acceptBtn;enabled: true}
            PropertyChanges {target: stopBtn;enabled: false}
            PropertyChanges {target: tfPanel; inputFieldsVisible: true}
            StateChangeScript {name: "notStartedScript"; script: {sp.enabled = false;updateTimer.stop(); tfPanel.apply()}}
        }
    ]
    Timer{
        id: updateTimer
        property var currentIndex
        interval: updateInterval
        repeat: true
        onTriggered: {
            if (TimeFocusModel.rowCount === 0)
                root.state = "notStarted"

            for (var i =0;;i++) {
                var idx = TimeFocusModel.index(i,0);
                var remTime = TimeFocusModel.data(idx, TimeFocusModel.RemainingTime);
                if(remTime <=0 || TimeFocusModel.data(idx,TimeFocusModel.Completed))
                    continue; //if cell already completed
                 if (TimeFocusModel.data(idx, TimeFocusModel.Type) !== root.state)
                    root.state = TimeFocusModel.data(idx, TimeFocusModel.Type);
                remTime -= interval
                if(remTime<=0)
                {
                    remainingTime =0;
                    TimeFocusModel.setData(idx,true,FocusModel.Completed)
                }
                TimeFocusModel.setData(idx,remTime, TimeFocusModel.RemainingTime)
                break;

            }
        }
    }
    SoundEffect {
            id: periodChangeSound
            source: Qt.resolvedUrl("qrc:/sounds/ring.wav")
        }
    TypeWriterSP
    {
        id: sp
    }
    header: TabBar {
        id: tabBar
        TabButton {
            text: qsTr("Time Focus")
        }
    }
    StackLayout {
        id: stack
        anchors.fill: parent
        currentIndex: tabBar.currentIndex
        ColumnLayout {
            TimeFocusPanel {
                id: tfPanel
                Layout.fillHeight: true
                Layout.fillWidth: true
             }
            Row {
                Layout.alignment: Qt.AlignHCenter
                spacing:5
                Button {
                    id:acceptBtn
                    text: "Accept"
                    focus:true
                    onClicked: root.state = "started"
                }
                Button {
                    id:stopBtn
                    text: "Stop"
                    enabled: false
                    onClicked: root.state = "notStarted"
                }
            }
        }
    }

   TypingAnalyzer
   {
       id:analyzer
       onRateChanged:{ root.rates.push(rate)}
   }
   StatisticsDialog
   {
       id: stDialog
   }
}
