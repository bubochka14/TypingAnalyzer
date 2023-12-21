import QtQuick
import QtQuick.Window
import QtQuick.Controls 6.2
import QtQuick.Layouts
import KeyboardAnalyzer
import QtMultimedia
import KeyboardInterceptor
MainWindowPage {
    id: root
    property int updateInterval: 1000
    property string currentPeriodType
    function start()
    {
        updateTimer.start();
        TypingAnalyzer.start()
    }
    function stop()
    {

    }
    Component.onCompleted: {statisticsDial.open(); state ="started"}
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
            StateChangeScript {name: "breakScript";script:{sp.enabled = false; periodChangeSound.play()}}
        },
        State {
            name: "work"
            PropertyChanges {target: tfPanel; inputFieldsVisible: false}
            PropertyChanges {target: acceptBtn;enabled: false}
            PropertyChanges {target: stopBtn;enabled: true}
            StateChangeScript {name: "workScript";script: {sp.enabled = true; periodChangeSound.play()}}
        },
        State {
            name: "notStarted"
            PropertyChanges {target: acceptBtn;enabled: true}
            PropertyChanges {target: stopBtn;enabled: false}
            PropertyChanges {target: tfPanel; inputFieldsVisible: true}
            StateChangeScript {name: "notStartedScript"; script: {sp.enabled = false;updateTimer.stop(); tfPanel.apply()}}
        }
    ]
    onStateChanged: console.log(state)
    Timer{
        id: updateTimer
        interval: updateInterval
        repeat: true
        onTriggered: {
            if (tfPanel.model.count === 0)
                root.finish();
            for (var i =0;tfPanel.model.get(i);i++) {
                var cell = tfPanel.model.get(i)
                var remainingTime = cell.remainingTime
                if(remainingTime <=0 || cell.completed)
                    continue;//if cell already completed
                if (cell.type !== root.state)
                    root.state = cell.type;
                remainingTime -= interval
                if(remainingTime<=0)
                {remainingTime =0;
                    tfPanel.model.setProperty(i,"completed",true)}
                tfPanel.model.setProperty(i, "remainingTime", remainingTime)
                break;

            }
        }
    }
    SoundEffect {
            id: periodChangeSound
            source: Qt.resolvedUrl("qrc:/sounds/ring.wav")
            Component.onCompleted: console.log("s",status)
        }
//    KeyboardInterceptor
//    {
//       id:watcher
//       onEventProduced:(e)=> {console.log(e);sp.produceSound(e)}
//    }
    TypeWriterSP
    {
        id: sp
    }
    header: TabBar {
        id: tabBar
        TabButton {
            text: qsTr("Time Focus")
        }
//        TabButton {
//            text: qsTr("Statistics")
//        }
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
                    onClicked: root.state = "started"
                }
                Button {
                    id:stopBtn
                    text: "Stop"
                    onClicked: root.state = "notStarted"
                }
            }
        }
    }

   TypingAnalyzer
   {
       id:analyzer
       // onWpmUpdated: {
       //     statistics.pushWpm(wpm,new Date)
       // }

   }
   Dialog
   {
       id:statisticsDial
       width:400
       height:300
       analyzer.onWpmChanged: pushWpm(analyzer.wpm)
       WpmStatistics
       {
           id: st
           anchors.fill: parent
           wordCount: analyzer.wordCount
       }
   }
}
