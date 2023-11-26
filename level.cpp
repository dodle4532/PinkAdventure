#include "level.h"
#include <QTimer>
#include <fstream>
#include <sstream>
#include <iostream>
extern QString buttonsLabels[];

Level::Level(Character* _character, std::vector <Barrier*> _barriers, MainWindow* _window) :
    character(_character), barriers(_barriers), window(_window)
{
//    QTimer *timer = new QTimer(this);
//    connect(timer, SIGNAL(timeout()), this, SLOT(fall()));
//    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
//    timer->start(5);
}

void parse(std::string style, std::string& str, Barrier*& barrier, int& i, MainWindow* window,
           std::string& startX, std::string& startY, std::string& endX, std::string& endY) {
    window->labels[i]->setStyleSheet(QString::fromStdString(style));
    std::stringstream ss;
    ss.str(str);
    std::getline(ss, startX, ' ');
    std::getline(ss, startY, ' ');
    std::getline(ss, endX, ' ');
    std::getline(ss, endY, ' ');
    barrier = new Barrier(window->labels[i],
                         QPoint(std::stoi(startX), std::stoi(startY)), QPoint(std::stoi(endX), std::stoi(endY)));
    std::getline(ss, style, '"');
    std::getline(ss, style, '"');
    if (style != "") {
        window->labels[i]->setStyleSheet(QString::fromStdString(style));
    }
    ++i;
}

void Level::setLeftAndRight(Barrier* i, int& min, int& max) {
    if (i == nullptr) {
        return;
    }
    int start = i->getStartPos().rx();
    int end = i->getEndPos().rx();
    if (end > max) {
        rightObject = i;
        max = end;
    }
    if (start < min) {
        leftObject = i;
        min = start;
    }
}

void Level::updateLeftAndRightObject() {
    int max = 0; int min = 9999999;
    for (auto & i : barriers) {
        setLeftAndRight(i, min, max);
    }
    for (auto & i : otherObjects) {
        setLeftAndRight(i, min, max);
    }
    for (auto & i : killingObjects) {
        setLeftAndRight(i, min, max);
    }
    for (auto & i : jumpingObjects) {
        setLeftAndRight(i, min, max);
    }
}

