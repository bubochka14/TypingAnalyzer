import QtQuick
import QtQuick.Controls 6.2
import QtCharts
ChartView {
   id: chartViewWPM
   property alias lineSeries: lsWPM
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
     max: new Date(new Date().getTime() + 10000)
     tickCount: 5
     titleText: "Time"
     titleFont.bold: true
     titleFont.italic: true
     titleFont.pointSize: 10
   }

   LineSeries {
     id: lsWPM
     onPointAdded: {
         if(count<=1)
             axisxTime.min = new Date()
         var point = lsWPM.at(index);
         if(point.x>=axisxTime.max)
            {axisxTime.max = new Date(axisxTime.max.getTime()+ 100000)}

         if(point.y>=axisyWPM.max)
            axisyWPM.max = axisyWPM.max+ 50
     }
     name: "WPM Statistics"
     axisX: axisxTime
     axisY: axisyWPM
   }
 }
