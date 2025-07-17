/*
 * CppTUI - Lightweight Text-based User Interface library for C++
 * 
 * Originally developed by KillerGrass (https://github.com/UbicaTravy/CppTUIEngine)
 * 
 * License: This code is provided as-is under MIT License.
 * You can freely use, modify, and distribute it in your projects,
 * including commercial ones, without any restrictions.
 */

#include <iostream>
#include "console_utils.h"
#include <windows.h>

void getConsoleSize(int &width, int &height) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
        width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    } else {
        width = height = 80;
    }
}

void clearScreen() {
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD count;
    DWORD cellCount;
    COORD homeCoords = {0, 0};

    if (hStdOut == INVALID_HANDLE_VALUE) return;

    if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;

    cellCount = csbi.dwSize.X * csbi.dwSize.Y;

    FillConsoleOutputCharacter(hStdOut, ' ', cellCount, homeCoords, &count);
    FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, cellCount, homeCoords, &count);
    SetConsoleCursorPosition(hStdOut, homeCoords);
}

void setColor(int colorText, int colorBackground) {
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, (colorBackground << 4) | (colorText & 0x0F));
}

void resetColor() {
    setColor(15, 0);
}

void show_text(const std::string &text, int x, int y) {
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = {static_cast<SHORT>(x), static_cast<SHORT>(y)};
    SetConsoleCursorPosition(hStdOut, coord);
    std::cout << text;
}