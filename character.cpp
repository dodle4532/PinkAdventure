#include "character.h"

Character::Character(std::string _url, std::string url_2, QLabel* _label, QPoint _startPos, QPoint _endPos,
                     Level* level)
{
    url =_url;
    urlMirror =url_2;
    this->level = level;
    label =_label;
    jumpCount =0;
    isMirrored =false;
    startPos =_startPos;
    endPos =_endPos;
    label->move(startPos);
    label->resize(abs(endPos.rx() - startPos.rx()), abs(endPos.ry() - startPos.ry()));
    level->setPicture(url, label);
}

void Character::setLevel(Level *level) {
    this->level = level;
}

void Character::move(Move move) {
    if (move == Move::RIGHT) {
        startPos = QPoint(startPos.rx() + HORIZONTAL_MOVEMENT, startPos.ry());
        endPos = QPoint(endPos.rx() + HORIZONTAL_MOVEMENT, endPos.ry());
        if (level->isMovePossible()) {
            if (startPos.rx() > SCREEN_BOARD_END_X * 0.45 && level->getRightPosX() > SCREEN_BOARD_END_X * 0.9) {
                level->moveAllObjects(Move::LEFT);
                startPos = QPoint(startPos.rx() - HORIZONTAL_MOVEMENT, startPos.ry());
                endPos = QPoint(endPos.rx() - HORIZONTAL_MOVEMENT, endPos.ry());
                return;
            }
            label->move(label->pos() + QPoint(HORIZONTAL_MOVEMENT, SCREEN_BOARD_START_Y));
            if (isMirrored == true) {
                level->setPicture(url, label);
            }
            isMirrored = false;
            return;
        }
        startPos = QPoint(startPos.rx() - HORIZONTAL_MOVEMENT, startPos.ry());
        endPos = QPoint(endPos.rx() - HORIZONTAL_MOVEMENT, endPos.ry());
    }
    if (move == Move::LEFT) {
        startPos = QPoint(startPos.rx() - HORIZONTAL_MOVEMENT, startPos.ry());
        endPos = QPoint(endPos.rx() - HORIZONTAL_MOVEMENT, endPos.ry());
        if (level->isMovePossible()) {
            if (startPos.rx() < SCREEN_BOARD_END_X * 0.3 && level->getLeftPosX() < SCREEN_BOARD_END_X * 0.1) {
                level->moveAllObjects(Move::RIGHT);
                startPos = QPoint(startPos.rx() + HORIZONTAL_MOVEMENT, startPos.ry());
                endPos = QPoint(endPos.rx() + HORIZONTAL_MOVEMENT, endPos.ry());
                return;
            }
            label->move(label->pos() + QPoint(-HORIZONTAL_MOVEMENT, SCREEN_BOARD_START_Y));
            if (isMirrored == false) {
                level->setPicture(urlMirror, label);
            }
            isMirrored = true;
            return;
        }
        startPos = QPoint(startPos.rx() + HORIZONTAL_MOVEMENT, startPos.ry());
        endPos = QPoint(endPos.rx() + HORIZONTAL_MOVEMENT, endPos.ry());
    }
    if (move == Move::DOWN) {
        startPos = QPoint(startPos.rx(), startPos.ry() + DOWN_MOVEMENT);
        endPos = QPoint(endPos.rx(), endPos.ry() + DOWN_MOVEMENT);
        if (level->isMovePossible()) {
            if (label->pos().ry() < SCREEN_BOARD_END_Y) {
                label->move(label->pos() + QPoint(SCREEN_BOARD_START_X, DOWN_MOVEMENT));
                return;
            }
        }
        startPos = QPoint(startPos.rx(), startPos.ry() - DOWN_MOVEMENT);
        endPos = QPoint(endPos.rx(), endPos.ry() - DOWN_MOVEMENT);
    }
    if (move == Move::UP) {
        startPos = QPoint(startPos.rx(), startPos.ry() - UP_MOVEMENT);
        endPos = QPoint(endPos.rx(), endPos.ry() - UP_MOVEMENT);
        if (level->isMovePossible()) {
            if (jumpCount < MAX_JUMP_COUNT) {
                label->move(label->pos() + QPoint(SCREEN_BOARD_START_Y, -UP_MOVEMENT));
                jumpCount++;
                return;
            }
        }
        startPos = QPoint(startPos.rx(), startPos.ry() + UP_MOVEMENT);
        endPos = QPoint(endPos.rx(), endPos.ry() + UP_MOVEMENT);
    }
}

void Character::move() {
    if (level->isTextLevel) {
        return;
    }
    for (Move i : moves) {
        move(i);
    }
    if (label->pos().ry() >= SCREEN_BOARD_END_Y) {
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
        jumpCount = 1; // Не 0 что б не пересекалась со случаем, когда падаешь с объекта
    }
}

void Character::resetMove(Move move) {
    moves.erase(move);
    if (move == Move::UP) {
        jumpCount = MAX_JUMP_COUNT;
    }
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
    startPos = QPoint(startPos.rx(), startPos.ry() + FALL_MOVEMENT);
    endPos = QPoint(endPos.rx(), endPos.ry() + FALL_MOVEMENT);
    if (level->isMovePossible()) {
        label->move(label->pos() + QPoint(SCREEN_BOARD_START_X, FALL_MOVEMENT));
        if (jumpCount == 0) {
            jumpCount = MAX_JUMP_COUNT;
        }
        return;
    }
    resetJumpCount();
    startPos = QPoint(startPos.rx(), startPos.ry() - FALL_MOVEMENT);
    endPos = QPoint(endPos.rx(), endPos.ry() - FALL_MOVEMENT);
}

int Character::getJumpCount() {
    return jumpCount;
}

void Character::increaseJumpCount() {
    jumpCount++;
}
