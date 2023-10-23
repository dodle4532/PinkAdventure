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
            if (_endPos.rx() + HORIZONTAL_MOVEMENT >= startPos.rx()) {
                return false;
            }
        }

        if (_startPos.rx() >= endPos.rx()) {
            if (_startPos.rx() - HORIZONTAL_MOVEMENT <= endPos.rx()) {
                return false;
            }
        }

        if (_endPos.ry() <= startPos.ry()) {
            if (_endPos.ry() + DOWN_MOVEMENT > startPos.ry()) {
                return false;
            }
        }

        if (_startPos.ry() >= endPos.ry()) {
            if (_startPos.ry() - UP_MOVEMENT <= endPos.ry()) {
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
        startPos = QPoint(startPos.rx() + HORIZONTAL_MOVEMENT, startPos.ry());
        endPos = QPoint(endPos.rx() + HORIZONTAL_MOVEMENT, endPos.ry());
        label->move(label->pos() + QPoint(HORIZONTAL_MOVEMENT, SCREEN_BOARD_START_Y));
    }
    if (move == Move::LEFT) {
        startPos = QPoint(startPos.rx() - HORIZONTAL_MOVEMENT, startPos.ry());
        endPos = QPoint(endPos.rx() - HORIZONTAL_MOVEMENT, endPos.ry());
//        label->move(label->pos() + QPoint(-HORIZONTAL_MOVEMENT, SCREEN_BOARD_START_Y));
        label->move(startPos.rx(), startPos.ry());
    }
    if (move == Move::DOWN) {
        startPos = QPoint(startPos.rx(), startPos.ry() + DOWN_MOVEMENT);
        endPos = QPoint(endPos.rx(), endPos.ry() + DOWN_MOVEMENT);
        if (label->pos().ry() < SCREEN_BOARD_END_Y) {
            label->move(label->pos() + QPoint(SCREEN_BOARD_START_X, DOWN_MOVEMENT));
        }
    }
    if (move == Move::UP) {
        startPos = QPoint(startPos.rx(), startPos.ry() - UP_MOVEMENT);
        endPos = QPoint(endPos.rx(), endPos.ry() - UP_MOVEMENT);
        label->move(label->pos() + QPoint(SCREEN_BOARD_START_X, -UP_MOVEMENT));
    }
}

void Barrier::move(QPoint pos) {
    label->move(pos);
    startPos = pos;
    endPos = QPoint(pos.rx() + label->size().rwidth(), pos.ry() + label->size().rheight());
}

void Barrier::resize(QPoint pos) {
    int x = pos.rx() - startPos.rx();
    int y = pos.ry() - startPos.ry();
    if (x < 1 || y < 1) {
        return;
    }
    label->resize(x, y);
    endPos = pos;

}

bool Barrier::isVisible() {
    if (startPos.rx() > SCREEN_BOARD_START_X && endPos.rx() < SCREEN_BOARD_END_X &&
        startPos.ry() > SCREEN_BOARD_START_Y && endPos.ry() < SCREEN_BOARD_END_Y)
    {
        return true;
    }
    return false;
}

void Barrier::activate() {
    if (!(isVisible())) {
        startPos.rx() += PARAM_TO_OUT_OF_BOARD;
        endPos.rx() += PARAM_TO_OUT_OF_BOARD;
        label->setVisible(true);
    }
}

QString Barrier::text() {
    return label->text();
}

void Barrier::deactivate() {
    if (isVisible()) {
        startPos.rx() -= PARAM_TO_OUT_OF_BOARD;
        endPos.rx() -= PARAM_TO_OUT_OF_BOARD;
        label->setVisible(false);
    }
}
