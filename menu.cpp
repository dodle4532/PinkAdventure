#include "menu.h"

Menu::Menu(QPushButton *playButton, QPushButton *closeButton, QPushButton *instructionButton, QLabel *backGround) :
    playButton(playButton), closeButton(closeButton), instructionButton(instructionButton), backGround(backGround) {
    playButton->setStyleSheet("border-image: url(:/new/prefix1/pictures/Play.png);");
    instructionButton->setStyleSheet("border-image: url(:/new/prefix1/pictures/Information.png);");
    closeButton->setStyleSheet("border-image: url(:/new/prefix1/pictures/Home.png);");
}

void Menu::setVisible(bool par) {
    playButton->setVisible(par);
    closeButton->setVisible(par);
    instructionButton->setVisible(par);
    backGround->setVisible(par);
}

bool Menu::isVisible() {
    return playButton->isVisible();
}
