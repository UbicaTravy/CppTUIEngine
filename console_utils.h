#ifndef CONSOLE_UTILS_H
#define CONSOLE_UTILS_H

#include <string>

// Получение размеров консоли
void getConsoleSize(int &width, int &height);

// Очистка экрана
void clearScreen();

// Установка цвета текста и фона
// colorText и colorBackground - значения из Windows API (например, 0=черный, 15=белый)
void setColor(int colorText, int colorBackground);

// Восстановление стандартных цветов
void resetColor();

// Вывод текста в позицию (x,y)
void show_text(const std::string &text, int x, int y);

#endif // CONSOLE_UTILS_H