# CMakeList.txt: файл проекта CMake верхнего уровня; проведите глобальную конфигурацию
# и включите сюда подпроекты.
#
cmake_minimum_required (VERSION 3.8)
project ("KeyboardAnalyzer" VERSION 0.0.1 LANGUAGES CXX C)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick QuickControls2 LinguistTools Multimedia Charts REQUIRED)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_VS_INCLUDE_INSTALL_TO_DEFAULT_BUILD 1)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

# Включите подпроекты.
add_subdirectory ("KeyboardAnalyzer")
add_subdirectory ("WinKeyboardCapture")