Level::Level(std::string path, MainWindow* _window, std::vector<QLabel*> background) :
     window(_window), background(background)
{
    labelMaxIndex = 0;
    QLabel* label = window->labels[99];
    label->setStyleSheet("background-color: 'transparent';");
    labelMaxIndex++;
    std::pair<QPoint, QPoint> charCheckPointPos = window->getCheckpoint();
    character = new Character(":/new/prefix1/pictures/Pink_Monster.png",
                              ":/new/prefix1/pictures/m_Pink_Monster.png",  label,
                              charCheckPointPos.first, charCheckPointPos.second, this);
//    int minStartX = SCREEN_BOARD_END_X;
//    int maxEndX = SCREEN_BOARD_START_X;
    otherObjects.resize(OTHER_OBJECTS_COUNT, nullptr);
    changingObject = nullptr;
    std::ifstream fd;
    std::string str;
    //std::stringstream ss;
    std::string startX;
    std::string startY;
    std::string endX;
    std::string endY;
    fd.open(path);
    if (!(fd.is_open())) {
        std::exit(0);
    }
    std::getline(fd, str);


    // Мэйби под одну функцию


    if (str == "Text:") {
        while (!(fd.eof() || str == "Barriers:")) {
            std::getline(fd, str);
            if (str == "Barriers:") {
                break;
            }
            std::stringstream ss;
            std::string style;
            ss.str(str);
            std::getline(ss, startX, ' ');
            std::getline(ss, startY, ' ');
            std::getline(ss, endX, ' ');
            std::getline(ss, endY, ' ');

            std::getline(ss, style, '"');
            std::getline(ss, style, '"');
            window->labels[labelMaxIndex]->setText(QString::fromStdString(style));
            window->labels[labelMaxIndex]->setStyleSheet("color: rgb(0, 0, 250);font-size:50px");

            Barrier* barrier = new Barrier(window->labels[labelMaxIndex],
                                 QPoint(std::stoi(startX), std::stoi(startY)),
                                 QPoint(std::stoi(endX), std::stoi(endY)));
            text.push_back(barrier);
            ++labelMaxIndex;
            if (str == "") {
                break;
            }
        }
    }
    if (fd.eof()) {
        isTextLevel = true;
        return;
    }
    if (str == "Barriers:" || str == "Barriers:\n") {
        while (!(fd.eof())) {
            std::getline(fd, str);
            if (str == "Finish:" || str == "Finish\n") {
                break;
            }
            Barrier* barrier;
            parse(BARRIER_LABEL, str, barrier, labelMaxIndex, window,
                  startX, startY, endX, endY);
            barriers.push_back(barrier);
        }
    }

    //Finish
    std::getline(fd, str);
    parse("background-color: rgb(170, 0, 0);", str, otherObjects[0], labelMaxIndex, window,
          startX, startY, endX, endY);

    // MovingObject
    std::getline(fd, str);
    if (str == "MovingObjects:" || str == "MovingObjects:\n") {
        std::getline(fd, str);
            parse(MOVING_OBJECT_LABEL, str, otherObjects[1], labelMaxIndex, window,
                  startX, startY, endX, endY);
//        otherObjects[1] = new Barrier(new QLabel,
//                                  QPoint(1, 1), QPoint(1, 1));
    }
//    else {
//        otherObjects[1] = new Barrier(new QLabel,
//                                  QPoint(1, 1), QPoint(1, 1));
//    }

    //KillingObjects
    int j = 0;
    std::getline(fd, str);
    if (str == "KillingObjects:") {
        while(!(fd.eof())) {
            std::getline(fd,str);
            if (fd.eof()) {
                break;
            }
            if (str == "JumpingObjects:" || str == "/") {
                break;
            }
            killingObjects.resize(killingObjects.size() + 1);
            parse(KILLING_OBJECT_LABEL, str, killingObjects[j], labelMaxIndex, window,
                  startX, startY, endX, endY);
            ++j;
        }
    }
    if (str == "/") {
        std::getline(fd,str);
    }
    j = 0;
    if (str == "JumpingObjects:") {
        while(!(fd.eof())) {
            std::getline(fd,str);
            if (fd.eof()) {
                break;
            }
            if (str == "KeyObjects:" || str == "/") {
                break;
            }
            jumpingObjects.resize(jumpingObjects.size() + 1);
            parse(JUMPING_OBJECT_LABEL, str, jumpingObjects[j], labelMaxIndex, window,
                  startX, startY, endX, endY);
            ++j;
        }
    }
    if (str == "/") {
        std::getline(fd,str);
    }
    if (str == "KeyObjects:" || str == "KeyObjects:\n") {
        std::getline(fd, str);
//        parse("background-color: rgb(170, 100, 170);", str, otherObjects[2], i, window,
//              startX, startY, endX, endY);
        std::string elemIndex;
        std::stringstream ss;
        ss.str(str);
        window->labels[labelMaxIndex]->setStyleSheet(KEY_OBJECT_LABEL);
        ss.str(str);
        std::getline(ss, startX, ' ');
        std::getline(ss, startY, ' ');
        std::getline(ss, endX, ' ');
        std::getline(ss, endY, ' ');
        otherObjects[2] = new Barrier(window->labels[labelMaxIndex],
                             QPoint(std::stoi(startX), std::stoi(startY)),
                                    QPoint(std::stoi(endX), std::stoi(endY)));

        //Доработать
//        std::getline(ss, elemIndex, ' ');
//        std::getline(ss, elemIndex, ' ');
//        std::getline(ss, elemIndex, ' ');
//        std::getline(ss, elemIndex, ' ');
        std::getline(ss, elemIndex, ' ');
        keyConnectedObject = barriers[std::stoi(elemIndex) - 1];
        deactivateObject();
        std::string style;
        std::getline(ss, style, '"');
        std::getline(ss, style, '"');
        if (style != "") {
            window->labels[labelMaxIndex]->setStyleSheet(QString::fromStdString(style));
        }
    }
    else {
        otherObjects[2] = nullptr;
        keyConnectedObject = nullptr;
    }
    labelMaxIndex++;
    updateLeftAndRightObject();
    isMoveCameraNeeded = isMovingCameraNeed();
    for (auto & i : background) {
        i->setVisible(true);
    }

}

void Level::fall() {
    if (character != nullptr)
        character->fall();
}

void Level::move() {
    if (character != nullptr)
        character->move();
}

void Level::setMove(Move move) {
    character->setMove(move);
}

void Level::resetMove(Move move) {
    character->resetMove(move);
}

QPoint Level::getCharStartPos() {
    return character->getStartPos() + QPoint(HITBOX_CORRECTION_X, 0); // Поправка под хитбоксы
}

