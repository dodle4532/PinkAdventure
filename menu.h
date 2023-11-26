#ifndef MENU_H
#define MENU_H

#include <QPushButton>
#include <QLabel>


class Menu
{
public:
    Menu(QPushButton* playButton, QPushButton* closeButton, QPushButton* instructionButton, QLabel* backGround);
    void setVisible(bool par);
    bool isVisible();

private:
    QPushButton* playButton;
    QPushButton* closeButton;
    QPushButton* instructionButton;
    QLabel* backGround;
};
#endif // MENU_H
