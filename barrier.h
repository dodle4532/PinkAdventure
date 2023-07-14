#ifndef BARRIRER_H
#define BARRIRER_H

#include "mainwindow.h"
#include "gameobject.h"
#include <QLabel>
#include <QPoint>

class MainWindow;

class Barrier : public GameObject
{

public:
    Barrier() = default;
    Barrier(QLabel* _label, QPoint _startPos, QPoint _endPos);
    bool isMovePosible(QPoint _startPos, QPoint _endPos);
    bool isCrossed(QPoint _startPos, QPoint _endPos);
};

#endif // BARRIRER_H
