#include "character.h"
#include "mainwindow.h"
#include <QPicture>

std::string charMovementPic[] = {":/new/prefix1/pictures/Pink_Monster.png",
                                 ":/new/prefix1/pictures/Pink_Monster_Run_1.png",
                            ":/new/prefix1/pictures/Pink_Monster_Run_2.png",
                                 ":/new/prefix1/pictures/Pink_Monster_Run_3.png",
                            ":/new/prefix1/pictures/Pink_Monster_Run_4.png",
                                 ":/new/prefix1/pictures/Pink_Monster_Run_5.png",
                            ":/new/prefix1/pictures/Pink_Monster_Run_6.png"};
std::string charMovementPicReversed[] = {":/new/prefix1/pictures/m_Pink_Monster.png", ":/new/prefix1/pictures/m_Pink_Monster_Run_1.png",
                            ":/new/prefix1/pictures/m_Pink_Monster_Run_2.png", ":/new/prefix1/pictures/m_Pink_Monster_Run_3.png",
                            ":/new/prefix1/pictures/m_Pink_Monster_Run_4.png", ":/new/prefix1/pictures/m_Pink_Monster_Run_5.png",
                            ":/new/prefix1/pictures/m_Pink_Monster_Run_6.png"};

std::string charJumpPic[] = {":/new/prefix1/pictures/Pink_Monster_Jump_4.png", ":/new/prefix1/pictures/Pink_Monster_Jump_5.png",
                         ":/new/prefix1/pictures/Pink_Monster_Jump_6.png", ":/new/prefix1/pictures/Pink_Monster_Jump_7.png",
                            ":/new/prefix1/pictures/Pink_Monster.png"};


std::string charJumpPicReversed[] = {":/new/prefix1/pictures/m_Pink_Monster_Jump_4.png", ":/new/prefix1/pictures/m_Pink_Monster_Jump_5.png",
                                ":/new/prefix1/pictures/m_Pink_Monster_Jump_6.png", ":/new/prefix1/pictures/m_Pink_Monster_Jump_7.png",
                                    ":/new/prefix1/pictures/m_Pink_Monster.png"};

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
    label->setPixmap(QPixmap(QString::fromStdString(url)));
//    label->setScaledContents(true);
//    label->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    MainWindow::setPicture(url, label);
}

void Character::setLevel(Level *level) {
    this->level = level;
}

void Character::move(Move move) {
    if (move == Move::RIGHT) {
        if (level->isMovePossible(move)) {
            if (isMirrored == true) {
                level->setPicture(url, label);
            }
            isMirrored = false;
            if (startPos.rx() > SCREEN_BOARD_END_X * CAMERA_MOVE_PAR_RIGHT_X &&
                    level->getRightPosX() > SCREEN_BOARD_END_X * CAMERA_MOVE_PAR_RIGHT_Y
                && level->isMoveCameraNeeded) {
                changeMovePic();
                level->moveAllObjects(Move::LEFT);
                return;
            }
            startPos = QPoint(startPos.rx() + HORIZONTAL_MOVEMENT, startPos.ry());
            endPos = QPoint(endPos.rx() + HORIZONTAL_MOVEMENT, endPos.ry());
            label->move(label->pos() + QPoint(HORIZONTAL_MOVEMENT, SCREEN_BOARD_START_Y));
            changeMovePic();
            return;
        }
    }
    if (move == Move::LEFT) {
        if (level->isMovePossible(move)) {
            if (isMirrored == false) {
                level->setPicture(urlMirror, label);
            }
            isMirrored = true;
            if (startPos.rx() < SCREEN_BOARD_END_X * CAMERA_MOVE_PAR_LEFT_X
                    && level->getLeftPosX() < SCREEN_BOARD_END_X * CAMERA_MOVE_PAR_LEFT_Y
                && level->isMoveCameraNeeded) {
                level->moveAllObjects(Move::RIGHT);
                changeMovePic();
                return;
            }
            startPos = QPoint(startPos.rx() - HORIZONTAL_MOVEMENT, startPos.ry());
            endPos = QPoint(endPos.rx() - HORIZONTAL_MOVEMENT, endPos.ry());
            label->move(label->pos() + QPoint(-HORIZONTAL_MOVEMENT, SCREEN_BOARD_START_Y));
            changeMovePic();
            return;
        }
    }
    if (move == Move::DOWN) {
        if (level->isMovePossible(move)) {
            startPos = QPoint(startPos.rx(), startPos.ry() + DOWN_MOVEMENT);
            endPos = QPoint(endPos.rx(), endPos.ry() + DOWN_MOVEMENT);
            label->move(label->pos() + QPoint(SCREEN_BOARD_START_X, DOWN_MOVEMENT));
            changeJumpPic(2);
            return;
        }
        changeJumpPic(4);
    }
    if (move == Move::UP) {
        if (level->isMovePossible(move)) {
            startPos = QPoint(startPos.rx(), startPos.ry() - UP_MOVEMENT);
            endPos = QPoint(endPos.rx(), endPos.ry() - UP_MOVEMENT);
            label->move(label->pos() + QPoint(SCREEN_BOARD_START_Y, -UP_MOVEMENT));
            jumpCount++;
           // changeJumpPic();
            return;
        }
    }
}

