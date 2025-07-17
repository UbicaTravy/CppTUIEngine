#include "../console_utils.h"
#include "../menu/menu.h"
#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>
#include <cstdlib> // для system()

const std::string ENGINE_INFO = "Powered by CppTUI Engine (github.com/UbicaTravy/CppTUI)";
const std::string COMPANY_INFO = "Maked by ANTI-TERROR Studio, 2025";

void executeCommand(const std::string& command) {
    system(command.c_str());
}

void buildRelease(int& prevWidth, int& prevHeight) {
    int width, height;
    getConsoleSize(width, height);
    prevWidth = width;
    prevHeight = height;
    
    clearScreen();
    
    std::string title = "Building Release Version";
    int titleX = (width - static_cast<int>(title.length())) / 2;
    show_text(title, titleX, 2);
    
    std::string msg = "Compiling with static linking...";
    show_text(msg, (width - static_cast<int>(msg.length())) / 2, height / 2);
    
    // Выполняем команду компиляции
    executeCommand("g++ -static -o build/mygame main.cpp console_utils.cpp menu/menu.cpp -std=c++17");
    
    show_text("Build completed!", (width - 15) / 2, height / 2 + 2);
    show_text("Press any key to return to menu...", (width - 32) / 2, height / 2 + 4);
    
    _getch();
}

void buildAndRun(int& prevWidth, int& prevHeight) {
    int width, height;
    getConsoleSize(width, height);
    prevWidth = width;
    prevHeight = height;
    
    clearScreen();
    
    std::string title = "Building and Running";
    int titleX = (width - static_cast<int>(title.length())) / 2;
    show_text(title, titleX, 2);
    
    std::string msg = "Compiling and running the game...";
    show_text(msg, (width - static_cast<int>(msg.length())) / 2, height / 2);
    
    // Выполняем команды компиляции и запуска
    executeCommand("g++ -o mygame main.cpp console_utils.cpp menu/menu.cpp -std=c++17");
    executeCommand("mygame");
	
    clearScreen();
    show_text("Press any key to return to menu...", (width - 32) / 2, height / 2 + 2);
    
    _getch();
}

void runGame(int& prevWidth, int& prevHeight) {
    int width, height;
    getConsoleSize(width, height);
    prevWidth = width;
    prevHeight = height;
    
    clearScreen();
    
    std::string title = "Running Game";
    int titleX = (width - static_cast<int>(title.length())) / 2;
    show_text(title, titleX, 2);
    
    std::string msg = "Starting the game...";
    show_text(msg, (width - static_cast<int>(msg.length())) / 2, height / 2);
    
    // Выполняем команду запуска
    executeCommand("mygame");
    
    show_text("Press any key to return to menu...", (width - 32) / 2, height / 2 + 2);
    
    _getch();
}

void drawMainMenu(int width, int height, Menu& menu) {
    clearScreen();
    
    // Заголовок
    std::string title = "CppTUI Build Tool v1.0 (for CppTUI Engine v0.12)";
    int titleX = (width - static_cast<int>(title.length())) / 2;
    show_text(title, titleX, 2);

    // Меню
    int menuX = (width - 30) / 2; 
    int menuY = height / 2 - 2;
    menu.draw(menuX, menuY);

    // Информация о движке внизу экрана
    int engineInfoX = (width - static_cast<int>(ENGINE_INFO.length())) / 2;
    show_text(ENGINE_INFO, engineInfoX, height - 2);
    
    // Информация о компании внизу экрана
    int companyInfoX = (width - static_cast<int>(COMPANY_INFO.length())) / 2;
    show_text(COMPANY_INFO, companyInfoX, height - 1);
}

int main() {
    int prevWidth = 0, prevHeight = 0;
    
    setColor(15, 1); // Белый текст на синем фоне

    // Меню
    std::vector<std::string> menuItems = {
        "1. Build Release (static)",
        "2. Build and Run",
        "3. Run Game",
        "4. Exit"
    };
    Menu menu(menuItems);

    while (true) {
        int width, height;
        getConsoleSize(width, height);

        if (width != prevWidth || height != prevHeight) {
            prevWidth = width;
            prevHeight = height;
            drawMainMenu(width, height, menu);
        }

        if (_kbhit()) {
            int ch = _getch();
            if (ch == 224 || ch == 0) { 
                ch = _getch();
                if (ch == 72) { // Up arrow
                    menu.moveUp();
                    drawMainMenu(width, height, menu);
                } else if (ch == 80) { // Down arrow
                    menu.moveDown();
                    drawMainMenu(width, height, menu);
                }
            } else if (ch == '\r') { // Enter key
                int selectedIdx = menu.getSelectedIndex();

                if (selectedIdx == 0) { 
                    buildRelease(prevWidth, prevHeight);
                } else if (selectedIdx == 1) { 
                    buildAndRun(prevWidth, prevHeight);
                } else if (selectedIdx == 2) { 
                    runGame(prevWidth, prevHeight);
                } else if (selectedIdx == 3) { 
                    break; // Выход
                }
                
                // После возврата перерисовываем меню
                getConsoleSize(width, height);
                prevWidth = width;
                prevHeight = height;
                drawMainMenu(width, height, menu);
            }
        }

    }

    return 0;
}