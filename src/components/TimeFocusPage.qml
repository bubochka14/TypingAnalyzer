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
                    statisticsDial.st.rates = root.rates
                   statisticsDial.show();
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
                    statisticsDial.close();
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
                {
                    remainingTime =0;
                    tfPanel.model.setProperty(i,"completed",true)
                    tfPanel.model.setProperty(i, "rates",root.rates);
                }
                tfPanel.model.setProperty(i, "remainingTime", remainingTime)
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
   Window
   {
       id:statisticsDial
       property alias st:st
       width:400
       height:500
       ColumnLayout{
           anchors.fill: parent
       WpmStatistics
       {
           Layout.fillHeight: true
           Layout.fillWidth: true
           id: st
       }
       Button{
           text: qsTr("Awesome!")
           focus: true
           onClicked: statisticsDial.close();
       }
       }
   }
}