QPoint Level::getCharEndPos() {
    return character->getEndPos() - QPoint(HITBOX_CORRECTION_X, 0); // Поправка под хитбоксы
}

bool Level::isDead() {
    for (auto & i : killingObjects) {
        if (i->isCrossed(this->getCharStartPos(), this->getCharEndPos())) {
            return true;
        }
    }
    return false;
}

bool Level::isJumpReset() {
    for (auto & i : jumpingObjects) {
        if (i->isCrossed(this->getCharStartPos(), this->getCharEndPos())) {
            return true;
        }
    }
    return false;
}

bool Level::isKey() {
    if (otherObjects[2] == nullptr) {
        return false;
    }
    if (otherObjects[2]->isCrossed(this->getCharStartPos(), this->getCharEndPos())) {
        return true;
    }
    return false;
}

int Level::getLabelMaxIndex() {
    return labelMaxIndex;
}

std::vector <Barrier*> Level::getBarriers() {
    return barriers;
}

void Level::printVectorToF(std::ofstream& fd, std::string name, std::vector<Barrier*> v2) {
    if (v2.size() == 0) {
        fd << "/" << std::endl;
        return;
    }
    fd << name << std::endl;
    for (auto &i : v2) {
        fd << i->getStartPos().rx() + levelShift << " " << i->getStartPos().ry() << " " <<
              i->getEndPos().rx() + levelShift << " " << i->getEndPos().ry() << std::endl;
    }
}

void Level::printObjectToF(std::ofstream& fd, Barrier* b) {
    fd << b->getStartPos().rx() + levelShift << " " << b->getStartPos().ry() << " " <<
          b->getEndPos().rx() + levelShift << " " << b->getEndPos().ry() << std::endl;
}

void Level::recordToFile(std::string path) {
    std::ofstream fd;
    fd.open(path);
//    if (!(fd.is_open())) {
//        std::exit(0);
//    }
    fd << "Text:\n";
    if (text.size() != 0) {
        for (auto &i : text) {
            fd << i->getStartPos().rx() + levelShift << " " << i->getStartPos().ry() << " " <<
                  i->getEndPos().rx() + levelShift << " " << i->getEndPos().ry() <<  "'" <<
                  i->text().toStdString() << "'" << std::endl;
        }
    }
    printVectorToF(fd, "Barriers:", barriers);
//    fd << "Barriers:\n";
//    for (Barrier & i : barriers) {
//        fd << i.getStartPos().rx() << " " << i.getStartPos().ry() << " " <<
//              i.getEndPos().rx() << " " << i.getEndPos().ry() << std::endl;
//    }
    if (otherObjects[0] != nullptr) {
        fd << "Finish:\n";
        printObjectToF(fd, otherObjects[0]);
    }
    else {
        fd << "/\n";
    }
    if (otherObjects[1] != nullptr) {
        fd << "MovingObjects:\n";
        printObjectToF(fd, otherObjects[1]);
    }
    else {
        fd << "/\n";
    }
    printVectorToF(fd, "KillingObjects:",  killingObjects);
    printVectorToF(fd, "JumpingObjects:", jumpingObjects);
    if (otherObjects[2] != nullptr) {
            fd << "KeyObjects:\n";
            fd << otherObjects[2]->getStartPos().rx() + levelShift << " " << otherObjects[2]->getStartPos().ry() << " " <<
                  otherObjects[2]->getEndPos().rx() + levelShift << " " << otherObjects[2]->getEndPos().ry() << " " << elementIndex <<  std::endl;
    }

}

