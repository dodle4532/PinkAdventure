#include "menu.h"

Menu::Menu(QPushButton *playButton, QPushButton *closeButton, QPushButton *instructionButton, QLabel *backGround) :
    playButton(playButton), closeButton(closeButton), instructionButton(instructionButton), backGround(backGround) {}

void Menu::setVisible(bool par) {
    playButton->setVisible(par);
    closeButton->setVisible(par);
    instructionButton->setVisible(par);
    backGround->setVisible(par);
}

bool Menu::isVisible() {
    return playButton->isVisible();
}
