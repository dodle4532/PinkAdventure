#include "barrier.h"

Barrier::Barrier(QLabel* _label, QPoint _startPos, QPoint _endPos)
{
    label = _label;
    startPos = _startPos;
    endPos = _endPos;
    label->move(startPos);
    label->resize(abs(endPos.rx() - startPos.rx()), abs(endPos.ry() - startPos.ry()));
}

bool Barrier::isMovePosible(QPoint _startPos, QPoint _endPos) {
        if (_endPos.rx() <= startPos.rx()) {
            if (_endPos.rx() + 2 >= startPos.rx()) {
                return false;
            }
        }

        if (_startPos.rx() >= endPos.rx()) {
            if (_startPos.rx() - 2 <= endPos.rx()) {
                return false;
            }
        }

        if (_endPos.ry() <= startPos.ry()) {
            if (_endPos.ry() + 1 > startPos.ry()) {
                return false;
            }
        }

        if (_startPos.ry() >= endPos.ry()) {
            if (_startPos.ry() - 5 <= endPos.ry()) {
                return false;
            }
        }

    return true;
}

bool Barrier::isCrossed(QPoint _startPos, QPoint _endPos) {
    if (_startPos.rx() > startPos.rx() && _startPos.rx() < endPos.rx() &&
        _startPos.ry() > startPos.ry() && _startPos.ry() < endPos.ry()) {
        return true;
    }

    if (_startPos.rx() > startPos.rx() && _startPos.rx() < endPos.rx() &&
        _endPos.ry() > startPos.ry() && _endPos.ry() < endPos.ry()) {
        return true;
    }

    if (_endPos.rx() > startPos.rx() && _endPos.rx() < endPos.rx() &&
        _startPos.ry() > startPos.ry() && _startPos.ry() < endPos.ry()) {
        return true;
    }

    if (_endPos.rx() > startPos.rx() && _endPos.rx() < endPos.rx() &&
        _endPos.ry() > startPos.ry() && _endPos.ry() < endPos.ry()) {
        return true;
    }

    if (startPos.rx() > _startPos.rx() && startPos.rx() < _endPos.rx() &&
        startPos.ry() > _startPos.ry() && startPos.ry() < _endPos.ry()) {
        return true;
    }

    if (startPos.rx() > _startPos.rx() && startPos.rx() < _endPos.rx() &&
        endPos.ry() > _startPos.ry() && endPos.ry() < _endPos.ry()) {
        return true;
    }

    if (endPos.rx() > _startPos.rx() && endPos.rx() < _endPos.rx() &&
        startPos.ry() > _startPos.ry() && startPos.ry() < _endPos.ry()) {
        return true;
    }

    if (endPos.rx() > _startPos.rx() && endPos.rx() < _endPos.rx() &&
        endPos.ry() > _startPos.ry() && endPos.ry() < _endPos.ry()) {
        return true;
    }
    return false;
}

void Barrier::move(Move move) {
    if (move == Move::RIGHT) {
        startPos = QPoint(startPos.rx() + 2, startPos.ry());
        endPos = QPoint(endPos.rx() + 2, endPos.ry());
        label->move(label->pos() + QPoint(2, 0));
    }
    if (move == Move::LEFT) {
        startPos = QPoint(startPos.rx() - 2, startPos.ry());
        endPos = QPoint(endPos.rx() - 2, endPos.ry());
        label->move(label->pos() + QPoint(-2, 0));
    }
    if (move == Move::DOWN) {
        startPos = QPoint(startPos.rx(), startPos.ry() + 2);
        endPos = QPoint(endPos.rx(), endPos.ry() + 2);
        if (label->pos().ry() < 611) {
            label->move(label->pos() + QPoint(0, 2));
        }
    }
    if (move == Move::UP) {
        startPos = QPoint(startPos.rx(), startPos.ry() - 5);
        endPos = QPoint(endPos.rx(), endPos.ry() - 5);
        label->move(label->pos() + QPoint(0, -5));
    }
}

bool Barrier::isVisible() {
    if (startPos.rx() > 0 && endPos.rx() < 1920 &&
        startPos.ry() > 0 && endPos.ry() < 900)
    {
        return true;
    }
    return false;
}

void Barrier::activate() {
    if (!(isVisible())) {
        startPos.rx() += 2000;
        endPos.rx() += 2000;
        label->setVisible(true);
    }
}

void Barrier::deactivate() {
    if (isVisible()) {
        startPos.rx() -= 2000;
        endPos.rx() -= 2000;
        label->setVisible(false);
    }
}
