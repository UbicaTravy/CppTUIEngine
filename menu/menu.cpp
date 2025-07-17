#include "menu.h"
#include "../console_utils.h"
#include <iostream>

Menu::Menu(const std::vector<std::string> &buttonTexts,
           char selectedSymbol,
           char unselectedSymbol)
    : symbolSelected(selectedSymbol),
      symbolUnselected(unselectedSymbol),
      currentIndex(0)
{
    for (const auto &txt : buttonTexts) {
        buttons.emplace_back(txt);
    }
    if (!buttons.empty()) {
        buttons[0].selected = true;
    }
}

void Menu::draw(int x, int y) {
    for (size_t i=0; i<buttons.size(); ++i) {
        std::string line;
        if (buttons[i].selected)
            line += symbolSelected;
        else
            line += ' ';

        line += " " + buttons[i].text;

        show_text(line, x, y + i);
    }
}

void Menu::moveUp() {
    if (buttons.empty()) return;
    buttons[currentIndex].selected = false;
    if (currentIndex == 0)
        currentIndex = buttons.size() -1;
    else
        --currentIndex;
    buttons[currentIndex].selected = true;
}

void Menu::moveDown() {
    if (buttons.empty()) return;
    buttons[currentIndex].selected = false;
    currentIndex = (currentIndex +1) % buttons.size();
    buttons[currentIndex].selected = true;
}

int Menu::getSelectedIndex() const {
    return currentIndex;
}