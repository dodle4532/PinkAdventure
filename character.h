#ifndef CHARACTER_H
#define CHARACTER_H

#include <QWidget>
#include <QLabel>
#include <string>
#include <vector>
#include <set>
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
    Character(std::string _url, std::string url_2, QLabel* _label, MainWindow* _window, QPoint _startPos, QPoint _endPos);
    void move();
    void resetMove(Move move);
    void setMove(Move move);
    void fall();
    QPoint getStartPos() const;
    QPoint getEndPos() const;
    void resetJumpCount();

private:
    std::string url;
    std::string urlMirror;
    QLabel* label;
    std::set <Move> moves;
    MainWindow* window;
    QPoint startPos;
    QPoint endPos;

    int jumpCount;
    bool isMirrored;
};

#endif // CHARACTER_H
