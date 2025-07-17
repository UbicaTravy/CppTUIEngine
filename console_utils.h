#ifndef CONSOLE_UTILS_H
#define CONSOLE_UTILS_H

#include <string>

void getConsoleSize(int &width, int &height);

void clearScreen();

void setColor(int colorText, int colorBackground);

void resetColor();

void show_text(const std::string &text, int x, int y);

#endif