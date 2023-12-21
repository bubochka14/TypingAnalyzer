import QtQuick
import QtQuick.Window
import QtQuick.Controls 6.2
import QtCharts
import KeyboardAnalyzer
import KeyboardInterceptor

WpmStatistics {
    totalWordsCount: TypingAnalyzer.wordCounter.wordCount //!
    KeyboardInterceptor {
        id: watcher
        onEventProduced: e => sp.produceSound(e)
    }
    TypeWriterSP {
        id: sp
    }

//    TypingAnalyzer {
//        id: TypingAnalyzer
//        interval: 1000
//        onWpmUpdated: {
//            statistics.pushWpm(wpm, new Date)
//        }
//        KeyboardInterceptor: watcher
//    }
    WpmStatistics {
        Layout.fillHeight: true
        Layout.fillWidth: true
        id: statistics
        totalWordsCount: TypingAnalyzer.wordCounter.wordCount //!
    }
}
