#include "gameobject.h"

QPoint GameObject::getStartPos() const {
    return startPos;
}

QPoint GameObject::getEndPos() const {
    return endPos;
}

void GameObject::setVisible(bool par) {
    label->setVisible(par);
}
