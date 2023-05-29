#ifndef CHARACTER_H
#define CHARACTER_H

#include <QWidget>
#include <QLabel>
#include <string>
#include <vector>
#include "mainwindow.h"

class MainWindow;

enum class Move {
    LEFT = 1,
    RIGHT,
    UP,
    DOWN
};

class Character
{
public:
    Character(std::string _url, QLabel* _label, MainWindow* _window);
    void move();
    void resetMove(Move move);
    void setMove(Move move);

private:
    std::string url;
    QLabel* label;
    std::vector <Move> moves;
    MainWindow* window;
};

#endif // CHARACTER_H
