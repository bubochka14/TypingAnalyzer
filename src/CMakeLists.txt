find_package(Qt6 REQUIRED COMPONENTS Core Qml Quick QuickControls2 Multimedia)
qt_standard_project_setup(REQUIRES 6.8)

set(QT_QML_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/qml)
set (APP_SOURCES 
	"main.cpp" "main.qrc" 
)
qt_add_executable (app ${APP_SOURCES})
if(MSVC)
    target_link_options(app
        PUBLIC
        $<$<CONFIG:Debug>:/subsystem:CONSOLE>
        $<$<CONFIG:Release>:/subsystem:WINDOWS;/ENTRY:mainCRTStartup>
    )
endif()
if (CMAKE_VERSION VERSION_GREATER 3.12)
	set_property(TARGET app PROPERTY CXX_STANDARD 20)
endif()
include(GNUInstallDirs)
install(TARGETS app
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
target_link_libraries(app PRIVATE 
	Qt6::Core 
	Qt6::Qml 
    Qt6::Gui
	Qt6::Charts
	Qt6::Multimedia
	Qt6::Quick 
	TypingAnalyzer
	KeyboardWatcher
)


set(APP_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}  CACHE INTERNAL "")
set(APP_BUILD ${CMAKE_CURRENT_BINARY_DIR} CACHE INTERNAL "")