bool Level::isMovePossible(Move move) {
    if (move == Move::RIGHT) {
        if (getCharEndPos().rx() > SCREEN_BOARD_END_X) {
            return false;
        }
        QPoint startPos = QPoint(getCharStartPos().rx() + HORIZONTAL_MOVEMENT, getCharStartPos().ry());
        QPoint endPos = QPoint(getCharEndPos().rx() + HORIZONTAL_MOVEMENT, getCharEndPos().ry());
        for (auto & i : barriers) {
            if (i->isCrossed(startPos, endPos)) {
                return false;
            }
        }
        return true;

    }
    if (move == Move::LEFT) {
        if (getCharStartPos().rx() < SCREEN_BOARD_START_X) {
            return false;
        }
        QPoint startPos = QPoint(getCharStartPos().rx() - HORIZONTAL_MOVEMENT, getCharStartPos().ry());
        QPoint endPos = QPoint(getCharEndPos().rx() - HORIZONTAL_MOVEMENT, getCharEndPos().ry());
        for (auto & i : barriers) {
            if (i->isCrossed(startPos, endPos)) {
                return false;
            }
        }
        return true;
    }
    if (move == Move::DOWN) {
        if (getCharEndPos().ry() > SCREEN_BOARD_END_Y) {
            return false;
        }
        QPoint startPos = QPoint(getCharStartPos().rx(), getCharStartPos().ry() + DOWN_MOVEMENT);
        QPoint endPos = QPoint(getCharEndPos().rx(), getCharEndPos().ry() + DOWN_MOVEMENT);
        for (auto & i : barriers) {
            if (i->isCrossed(startPos, endPos)) {
                return false;
            }
        }
        return true;
    }
    if (move == Move::UP) {
        if (getCharStartPos().ry() < SCREEN_BOARD_START_Y) {
            return false;
        }
        if (character->getJumpCount() >= MAX_JUMP_COUNT) {
            return false;
        }
        QPoint startPos = QPoint(getCharStartPos().rx(), getCharStartPos().ry() - UP_MOVEMENT);
        QPoint endPos = QPoint(getCharEndPos().rx(), getCharEndPos().ry() - UP_MOVEMENT);
        for (auto & i : barriers) {
            if (i->isCrossed(startPos, endPos)) {
                return false;
            }
        }
        return true;
    }
    return false;
}

void Level::setPicture(std::string path, QLabel *pic) {
    window->setPicture(path, pic);
}

void Level::setCharacter(Character *_character) {
    character = _character;
}

bool Level::isFinish() {
    if (otherObjects[0] == nullptr) {
        return false;
    }
    if (otherObjects[0]->isCrossed(character->getStartPos(), character->getEndPos())) {
        return true;
    }
    return false;
}

bool Level::isMovingCameraNeed() {
    for (Barrier* i : barriers) {
        if (keyConnectedObject != nullptr) {
            if (i == keyConnectedObject) {
                continue;
            }
        }
        if (!i->isVisible()) {
            return true;
        }
    }
    for (Barrier* i : jumpingObjects) {
        if (!i->isVisible()) {
            return true;
        }
    }
    for (Barrier* i : killingObjects) {
        if (!i->isVisible()) {
            return true;
        }
    }
    for (Barrier* i : otherObjects) {
        if (i == nullptr) {
            continue;
        }
        if (!i->isVisible()) {
            return true;
        }
    }
    return false;
}

void Level::moveCamera() {
    while(!(otherObjects[1]->getEndPos().rx() < 1)) {
        moveAllObjects(Move::LEFT);
    }
}

void Level::resetLevel() {
    for (int i = 0; i < window->labels.size(); ++i) {
        window->labels[i]->setVisible(false);
    }
    for (auto & i: text) {
        i->setVisible(false);
    }
    window->resetLevel();
}

void Level::increaseCharacterJumpCount() {
    character->increaseJumpCount();
}

void Level::moveAllObjects(Move move) {
      for (auto &i : otherObjects) {
          i->move(move);
      }
      for (auto &i : killingObjects) {
          i->move(move);
      }
      for (auto &i : jumpingObjects) {
          i->move(move);
      }
      for (auto &i : barriers) {
          i->move(move);
      }
      int par;
      if (move == Move::LEFT) {
          par = HORIZONTAL_MOVEMENT;
      }
      if (move == Move::RIGHT) {
          par = -HORIZONTAL_MOVEMENT;
      }
      levelShift -= HORIZONTAL_MOVEMENT;
      for (auto & i : background) {
          i->move(par, 0);
          std::cout << "1";
      }
      //leftObject->move(move);
      //rightObject->move(move);

//      character->move(move);
//    for (auto &i : barriers) {
//        i.move(move);
//    }
//    barriers.pop_back();
//    barriers.pop_back();
}

void Level::nextLevel() {
    window->nextLevel();
}

void Level::deactivateObject() {
    keyConnectedObject->deactivate();
}

void Level::activateObject() {
    keyConnectedObject->activate();
}

void Level::keyDisappear() {
    otherObjects[2]->deactivate();
}

bool Level::isCheckpoint() {
    if (otherObjects[1] == nullptr) {
        return false;
    }
    if (otherObjects[1]->isCrossed(character->getStartPos(), character->getEndPos())) {
        return true;
    }
    return false;
}

