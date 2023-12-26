import QtQuick
import QtQuick.Window
import QtQuick.Controls 6.2
import QtQuick.Layouts
import KeyboardAnalyzer

ColumnLayout {
    id: layout
    property list<typingRate> rates
    property alias chart: chart
    onRatesChanged:
    {
        chart.lineSeries.clear()
        for(var i=0; i< rates.length; i++)
           {console.log(rates[i].time, rates[i].cpm); chart.lineSeries.append(rates[i].time, rates[i].cpm)}
        chart.xAxis.min = new Date(rates[0].time);
        chart.xAxis.max = new Date(rates[rates.length-1].time);
        totalWordsLbl.text= qsTr("Total words: ") + rates[rates.length - 1].wordCount;
        avgWpmLbl.text= qsTr("Average WPM: ") + rates[rates.length - 1].avgWpm;
        totalCharsLbl.text= qsTr("Total characters: ") + rates[rates.length - 1].charCount;
        avgCpmLbl.text= qsTr("Average CPM: ") + rates[rates.length - 1].avgCpm;

    }
    WPMChart {
        id: chart
        Layout.fillHeight: true
        Layout.fillWidth: true
    }
    Row {
        Column {
            Label {
                id: totalWordsLbl
                text: qsTr("Total words: ") + rates[rates.length - 1].wordCount
            }
            Label {
                id: avgWpmLbl
                text: qsTr("Average WPM: ") + rates[rates.length - 1].avgWpm
            }
            Column {
                Label {
                    id: totalCharsLbl
                    text: qsTr("Total characters: ") + rates[rates.length - 1].charCount
                }
                Label {
                    id: avgCpmLbl
                    text: qsTr("Average CPM: ") + rates[rates.length - 1].avgCpm
                }
            }
        }
    }
}
