
# Добавьте источник в исполняемый файл этого проекта.
add_library(KeyboardInterceptor STATIC 	
	"src/keyboardInterceptor.cpp"
	"src/winkeyboardinterceptor.cpp"  
	"include/keyboardInterceptor.h"
	"include/keyevent.h"
	"include/akeyboardInterceptor.h"
	"src/akeyboardInterceptor.cpp"
)
#add_library(winKeyboardCapture SHARED "winkeyboardinjection.cpp") 
target_include_directories(KeyboardInterceptor
    PRIVATE 
        "${CMAKE_CURRENT_SOURCE_DIR}/src"
    PUBLIC 
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
)
target_sources(KeyboardInterceptor PRIVATE "src/winkeyboardinterceptor.h" "src/keyboardinterceptor_private.h")
target_compile_definitions(KeyboardInterceptor PRIVATE SHARED=true)
# TODO: Добавьте тесты и целевые объекты, если это необходимо.
#install(TARGETS winKeyboardCapture
#  LIBRARY DESTINATION ${APP_BUILD}
#  RUNTIME DESTINATION ${APP_BUILD})

    target_link_libraries(KeyboardInterceptor PRIVATE 
	Qt6::Core 
	Qt6::Gui
	Qt6::Qml 
	Qt6::Quick 
)