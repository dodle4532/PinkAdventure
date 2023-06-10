#ifndef BARRIRER_H
#define BARRIRER_H

#include "mainwindow.h"
#include <QLabel>
#include <QPoint>

enum class Move {
    LEFT = 1,
    DOWN,
    RIGHT,
    UP
};

class Barrirer
{

public:
    Barrirer(QLabel* _label, QPoint _startPos, QPoint _endPos,  MainWindow* _window);
    bool isMovePosible(QPoint pos, Move move) const;

private:
    QLabel* label;
    QPoint startPos;
    QPoint endPos;
    MainWindow* window;
};

#endif // BARRIRER_H