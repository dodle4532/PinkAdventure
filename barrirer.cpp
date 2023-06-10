#include "barrirer.h"

Barrirer::Barrirer(QLabel* _label, QPoint _startPos, QPoint _endPos, MainWindow* _window) :
    label(_label), startPos(_startPos), endPos(_endPos), window(_window)
{
    label->move(startPos);
    label->resizePos(startPos.rx() + endPos.rx(), startPos.ry() + endPos.ry());

}

bool Barrirer::isMovePosible(QPoint pos, Move move) const {
    if (move == Move::RIGHT) {
        if (pos.rx() == startPos.rx() - 1) {
            return true;
        }
    }

    else if (move == Move::LEFT) {
        if (pos.rx() == endPos.rx() + 1) {
            return true;
        }
    }

    else if (move == Move::DOWN) {
        if (pos.ry() == startPos.ry() - 1) {
            return true;
        }
    }

    else {
        if (pos.ry() == endPos.ry() + 1) {
            return true;
        }
    }

    return false;
}
