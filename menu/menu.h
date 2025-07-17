#ifndef MENU_H
#define MENU_H

#include <vector>
#include <string>

class Button {
public:
    std::string text;
    bool selected;

    Button(const std::string &txt) : text(txt), selected(false) {}
};

class Menu {
private:
    std::vector<Button> buttons;
    int currentIndex;
    char symbolSelected;   // символ для выбранной кнопки (например, '*')
    char symbolUnselected; // символ для невыбранных (например, ' ')
public:
    Menu(const std::vector<std::string> &buttonTexts,
         char selectedSymbol='*',
         char unselectedSymbol=' ');
    void draw(int x, int y);
    void moveUp();
    void moveDown();
    int getSelectedIndex() const;
};

#endif // MENU_H