void Level::setNewCheckpoint() {
    window->setNewCheckpoint(QPoint(CHAR_START_X, character->getStartPos().ry()),
                             QPoint(CHAR_START_X + CHAR_SIZE_X, character->getEndPos().ry()));
}

void Level::increaseCheckpointNumber() {
    window->increaseCheckpointNumber();
}

int Level::textCount() {
    return text.size();
}

void Level::setChangingObject(QPoint pos) {
    int x = pos.rx();
    int y = pos.ry();
    for (Barrier*& i: barriers) {
        if (x > i->getStartPos().rx() && x < i->getEndPos().rx() &&
            y > i->getStartPos().ry() && y < i->getEndPos().ry()) {
//            i.deactivate();
                changingObject = i;
                return;
        }
    }
    for (Barrier*& i: otherObjects) {
        if (i == nullptr) {
            continue;
        }
        if (x > i->getStartPos().rx() && x < i->getEndPos().rx() &&
            y > i->getStartPos().ry() && y < i->getEndPos().ry()) {
//            i.deactivate();
                changingObject = i;
                return;
        }
    }
    for (Barrier*& i: killingObjects) {
        if (x > i->getStartPos().rx() && x < i->getEndPos().rx() &&
            y > i->getStartPos().ry() && y < i->getEndPos().ry()) {
//            i.deactivate();
                changingObject = i;
                return;
        }
    }
    for (Barrier*& i: jumpingObjects) {
        if (x > i->getStartPos().rx() && x < i->getEndPos().rx() &&
            y > i->getStartPos().ry() && y < i->getEndPos().ry()) {
//            i.deactivate();
                changingObject = i;
                return;
        }
    }
}

void Level::moveChangingObject(QPoint pos) {
    if (changingObject != nullptr) {
        changingObject->move(pos);
    }
}

void Level::resizeChangingObject(QPoint pos) {
    if (changingObject != nullptr) {
        changingObject->resize(pos);
    }
}

//Barrier* Level::getNewBarrier() {
//    Barrier b = Barrier(window->labels[labelMaxIndex], QPoint(500, 500), QPoint(600, 600));
//    window->labels[labelMaxIndex]->setStyleSheet(BARRIER_LABEL);
//    ++labelMaxIndex;
//    barriers.push_back(b);
//    return b;
//}

Barrier* Level::getNewObject(Object o) {
    if (o == Object::FINISH) {
        if (otherObjects[0] == nullptr) {
            Barrier* b = new Barrier(window->labels[labelMaxIndex], QPoint(500, 500), QPoint(600, 600));
            otherObjects[0] = b;
            window->labels[labelMaxIndex]->setStyleSheet(buttonsLabels[static_cast<int>(o)]);
            ++labelMaxIndex;
            return b;
        }
        else {
            otherObjects[0]->move(QPoint(500, 500));
            return otherObjects[0];
        }
    }
    else if (o == Object::MOVING_OBJECT) {
        if (otherObjects[1] == nullptr) {
            Barrier* b = new Barrier(window->labels[labelMaxIndex], QPoint(500, 500), QPoint(600, 600));
            otherObjects[1] = b;
            window->labels[labelMaxIndex]->setStyleSheet(buttonsLabels[static_cast<int>(o)]);
            ++labelMaxIndex;
            return b;
        }
        else {
            otherObjects[1]->move(QPoint(500, 500));
            return otherObjects[1];
        }
    }
    Barrier *b = new Barrier(window->labels[labelMaxIndex], QPoint(500, 500), QPoint(600, 600));
    window->labels[labelMaxIndex]->setStyleSheet(buttonsLabels[static_cast<int>(o)]);
    if (o == Object::BARRIER)
        barriers.push_back(b);
    if (o == Object::KILLING_OBJECT)
        killingObjects.push_back(b);
    if (o == Object::JUMPING_OBJECT)
        jumpingObjects.push_back(b);
    ++labelMaxIndex;
    return b;
}

int Level::getRightPosX() {
    return rightObject->getEndPos().rx();
}

int Level::getLeftPosX() {
    return leftObject->getStartPos().rx();
}

QLabel* Level::getCharLabel() {
    return character->getLabel();
}

Level::~Level() {
    for (auto & i: text) {
        i->setVisible(false);
    }
    for (auto & i : background) {
        i->setVisible(false);
    }
    delete character;
    character = nullptr;
}
