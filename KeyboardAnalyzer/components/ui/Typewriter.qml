import QtQuick
import QtQuick.Controls
Image {
    property date timeInterval
    source: Qt.resolvedUrl("pics/typewriter")
    width: 100
    height: 100
 TextField  {
        id: hourField
        anchors.top: parent.bottom;
        anchors.horizontalCenter: parent.horizontalCenter
        placeholderText: "00:00"
        inputMethodHints: Qt.ImhDigitsOnly
        onActiveFocusChanged:{
                    inputMask="99:99"
            }
        background: Rectangle{
            opacity:    0
        }
    }
}
