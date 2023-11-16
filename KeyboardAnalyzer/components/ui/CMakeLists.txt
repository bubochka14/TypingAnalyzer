set(QML_SOURCES

    "Typewriter.qml"
    "MenuButton.qml"
    "ImageButton.qml"
)
set(QML_RESOURCES
    "icons/menu.png"
    "icons/settings.svg"
    "pics/typewriter.png"
)
set(CPP_SOURCES 

)

QT_ADD_QML_MODULE(components_ui STATIC
    NO_PLUGIN
    URI components/components_ui
    RESOURCES 
        ${QML_RESOURCES}
    QML_FILES
        ${QML_SOURCES}
    DEPENDENCIES
        Quick

        SOURCES
        QML_FILES NamedTextField.qml

)
target_link_libraries(components_ui PRIVATE Qt::QmlPrivate Qt::QuickPrivate )
