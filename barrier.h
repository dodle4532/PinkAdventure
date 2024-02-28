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
    Barrier(QLabel* _label, QPoint _startPos, QPoint _endPos, std::string style = "");
    bool operator ==(Barrier b2);
    bool isMovePosible(QPoint _startPos, QPoint _endPos);
    bool isCrossed(QPoint _startPos, QPoint _endPos);
    void move(Move move);
    void move(QPoint pos);
    void resize(QPoint pos);
    QString text();
    bool isVisible();
    void activate();
    void deactivate();
    std::string getStyle();
    bool isNull();

private:
    std::string style;
};

#endif // BARRIRER_H
