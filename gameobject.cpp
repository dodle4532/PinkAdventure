#include "gameobject.h"

GameObject::GameObject()
{

}

QPoint GameObject::getStartPos() const {
    return startPos;
}

QPoint GameObject::getEndPos() const {
    return endPos;
}
