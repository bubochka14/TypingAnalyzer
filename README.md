# TypingAnalyzer
Необходим Qt версии 6.5 и C++17. 
Программа предназначена для измерения скорости ввода на клавиатуре, составления периодов работы/отдыха, возпроизведение звука под нажатия клавиш.
## Скриншоты
![Alt text](/screenshots/focus.png?)
![Alt text](/screenshots/gr.png?)

## Сборка
```
git submodule update --init --recursive
mkdir build && cd build
cmake --build . --config Release --target app
```
