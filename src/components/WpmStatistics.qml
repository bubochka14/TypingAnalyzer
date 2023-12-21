import QtQuick
import QtQuick.Window
import QtQuick.Controls 6.2
import QtQuick.Layouts
ColumnLayout {
    id: layout
    property int wordCount : 0
    property int wpmSum: 0
    property alias chart: chart
    function clear()
    {
        wpmSum = 0;
        chart.lineSeries.clear();
    }

    function pushWpm(wpm, time)
    {
        chart.lineSeries.append(time,wpm);
        wpmSum+= wpm;
    }

    WPMChart
    {
        id: chart
        Layout.fillHeight: true
        Layout.fillWidth: true
    }
    Label
    {
        id: totalWordsLbl
        text: qsTr("Total words: ")+wordCount;
    }
    Label
    {
        id: avgWpm
        text: qsTr("Average WPM: ") + (chart.lineSeries.count===0 ? "0": wpmSum/chart.lineSeries.count);
    }
}
