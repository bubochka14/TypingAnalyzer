set(QML_SOURCES
    "SettingsPage.qml"
    "MainWindow.qml"
    "WPMChart.qml"
    "Main.qml"
    "MyHeader.qml"
    "Typewriter.qml"
    "MenuButton.qml"
    "ImageButton.qml"
    "TimeFocusPage.qml"
)
set(QML_RESOURCES
    "icons/menu.png"
    "icons/chart.svg"
    "icons/settings.svg"
    "pics/typewriter.png"
    "pics/coffee.svg"
    "pics/completed.svg"
)
set(CPP_SOURCES 
)

QT_ADD_QML_MODULE(components STATIC
    PLUGIN_TARGET components

    URI components
    RESOURCES 
        ${QML_RESOURCES}
    QML_FILES
        ${QML_SOURCES}
    SOURCES
        ${CPP_SOURCES}
    DEPENDENCIES
        Quick
        QML_FILES PageSelector.qml
        QML_FILES FreeModePage.qml
        QML_FILES WpmStatistics.qml
        QML_FILES TimeFocusPanel.qml
        QML_FILES InputHandler.qml
        QML_FILES MainWindowPage.qml
        QML_FILES StatisticsDialog.qml

)
target_link_libraries(components PRIVATE Qt::QmlPrivate Qt::QuickPrivate)
