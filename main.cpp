#include "console_utils.h"
#include "menu/menu.h"
#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>
#include <random>
#include <sstream>

const std::string ENGINE_INFO = "Powered by CppTUI Engine (github.com/UbicaTravy/CppTUI)";
const std::string COMPANY_INFO = "Maked by ANTI-TERROR Studio, 2025";

void drawGameScreen(int width, int height, const std::string& title, const std::string& attemptsText, 
                   const std::string& hint, const std::string& numberText, const std::string& controls) {
    clearScreen();
	
    int titleX = (width - static_cast<int>(title.length())) / 2;
    show_text(title, titleX, 2);
    show_text(attemptsText, (width - static_cast<int>(attemptsText.length())) / 2, 4);
    show_text(hint, (width - static_cast<int>(hint.length())) / 2, height / 2);
    show_text(numberText, (width - static_cast<int>(numberText.length())) / 2, height / 2 + 2);
    show_text(controls, (width - static_cast<int>(controls.length())) / 2, height / 2 + 4);
}

void playGame(int& prevWidth, int& prevHeight) {
    // Генерация случайного числа от 1 до 100
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1, 100);
    int secretNumber = distrib(gen);
    
    int attempts = 0;
    int guess = 0;
    bool gameOver = false;
    
    while (!gameOver) {
        int width, height;
        getConsoleSize(width, height);
        
        if (width != prevWidth || height != prevHeight) {
            prevWidth = width;
            prevHeight = height;
        }
        
        // Подготовка текста для отображения
        std::string title = "Guess the Number (1-100)";
        std::string attemptsText = "Attempts: " + std::to_string(attempts);
        std::string hint;
        
        if (attempts == 0) {
            hint = "I'm thinking of a number between 1 and 100...";
        } else if (guess < secretNumber) {
            hint = "Too low! Try higher.";
        } else if (guess > secretNumber) {
            hint = "Too high! Try lower.";
        } else {
            hint = "Correct! You guessed it in " + std::to_string(attempts) + " attempts!";
            gameOver = true;
        }
        
        std::string numberText = "Current guess: " + std::to_string(guess);
        std::string controls = "Use UP/DOWN to change number, ENTER to guess";
        
        // Отрисовка экрана
        drawGameScreen(width, height, title, attemptsText, hint, numberText, controls);
        
        if (!gameOver) {
            // Ожидание ввода
            while (true) {
                if (_kbhit()) {
                    int ch = _getch();
                    if (ch == 224 || ch == 0) { 
                        ch = _getch();
                        if (ch == 72) { // Up arrow
                            if (guess < 100) guess++;
                            break;
                        } else if (ch == 80) { // Down arrow
                            if (guess > 1) guess--;
                            break;
                        }
                    } else if (ch == '\r') { // Enter key
                        attempts++;
                        break;
                    }
                }
                
                // Проверка изменения размеров во время ожидания ввода
                int newWidth, newHeight;
                getConsoleSize(newWidth, newHeight);
                if (newWidth != width || newHeight != height) {
                    width = newWidth;
                    height = newHeight;
                    prevWidth = width;
                    prevHeight = height;
                    drawGameScreen(width, height, title, attemptsText, hint, numberText, controls);
                }
                
                Sleep(50);
            }
        } else {
            // Конец игры
            show_text("Press any key to return to menu...", 
                     (width - 32) / 2, height / 2 + 2);
            _getch();
        }
    }
}

void drawSettingsScreen(int width, int height) {
    clearScreen();
    
    std::string title = "Settings";
    int titleX = (width - static_cast<int>(title.length())) / 2;
    show_text(title, titleX, 2);
    
    std::string msg = "No settings available yet!";
    show_text(msg, (width - static_cast<int>(msg.length())) / 2, height / 2);
    
    show_text("Press any key to return to menu...", 
             (width - 32) / 2, height / 2 + 2);
}

void showSettings(int& prevWidth, int& prevHeight) {
    int width, height;
    getConsoleSize(width, height);
    prevWidth = width;
    prevHeight = height;
    
    drawSettingsScreen(width, height);
    
    while (true) {
        if (_kbhit()) {
            _getch(); // Любая клавиша для выхода
            break;
        }
        
        // Проверка изменения размеров
        int newWidth, newHeight;
        getConsoleSize(newWidth, newHeight);
        if (newWidth != width || newHeight != height) {
            width = newWidth;
            height = newHeight;
            prevWidth = width;
            prevHeight = height;
            drawSettingsScreen(width, height);
        }
        
        Sleep(50);
    }
}

int main() {
    int prevWidth = 0, prevHeight = 0;

    // Меню
    std::vector<std::string> menuItems = {"Play Game", "Settings", "Exit"};
    Menu menu(menuItems);

    while (true) {
        int width, height;
        getConsoleSize(width, height);

        if (width != prevWidth || height != prevHeight) {
            prevWidth = width;
            prevHeight = height;
            clearScreen();

            // Заголовок
			std::string title = "Main Menu";
			int titleX = (width - static_cast<int>(title.length())) / 2;
			show_text(title, titleX, 2);

			// Меню
			int menuX = (width - 20) / 2; 
			int menuY = height / 2 - static_cast<int>(menuItems.size()/2);
			menu.draw(menuX, menuY);

			// Информация о движке внизу экрана
			int engineInfoX = (width - static_cast<int>(ENGINE_INFO.length())) / 2;
			show_text(ENGINE_INFO, engineInfoX, height - 2);
			
			// Информация о движке внизу экрана
			int companyInfoX = (width - static_cast<int>(COMPANY_INFO.length())) / 2;
			show_text(COMPANY_INFO, companyInfoX, height - 1);
		}

        if (_kbhit()) {
            int ch = _getch();
            if (ch == 224 || ch == 0) { 
                ch = _getch();
                if (ch == 72) { // Up arrow
                    menu.moveUp();
                } else if (ch == 80) { // Down arrow
                    menu.moveDown();
                }
                // Перерисовка после навигации
                clearScreen();
                std::string title = "Main Menu";
                int titleX = (width - static_cast<int>(title.length())) / 2;
                show_text(title, titleX, 2);
                int menuX = (width - 20) / 2; 
                int menuY = height / 2 - static_cast<int>(menuItems.size()/2);
                menu.draw(menuX, menuY);
            } else if (ch == '\r') { // Enter key
                int selectedIdx = menu.getSelectedIndex();

                if (selectedIdx == 0) { 
                    playGame(prevWidth, prevHeight);
                } else if (selectedIdx == 1) { 
                    showSettings(prevWidth, prevHeight);
                } else if (selectedIdx == 2) { 
                    break; // Выход
                }
                
                // После возврата из игры/настроек перерисовываем меню
                clearScreen();
                getConsoleSize(width, height);
                prevWidth = width;
                prevHeight = height;
                std::string title = "Main Menu";
                int titleX = (width - static_cast<int>(title.length())) / 2;
                show_text(title, titleX, 2);
                int menuX = (width - 20) / 2; 
                int menuY = height / 2 - static_cast<int>(menuItems.size()/2);
                menu.draw(menuX, menuY);
            }
        }

        Sleep(100);
    }

    return 0;
}