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