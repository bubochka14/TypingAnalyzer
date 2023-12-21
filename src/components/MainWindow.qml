import QtQuick
import QtQuick.Window
import QtQuick.Controls 6.2
import QtQuick.Layouts

ApplicationWindow {
    id: root
    function setPage(page : MainWindowPage)
    {
        root.header = page.header;
    }
    background: Rectangle {
        color: "grey"
    }
    StackLayout {
        id: stack
        anchors.fill: parent
        TimeFocusPage {}
       // FreeModePage {}
        SettingsPage {}
    }
    PageSelector {
        id: selector
        pagesToSelect: stack.children
        width: root.width * 0.4
        height: root.height
        onPageSelected: (index,name) =>
                        {
                            selector.close()
                            stack.currentIndex = index
                        }
    }
    MenuButton {
        id: menuBtn
        anchors.top: parent.top
        anchors.margins: 10
        anchors.left: parent.left
        onClicked: selector.open()
    }
}
