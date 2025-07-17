# CppTUIEngine

![C++](https://img.shields.io/badge/C++-00599C?style=flat&logo=c%2B%2B&logoColor=white)
![G++](https://img.shields.io/badge/G++-00599C?style=flat&logo=c%2B%2B&logoColor=white)
<img src="https://upload.wikimedia.org/wikipedia/commons/5/5f/Windows_logo_-_2012.svg" width="20" alt="Windows"/>

README.md на русском

[![English](https://img.shields.io/badge/README-English-blue)](README.md)

<div align="center">
  <img src="img/CppTUIIcon.png" width="500" alt="CppTUI_icon"/>
</div>

# Движок на C++ для TUI

Это простой движок на C++ для создания текстового пользовательского интерфейса (TUI). Он сочетает в себе скорость и простоту, но при этом обладает детальной настройкой элементов. Не использует никакие другие библиотеки, только чистый C++. Работает только в Windows.

[![Документация](https://img.shields.io/badge/Documentation-В_процессе-yellow?style=flat&logo=read-the-docs&logoColor=white)](https://github.com/your-repo/wiki)

Здесь будет краткая и поверхностная документация по установке и использованию последней версии движка.

# Установка

Для установки CppTUIEngine на компьютер выполните команду cmd:

``` bash
git clone https://github.com/UbicaTravy/CppTUIEngine
```

Отлично! CppTUIEngine установлен на ваш ПК!

## Структура

```
CppTUIEngine/
 |helper/
 |-build_tool.cpp
 |-comp.bat <--- Он собирает только build_tool.cpp!
 |menu/
 |-menu.cpp
 |-menu.h
 |console_utils.cpp <--- главный файл движка
 |console_utils.h
 |main.cpp <--- Ваш код
```

## Использование

Для использования движка нужно установить `g++` и иметь Windows7/8/10 (или любую ту, на которую можно установить g++). Авторы используют `g++` версии `14.2.0`.

В начале файла находятся импорты заголовочных и .cpp файлов движка, а также Windows.h

```cpp
#include "console_utils.h"
#include "menu/menu.h" // для меню
#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h> // _getch()
```

Сначала давайте инициализируем цвет фона и шрифта.

```cpp
setColor(15, 1); // белый шрифт на чёрном фоне
```

Создадим простое меню

```cpp
std::vector<std::string> menuItems = {
    "1. Первая опция",
    "2. Вторая опция", 
    "3. Выход"
};

// Создаём меню:
// '+' - символ возле выбранного элемента меню
// ' ' - символ возле не выбранного элемента меню
Menu menu(menuItems, '+', ' ');
```

Теперь сделаем отображение меню и обработку выбора.

```cpp
while (true) {
        if (_kbhit()) {
            int ch = _getch();
            
            // Обработка стрелок
            if (ch == 224 || ch == 0) {
                ch = _getch();
                if (ch == 72) menu.moveUp(); // Вверх
                else if (ch == 80) menu.moveDown(); // Вниз
                
                // Перерисовка
                clearScreen();
                show_text("Главное меню", (width - 11) / 2, 2);
                menu.draw((width - 20) / 2, height / 2 - 1);
            }
            // Обработка Enter
            else if (ch == '\r') {
                int selected = menu.getSelectedIndex();
                
                if (selected == 0) showOption1(width, height);
                else if (selected == 1) showOption2(width, height);
                else if (selected == 2) break; // Выход
                
                // Перерисовка после возврата
                clearScreen();
                show_text("Главное меню", (width - 11) / 2, 2);
                menu.draw((width - 20) / 2, height / 2 - 1);
            }
        }
    }
    
    // Восстановление цветов
    setColor(15, 0);
    clearScreen();
    return 0;
}
```

Добавим функцию, которая позволит при изменении размера окна подстраивать интерфейс под новый размер.

```cpp
// Проверка изменения размера консоли
int newWidth, newHeight;
getConsoleSize(newWidth, newHeight);
if (newWidth != width || newHeight != height) {
    width = newWidth;
    height = newHeight;
    clearScreen();
    show_text("Главное меню", (width - 11) / 2, 2);
    menu.draw((width - 20) / 2, height / 2 - 1);
```

Полный код:

```cpp
#include "console_utils.h"
#include "menu/menu.h"
#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>

void showOption1(int width, int height) {
    clearScreen();
    show_text("Вы выбрали первую опцию!", (width - 22) / 2, height / 2);
    show_text("Нажмите любую клавишу...", (width - 22) / 2, height / 2 + 1);
    _getch();
}

void showOption2(int width, int height) {
    clearScreen();
    show_text("Вы выбрали вторую опцию!", (width - 22) / 2, height / 2);
    show_text("Нажмите любую клавишу...", (width - 22) / 2, height / 2 + 1);
    _getch();
}

int main() {
    int width, height;
    getConsoleSize(width, height);
    
    // Настройка цветов (белый текст на синем фоне)
    setColor(15, 1);
    
    // Создание пунктов меню
    std::vector<std::string> menuItems = {
        "1. Первая опция",
        "2. Вторая опция",
        "3. Выход"
    };
    
    // Инициализация объекта меню (исправлено)
    Menu menu(menuItems, '>', ' ');
    
    // Первоначальная отрисовка
    clearScreen();
    show_text("Главное меню", (width - 11) / 2, 2);
    menu.draw((width - 20) / 2, height / 2 - 1);
    
    // Основной цикл
    while (true) {
        if (_kbhit()) {
            int ch = _getch();
            
            // Обработка стрелок
            if (ch == 224 || ch == 0) {
                ch = _getch();
                if (ch == 72) menu.moveUp(); // Вверх
                else if (ch == 80) menu.moveDown(); // Вниз
                
                // Перерисовка
                clearScreen();
                show_text("Главное меню", (width - 11) / 2, 2);
                menu.draw((width - 20) / 2, height / 2 - 1);
            }
            // Обработка Enter
            else if (ch == '\r') {
                int selected = menu.getSelectedIndex();
                
                if (selected == 0) showOption1(width, height);
                else if (selected == 1) showOption2(width, height);
                else if (selected == 2) break; // Выход
                
                // Перерисовка после возврата
                clearScreen();
                show_text("Главное меню", (width - 11) / 2, 2);
                menu.draw((width - 20) / 2, height / 2 - 1);
            }
        }
        
        // Проверка изменения размера консоли
        int newWidth, newHeight;
        getConsoleSize(newWidth, newHeight);
        if (newWidth != width || newHeight != height) {
            width = newWidth;
            height = newHeight;
            clearScreen();
            show_text("Главное меню", (width - 11) / 2, 2);
            menu.draw((width - 20) / 2, height / 2 - 1);
        }
        
        Sleep(50);
    }
    
    // Восстановление цветов
    setColor(15, 0);
    clearScreen();
    return 0;
}
```

## Сборка и релиз

Движок имеет помощника для сборки и запуска проекта. Но сначала его нужно собрать. Зайдите в папку `helper` и выполните файл `comp.cmd`. .ехе файл не идёт с этим помощником из-за различия архитектуры и для удобства менять команды в нём или добавлять что-то своё.

После сборки в главной папке проекта появиться `build_tool.exe`, запустите его. Выберете стрелочками пункт `Build and Run`. Если нет ошибок и установлен `g++` то проект соберётся и запуститься.

При такой сборке собирается только для этого компьютера. Для релиза выберете  `Build Release (static)`. УЧТИТЕ, ПО НАЧАЛУ СТОИТ СТАТИЧЕСКАЯ ЛИНОВКА! Ваш собранный релиз появиться в папке "build".

# Лицензия

[![Лицензия](https://img.shields.io/badge/License-MIT-green)](LICENSE)

<div align="center">

### Created by KillerGrass

<img src="img/killergrass_logo.jpg" width="400" alt="KillerGrass_logo"/> 

[![GitHub](https://img.shields.io/badge/-GitHub-181717?style=for-the-badge&logo=github&logoColor=white)](https://github.com/UbicaTravy)

[![Telegram](https://img.shields.io/badge/-Telegram-2CA5E0?style=for-the-badge&logo=telegram&logoColor=white)](https://t.me/killergrass_programms)

[![LIVE Channel](https://img.shields.io/badge/-LIVE&nbsp;Kanal-2CA5E0?style=for-the-badge&logo=telegram&logoColor=white)](https://t.me/kanal_kashkamalhika)

</div>

<div align="center">

## Contacts

[![Telegram](https://img.shields.io/badge/Telegram-2CA5E0?style=flat&logo=telegram&logoColor=white)](https://t.me/killer_grass1834)
[![Gmail](https://img.shields.io/badge/Gmail-D14836?style=flat&logo=gmail&logoColor=white)](mailto:killergrasscontact@gmail.com)
</div>