set(QML_SOURCES
    "SettingsMenu.qml"
    "MainWindow.qml"
    "WPMChart.qml"
    "Main.qml"
    "MyHeader.qml"
)
set(QML_RESOURCES

)
set(CPP_SOURCES 
    "timefocusmodel.cpp"
    "timefocusmodel.h"
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
        QML_FILES MenuPage.qml
        QML_FILES FreeModePage.qml

)
add_subdirectory(ui)
target_link_libraries(components PRIVATE Qt::QmlPrivate Qt::QuickPrivate components_ui)
