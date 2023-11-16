import QtQuick
import QtQuick.Controls 6.2
import QtCharts
ChartView {
   id: chartViewWPM
   title: "WPM Statistics"
   titleFont.bold: true
   titleFont.pointSize: 12
   antialiasing: true
   legend.visible: false

   ValueAxis {
     id: axisyWPM
     min: 0
     max: 150
     gridVisible: true
     tickCount: 7
     titleText: "WPM"
     titleFont.bold: true
     titleFont.italic: true
     titleFont.pointSize: 10
   }

   DateTimeAxis {
     id: axisxTime
     gridVisible: true
     format: "hh:mm:ss"
    min: new Date()
    max: new Date(new Date().getTime() + 45000000)
     tickCount: 10
     titleText: "Time"
     titleFont.bold: true
     titleFont.italic: true
     titleFont.pointSize: 10
   }

   LineSeries {
     id: lsWPM

     name: "WPM Statistics"
     axisX: axisxTime
     axisY: axisyWPM
   }
 }
