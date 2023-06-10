#ifndef BARRIRER_H
#define BARRIRER_H

#include "mainwindow.h"
#include <QLabel>
#include <QPoint>

class MainWindow;
enum class Move;

class Barrier
{

public:
    Barrier(QLabel* _label, QPoint _startPos, QPoint _endPos,  MainWindow* _window);
    bool isMovePosible(QPoint _startPos, QPoint _endPos);
    bool isCrossed(QPoint _startPos, QPoint _endPos);

private:
    QLabel* label;
    QPoint startPos;
    QPoint endPos;
    MainWindow* window;
};

#endif // BARRIRER_H
