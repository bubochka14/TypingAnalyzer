
# Добавьте источник в исполняемый файл этого проекта.
add_library (keywatcher STATIC
	"keywatcher.h"
	"keywatcher.cpp"
	"keywatcher_private.h"
	"ikeyboardinterceptor.h"
	"ikeyboardinterceptor.cpp"
	"winkeyboardinterceptor.h"
	"winkeyboardinterceptor.cpp" "keyevent.h")
#add_library(winKeyboardCapture SHARED "winkeyboardinjection.cpp") 
target_include_directories(keywatcher PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
# TODO: Добавьте тесты и целевые объекты, если это необходимо.
#install(TARGETS winKeyboardCapture
#  LIBRARY DESTINATION ${APP_BUILD}
#  RUNTIME DESTINATION ${APP_BUILD})

    target_link_libraries(keywatcher PRIVATE 
	Qt6::Core 
	Qt6::Gui
	Qt6::Qml 
	Qt6::Quick 
)