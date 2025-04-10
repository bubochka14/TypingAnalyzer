﻿
file(GLOB ABS_QML_SOURCES ./qml/*.qml)
foreach(file IN LISTS ABS_QML_SOURCES)
	file(RELATIVE_PATH QML_SOURCE ${CMAKE_CURRENT_SOURCE_DIR} ${file})
	get_filename_component(QML_FILENAME ${file}	NAME)
	set_source_files_properties(${QML_SOURCE} PROPERTIES
		QT_RESOURCE_ALIAS ${QML_FILENAME}
	)

	list(APPEND QML_SOURCES ${QML_SOURCE})
endforeach()
#set(QT_QML_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/qml)

set (CPP_SOURCES 
	"wordcounter.h" 
	"wordcounter.cpp" 
	"typewriterSP.h" 
	"typewritersp.cpp"
	"timefocusmodel.cpp"
	"timefocusmodel.h"
	"applicationsettings.h"
	"applicationsettings.cpp"
	"soundinterfaces.h"
	"typinganalyzer_include.h"
	"soundinterfaces.cpp"
    "pageapplication.h"
    "pageapplication.cpp"
	"customkbproducer.h" 
	"customkbproducer.cpp" 
	"apppage.h" 
	"namedobject.h" 
	"slidersetting.h"
	"slidersetting.cpp"
	"timefocuspage.h" 
	"apppage.cpp" 
	"timefocuspage.cpp"
	"settingslist.h"
	"timefocusexecutable.h" 
	"timefocusexecutable.cpp" 
	"executable.h"  
	"settingspage.h" 
	"namedobject.cpp" 
	"settingspage.cpp" 
	"executable.cpp" 
    "typingmeter.h"
	"customperiodproducer.h"
	"customperiodproducer.cpp"
	"aconfigurable.h"
	"aconfigurable.cpp"
    "typingmeter.cpp"
	"freemodepage.h" 
	"freemodepage.cpp" 
	"typingrate.h" 
	"typingrate.cpp" 
	"appsetting.h" 
	"iqmlcontent.h" 
	"appsetting.cpp" 
	"listsetting.h" 
	"listsetting.cpp" 
	"contentbuilder.h" 
	"contentbuilder.cpp" 
	"executablekbproducer.h" 
	"executablekbproducer.cpp" 
	"application.h" 
    "application.cpp"
	"executableholder.h" 
	"executableholder.cpp"
)
set(LIB_NAME "TypingAnalyzer")
set(RESOURCES 
	"resources/pics/chart.svg"
	"resources/pics/coffee.svg"
	"resources/pics/completed.svg"
	"resources/pics/menu.png"
	"resources/pics/settings.svg"
	"resources/pics/typewriter.png"
)
add_library(${LIB_NAME} SHARED)
QT_ADD_QML_MODULE(${LIB_NAME}
	URI ${LIB_NAME}
	NO_GENERATE_PLUGIN_SOURCE
	SOURCES ${CPP_SOURCES}
	QML_FILES ${QML_SOURCES}
	RESOURCES 	${RESOURCES}

)
target_compile_definitions(${LIB_NAME} PRIVATE 	
	LIB_NAME="${LIB_NAME}" 
	SHARED
)
target_include_directories(${LIB_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
if (CMAKE_VERSION VERSION_GREATER 3.12)
	set_property(TARGET ${LIB_NAME} PROPERTY CXX_STANDARD 20)
	set_property(TARGET ${LIB_NAME} PROPERTY CXX_STANDARD_REQUIRED TRUE
)
endif()
include(GNUInstallDirs)
install(TARGETS ${LIB_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)   
target_link_libraries(${LIB_NAME} PRIVATE 
	Qt6::Core
	Qt6::Qml 
    Qt6::Gui
	Qt6::Charts
	Qt6::Multimedia
	Qt6::Quick 
	KeyboardWatcher
)
