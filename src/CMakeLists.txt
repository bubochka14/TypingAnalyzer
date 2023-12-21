# CMakeList.txt: проект CMake для KeyboardAnalyzer; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#

# Добавьте источник в исполняемый файл этого проекта

set(QML_SOURCES 

)
set (CPP_SOURCES 
	"KeyboardAnalyzer.cpp"	
	"KeyboardAnalyzer.h" 
	"pressingmodel.h" 
	"wordcounter.h" 
	"wordcounter.cpp" 
	"AKBSoundPlayer.h" 
	"AKBSoundPlayer.cpp" 
	"EmptyKBSoundPlayer.h" 
	"emptykbsoundplayer.cpp" 
	"TypingAnalyzer.h" 
	"TypingAnalyzer.cpp" 
	"typewriterSP.h" 
	"typewritersp.cpp"
	"timefocusmodel.cpp"
     "timefocusmodel.h"
	"Applicationsettings.h"
	"Applicationsettings.cpp"
)
add_executable(KeyboardAnalyzer "main.cpp" "main.qrc")
if(MSVC)
    target_link_options(KeyboardAnalyzer
        PUBLIC
        $<$<CONFIG:Debug>:/subsystem:CONSOLE>
        $<$<CONFIG:Release>:/subsystem:WINDOWS>
    )
endif()


QT_ADD_QML_MODULE(KeyboardAnalyzer 
	URI "KeyboardAnalyzer"
	SOURCES ${CPP_SOURCES}
	QML_FILES ${QML_SOURCES}
)
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET KeyboardAnalyzer PROPERTY CXX_STANDARD 20)
endif()

target_compile_definitions(KeyboardAnalyzer PRIVATE APP_NAME="KeyboardAnalyzer" ORG_NAME="ORG")
target_link_libraries(KeyboardAnalyzer PRIVATE 
	Qt6::Core 
	Qt6::Qml 
        Qt6::Gui
	Qt6::Charts
	Qt6::Multimedia
	Qt6::Quick 
	KeyboardInterceptor
        components
)


set(APP_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}  CACHE INTERNAL "")
set(APP_BUILD ${CMAKE_CURRENT_BINARY_DIR} CACHE INTERNAL "")
add_subdirectory(components)
