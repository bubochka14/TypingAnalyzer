# CMakeList.txt: проект CMake для KeyboardAnalyzer; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#

# Добавьте источник в исполняемый файл этого проекта

set(QML_SOURCES )
add_executable (KeyboardAnalyzer "KeyboardAnalyzer.cpp" "KeyboardAnalyzer.h" "main.cpp" "main.qrc"  "pressingmodel.h" "wordcounter.h" "wordcounter.cpp" "KBSoundPlayerI.h" "EmptyKBSoundPlayer.h" "emptykbsoundplayer.cpp" "wpmcalculator.h" "wpmcalculator.cpp" "typewriterSP.h" "typewritersp.cpp")
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET KeyboardAnalyzer PROPERTY CXX_STANDARD 20)
endif()

target_link_libraries(KeyboardAnalyzer PRIVATE 
	Qt6::Core 
	Qt6::Qml 
    Qt6::Gui
	Qt6::Charts
	Qt6::Multimedia
	Qt6::Quick 
	keywatcher
	components
)


set(APP_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}  CACHE INTERNAL "")
set(APP_BUILD ${CMAKE_CURRENT_BINARY_DIR} CACHE INTERNAL "")
add_subdirectory(components)
#file(REAL_PATH "./elements" LIB_PATH BASE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
#list(APPEND QML_IMPORT_PATHS "${LIB_PATH}")
#set(QML_IMPORT_PATH "${QML_IMPORT_PATHS}" CACHE STRING "Qt Creator QML import paths")

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