void Character::changeMovePic() {
    if (isMirrored) {
        MainWindow::setPicture(charMovementPicReversed[picIndex], label);
    }
    else {
        MainWindow::setPicture(charMovementPic[picIndex], label);
    }
    picIndex++;
    if (picIndex > 6) {
        picIndex = 0;
    }
}

void Character::changeJumpPic(int index) {
    if (index < 0) {
        index = (jumpCount / 10) % 4;
    }
    if (level->isJumpReset() && index != 3 && moves.find(Move::UP) == moves.end()) {
        return;
    }
    if (isMirrored) {
        MainWindow::setPicture(charJumpPicReversed[index], label);
    }
    else {
        MainWindow::setPicture(charJumpPic[index], label);
    }
    if (picIndex > 6) {
        picIndex = 1;
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
    if (level->isCheckpoint()) {
        level->increaseCheckpointNumber();
 //       level->moveCamera();
        level->setNewCheckpoint();
    }
//    if(level->isMovingCameraNeed()) {
//        level->increaseCheckpointNumber();
//        level->moveCamera();
//        level->setNewCheckpoint();
//    }
    if (level->isDead()) {
        level->resetLevel();
    }
    if (level->isKey()) {
        level->activateObject();
        level->keyDisappear();
    }
    if (level->isJumpReset()) {
        jumpCount = 1; // Не 0 что б не пересекалась со случаем, когда падаешь с объекта
        changeJumpPic(3);
    }
}

void Character::resetMove(Move move) {
    moves.erase(move);
    if (move == Move::LEFT || move == Move::RIGHT) {
        picIndex = 0;
        changeMovePic();
    }
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
    if (level->isMovePossible(Move::DOWN)) {
        startPos = QPoint(startPos.rx(), startPos.ry() + FALL_MOVEMENT);
        endPos = QPoint(endPos.rx(), endPos.ry() + FALL_MOVEMENT);
        label->move(label->pos() + QPoint(SCREEN_BOARD_START_X, FALL_MOVEMENT));
        if (jumpCount == 0) {
            jumpCount = MAX_JUMP_COUNT;
        }
        changeJumpPic(2);
        return;
    }
    if (moves.find(Move::RIGHT) == moves.end() && moves.find(Move::LEFT) == moves.end()) {
        changeJumpPic(4);
    }
    resetJumpCount();
}

int Character::getJumpCount() {
    return jumpCount;
}

void Character::increaseJumpCount() {
    jumpCount++;
}

void Character::setMirrored(bool par) {
    isMirrored = par;
}
