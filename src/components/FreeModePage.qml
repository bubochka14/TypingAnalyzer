import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import KeyboardAnalyzer
import KeyboardInterceptor
MainWindowPage{
    id: root
    name: "Free Mode"
    iconSource: Qt.resolvedUrl("icons/chart")
    states:[
        State{
            name: "stopped"; //when: pauseBtn.pressed  || finishBtn.pressed
            PropertyChanges { target: startBtn; enabled: true }
            PropertyChanges { target: pauseBtn; enabled: false }
            PropertyChanges { target: finishBtn; enabled: true }
        },
        State{
            name: "enrolling"; //when: startBtn.pressed
            PropertyChanges { target: startBtn; enabled: false }
            PropertyChanges { target: pauseBtn; enabled: true }
            PropertyChanges { target: finishBtn; enabled: true }
        },
        State{
            name: "finished"; //when: startBtn.pressed
            PropertyChanges { target: startBtn; enabled: true }
            PropertyChanges { target: pauseBtn; enabled: false }
            PropertyChanges { target: finishBtn; enabled: false }
        }

    ]
//    KeyboardInterceptor
//    {
//        id:watcher
//        onEventProduced:(e)=> sp.produceSound(e)
//    }
    TypeWriterSP
    {
        id: sp
    }

    TypingAnalyzer
    {
        id:typingAnalyzer
        // onWpmUpdated: {
        //     statistics.pushWpm(wpm,new Date)
        // }
        //KeyboardInterceptor: watcher

    }
    ColumnLayout {
        anchors.fill: parent
        WpmStatistics {
            Layout.fillHeight: true
            Layout.fillWidth: true
            id: statistics
            totalWordsCount: TypingAnalyzer.wordCounter.wordCount//!
        } Row{
            Layout.alignment: Qt.AlignHCenter
            Button {
                id: startBtn
                onClicked: {
                    watcher.startWatching();
                    TypingAnalyzer.start();
                    root.state ="enrolling"
                }
                text: qsTr("Start")
            }
            Button{
                id: pauseBtn
                enabled: false
                text: qsTr("Pause")
                onClicked: {
                    root.state = "stopped"
                    TypingAnalyzer.stop();
                    watcher.stopWatching();


                }
            }
            Button{
                id: finishBtn
                enabled: false
                text: qsTr("Finish")
                onClicked: {root.state = "finished";
                    TypingAnalyzer.stop();
                    watcher.stopWatching();
                    TypingAnalyzer.wordCounter.wordCount = 0 //!!!
                            statistics.clear();
                }
            }
        }
    }
}
