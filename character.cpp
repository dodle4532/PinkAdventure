#include "character.h"

Character::Character(std::string _url, std::string url_2, QLabel* _label, Level* _level, QPoint _startPos, QPoint _endPos) 
{
    url =_url;
    urlMirror =url_2;
    label =_label;
    level =_level;
    jumpCount =0;
    isMirrored =false;
    startPos =_startPos;
    endPos =_endPos;
    label->move(startPos);
    label->resize(abs(endPos.rx() - startPos.rx()), abs(endPos.ry() - startPos.ry()));
    level->setPicture(url, label);
}

void Character::move(Move move) {
    for (int i = 0; i < 1; ++i) {
    if (move == Move::RIGHT) {
        startPos = QPoint(startPos.rx() + 2, startPos.ry());
        endPos = QPoint(endPos.rx() + 2, endPos.ry());
        if (level->isMovePossible()) {
            label->move(label->pos() + QPoint(2, 0));
            if (isMirrored == true) {
                level->setPicture(url, label);
            }
            isMirrored = false;
            continue;
        }
        startPos = QPoint(startPos.rx() - 2, startPos.ry());
        endPos = QPoint(endPos.rx() - 2, endPos.ry());
    }
    if (move == Move::LEFT) {
        startPos = QPoint(startPos.rx() - 2, startPos.ry());
        endPos = QPoint(endPos.rx() - 2, endPos.ry());
        if (level->isMovePossible()) {
            label->move(label->pos() + QPoint(-2, 0));
            if (isMirrored == false) {
                level->setPicture(urlMirror, label);
            }
            isMirrored = true;
            continue;
        }
        startPos = QPoint(startPos.rx() + 2, startPos.ry());
        endPos = QPoint(endPos.rx() + 2, endPos.ry());
    }
    if (move == Move::DOWN) {
        startPos = QPoint(startPos.rx(), startPos.ry() + 2);
        endPos = QPoint(endPos.rx(), endPos.ry() + 2);
        if (level->isMovePossible()) {
            if (label->pos().ry() < 611) {
                label->move(label->pos() + QPoint(0, 2));
                continue;
            }
        }
        startPos = QPoint(startPos.rx(), startPos.ry() - 2);
        endPos = QPoint(endPos.rx(), endPos.ry() - 2);
    }
    if (move == Move::UP) {
        startPos = QPoint(startPos.rx(), startPos.ry() - 5);
        endPos = QPoint(endPos.rx(), endPos.ry() - 5);
        if (level->isMovePossible()) {
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
}

void Character::move() {
    if (level->isTextLevel) {
        return;
    }
    for (Move i : moves) {
        move(i);
    }
    if (label->pos().ry() >= 900) {
        resetJumpCount();
    }
    if (level->isFinish()) {
        level->nextLevel();
        level->resetLevel();
    }
    if(level->isMovingCameraNeed()) {
        level->increaseCheckpointNumber();
        level->moveCamera();
        level->setNewCheckpoint();
    }
    if (level->isDead()) {
        level->resetLevel();
    }
    if (level->isKey()) {
        level->activateObject();
        level->keyDisappear();
    }
    if (level->isJumpReset()) {
        jumpCount = 0;
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
    if (level->isTextLevel) {
        return;
    }
    startPos = QPoint(startPos.rx(), startPos.ry() + 2);
    endPos = QPoint(endPos.rx(), endPos.ry() + 2);
    if (level->isMovePossible()) {
        label->move(label->pos() + QPoint(0, 2));
        return;
    }
    resetJumpCount();
    startPos = QPoint(startPos.rx(), startPos.ry() - 2);
    endPos = QPoint(endPos.rx(), endPos.ry() - 2);
}

int Character::getJumpCount() {
    return jumpCount;
}

void Character::increaseJumpCount() {
    jumpCount++;
}

