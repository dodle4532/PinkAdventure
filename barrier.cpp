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
