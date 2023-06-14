#include "character.h"

Character::Character(std::string _url, std::string url_2, QLabel* _label, MainWindow* _window, QPoint _startPos, QPoint _endPos) :
    url(_url), urlMirror(url_2), label(_label), window(_window), jumpCount(0), isMirrored(false), startPos(_startPos), endPos(_endPos)
{
    label->move(startPos);
    label->resize(abs(endPos.rx() - startPos.rx()), abs(endPos.ry() - startPos.ry()));
    window->setPicture(url, label);
}

void Character::move() {
    for (Move i : moves) {
        if (i == Move::RIGHT) {
            startPos = QPoint(startPos.rx() + 2, startPos.ry());
            endPos = QPoint(endPos.rx() + 2, endPos.ry());
            if (window->isMovePossible()) {
                label->move(label->pos() + QPoint(2, 0));
                if (isMirrored == true) {
                    window->setPicture(url, label);
                }
                isMirrored = false;
                continue;
            }
            startPos = QPoint(startPos.rx() - 2, startPos.ry());
            endPos = QPoint(endPos.rx() - 2, endPos.ry());
        }
        if (i == Move::LEFT) {
            startPos = QPoint(startPos.rx() - 2, startPos.ry());
            endPos = QPoint(endPos.rx() - 2, endPos.ry());
            if (window->isMovePossible()) {
                label->move(label->pos() + QPoint(-2, 0));
                if (isMirrored == false) {
                    window->setPicture(urlMirror, label);
                }
                isMirrored = true;
                continue;
            }
            startPos = QPoint(startPos.rx() + 2, startPos.ry());
            endPos = QPoint(endPos.rx() + 2, endPos.ry());
        }
        if (i == Move::DOWN) {
            startPos = QPoint(startPos.rx(), startPos.ry() + 2);
            endPos = QPoint(endPos.rx(), endPos.ry() + 2);
            if (window->isMovePossible()) {
                if (label->pos().ry() < 611) {
                    label->move(label->pos() + QPoint(0, 2));
                    continue;
                }
            }
            startPos = QPoint(startPos.rx(), startPos.ry() - 2);
            endPos = QPoint(endPos.rx(), endPos.ry() - 2);
        }
        if (i == Move::UP) {
            startPos = QPoint(startPos.rx(), startPos.ry() - 5);
            endPos = QPoint(endPos.rx(), endPos.ry() - 5);
            if (window->isMovePossible()) {
                if (jumpCount < 50) {
                    label->move(label->pos() + QPoint(0, -5));
                    jumpCount++;
                    continue;
                }
            }
            startPos = QPoint(startPos.rx(), startPos.ry() + 5);
            endPos = QPoint(endPos.rx(), endPos.ry() + 5);
        }
    }
    if (label->pos().ry() >= 900) {
        resetJumpCount();
    }
}

void Character::resetMove(Move move) {
    moves.erase(move);
}

void Character::setMove(Move move) {
    moves.insert(move);
}

void Character::resetJumpCount() {
    jumpCount = 0;
}

void Character::fall() {
    startPos = QPoint(startPos.rx(), startPos.ry() + 2);
    endPos = QPoint(endPos.rx(), endPos.ry() + 2);
    if (window->isMovePossible()) {
        label->move(label->pos() + QPoint(0, 2));
        return;
    }
    resetJumpCount();
    startPos = QPoint(startPos.rx(), startPos.ry() - 2);
    endPos = QPoint(endPos.rx(), endPos.ry() - 2);
}

QPoint Character::getStartPos() const {
    return startPos;
}

QPoint Character::getEndPos() const {
    return endPos;
}
