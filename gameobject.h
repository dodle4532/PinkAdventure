#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QLabel>
#include <QPoint>



class GameObject
{
public:
    GameObject();
    QPoint getStartPos() const;
    QPoint getEndPos() const;

protected:
    QLabel* label;
    QPoint startPos;
    QPoint endPos;

};

#endif // GAMEOBJECT_H
