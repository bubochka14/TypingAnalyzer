import QtQuick
import QtQuick.Controls 6.2
import QtCharts
ChartView {
   id: chartViewWPM
   property alias lineSeries: lsWPM
   property alias yAxis: axisyWPM
   property alias xAxis: axisxTime
   title: "WPM Statistics"
   titleFont.bold: true
   titleFont.pointSize: 12
   antialiasing: true
   legend.visible: false

   ValueAxis {
     id: axisyWPM
     min: 0
     max: 100
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
     format: "hh:mm"
     tickCount: 5
     titleText: "Time"
     titleFont.bold: true
     titleFont.italic: true
     titleFont.pointSize: 10
   }

   SplineSeries {
     id: lsWPM
     onPointAdded :(index)=> {
         if(count<=1)
             axisxTime.min = new Date()
         var point = lsWPM.at(index);
         if(point.x>=axisxTime.max)
            {axisxTime.max = new Date(point.x+1000)}

         if(point.y>=axisyWPM.max)
            axisyWPM.max = point.y + 10
     }
     name: "WPM Statistics"
     axisX: axisxTime
     axisY: axisyWPM
   }
 }
