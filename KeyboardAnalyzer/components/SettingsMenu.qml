import QtQuick
import QtQuick.Window
import QtQuick.Controls 6.2

Drawer {
        id: drawer
        width: 0.4 * window.width
        height: window.height
        dragMargin :0
        //        interactive:false
        Menu {
               id: menu
               height:parent.height
               width: parent.width
               MenuItem {
                   text: "New..."
               }
               MenuItem {
                   text: "Open..."
               }
               MenuItem {
                   text: "Save"
               }

           }
         Component.onCompleted: menu.open()
    }
