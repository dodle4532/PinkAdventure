#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "header.h"

#include <QLabel>
#include <QPoint>

enum class Move {
    LEFT = 1,
    RIGHT,
    UP,
    DOWN
};

class GameObject
{
public:
    GameObject() = default;
    QPoint getStartPos() const;
    QPoint getEndPos() const;

protected:
    QLabel* label;
    QPoint startPos;
    QPoint endPos;

};

#endif // GAMEOBJECT_H
