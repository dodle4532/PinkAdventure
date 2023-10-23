#include "level.h"
#include <QTimer>
#include <fstream>
#include <sstream>
#include <iostream>
#define OTHER_OBJECTS_COUNT 2
extern QString buttonsLabels[];

Level::Level(Character* _character, std::vector <Barrier> _barriers, MainWindow* _window) :
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
        //window->labels[i]->setStyleSheet(QString::fromStdString(style));
    }
    ++i;
}

void Level::updateLeftAndRightObject(int& min, int& max, Barrier* barrier) {
    int start = barrier->getStartPos().rx();
    int end = barrier->getEndPos().rx();
    if (end > max) {
        rightObject = barrier;
        max = end;
    }
    if (start < min) {
        leftObject = barrier;
        min = start;
    }
}

Level::Level(std::string path, MainWindow* _window, Character* _character) :
    character(_character), window(_window)
{
    int minStartX = SCREEN_BOARD_END_X;
    int maxEndX = SCREEN_BOARD_START_X;
    for (int i = 0; i < OTHER_OBJECTS_COUNT; ++i) {
        otherObjects.push_back(nullptr);
    }
    changingObject = nullptr;
    if (character != nullptr) {
        character->setLevel(this);
    }
    std::ifstream fd;
    std::string str;
    //std::stringstream ss;
    std::string startX;
    std::string startY;
    std::string endX;
    std::string endY;
    labelMaxIndex = 0;
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
            updateLeftAndRightObject(minStartX, maxEndX, barrier);
            text.push_back(*barrier);
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
            updateLeftAndRightObject(minStartX, maxEndX, barrier);
            barriers.push_back(*barrier);
        }
    }

    //Finish
    std::getline(fd, str);
    parse("background-color: rgb(170, 0, 0);", str, otherObjects[0], labelMaxIndex, window,
          startX, startY, endX, endY);
    updateLeftAndRightObject(minStartX, maxEndX, otherObjects[0]);

    // MovingObject
    std::getline(fd, str);
    if (str == "MovingObjects:" || str == "MovingObjects:\n") {
        std::getline(fd, str);
//            parse(MOVING_OBJECT_LABEL, str, otherObjects[1], labelMaxIndex, window,
//                  startX, startY, endX, endY);
        otherObjects[1] = new Barrier(new QLabel,
                                  QPoint(1, 1), QPoint(1, 1));
    }
    else {
        otherObjects[1] = new Barrier(new QLabel,
                                  QPoint(1, 1), QPoint(1, 1));
    }

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
            updateLeftAndRightObject(minStartX, maxEndX, killingObjects[j]);
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
            updateLeftAndRightObject(minStartX, maxEndX, jumpingObjects[j]);
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
        updateLeftAndRightObject(minStartX, maxEndX, otherObjects[2]);

        //Доработать
//        std::getline(ss, elemIndex, ' ');
//        std::getline(ss, elemIndex, ' ');
//        std::getline(ss, elemIndex, ' ');
//        std::getline(ss, elemIndex, ' ');
        std::getline(ss, elemIndex, ' ');
        elementIndex = std::stoi(elemIndex) - 1;
        deactivateObject();
    }
    else {
        otherObjects[2] = new Barrier(new QLabel,
                                  QPoint(1, 1), QPoint(1, 1));
    }


//    for (int i = labelMaxIndex; i < MAX_LABELS; ++i) {
//        win
//    }
    //barriers.resize(1);
}

void Level::fall() {
    character->fall();
}

void Level::move() {
    character->move();
    //moveAllObjects(Move::RIGHT);
}

void Level::setMove(Move move) {
    character->setMove(move);
}

void Level::resetMove(Move move) {
    character->resetMove(move);
}

QPoint Level::getCharStartPos() {
    return character->getStartPos();
}

QPoint Level::getCharEndPos() {
    return character->getEndPos();
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
    if (otherObjects[2]->isCrossed(this->getCharStartPos(), this->getCharEndPos())) {
        return true;
    }
    return false;
}

int Level::getLabelMaxIndex() {
    return labelMaxIndex;
}

std::vector <Barrier> Level::getBarriers() {
    return barriers;
}

void printVectorToF(std::ofstream& fd, std::string name,
                    std::vector<Barrier>* v1 = nullptr, std::vector<Barrier*>* v2 = nullptr) {
    if (v1 == nullptr) {
        if (v2->size() == 0) {
            fd << "/" << std::endl;
        }
        fd << name << std::endl;
        for (auto &i : *v2) {
            fd << i->getStartPos().rx() << " " << i->getStartPos().ry() << " " <<
                  i->getEndPos().rx() << " " << i->getEndPos().ry() << std::endl;
        }
    }
    if (v2 == nullptr) {
        if (v1->size() == 0) {
            fd << "/" << std::endl;
        }
        fd << name << std::endl;
        for (auto &i : *v1) {
            fd << i.getStartPos().rx() << " " << i.getStartPos().ry() << " " <<
                  i.getEndPos().rx() << " " << i.getEndPos().ry() << std::endl;
        }
    }
}

void printObjectToF(std::ofstream fd, Barrier* b1, Barrier** b2 = nullptr) {
    if (b1 == nullptr) {
        Barrier* b = *b2;
        fd << b->getStartPos().rx() << " " << b->getStartPos().ry() << " " <<
              b->getEndPos().rx() << " " << b->getEndPos().ry() << std::endl;
    }
    if (b2 == nullptr) {
        Barrier b = *b1;
        fd << b.getStartPos().rx() << " " << b.getStartPos().ry() << " " <<
              b.getEndPos().rx() << " " << b.getEndPos().ry() << std::endl;
    }
}

void Level::recordToFile(std::string path) {
    std::ofstream fd;
    fd.open(path);
//    if (!(fd.is_open())) {
//        std::exit(0);
//    }
    if (text.size() != 0) {
        for (auto &i : text) {
            fd << i.getStartPos().rx() << " " << i.getStartPos().ry() << " " <<
                  i.getEndPos().rx() << " " << i.getEndPos().ry() << i.text().toStdString() << std::endl;
        }
    }
    printVectorToF(fd, "Barriers:", &barriers);
//    fd << "Barriers:\n";
//    for (Barrier & i : barriers) {
//        fd << i.getStartPos().rx() << " " << i.getStartPos().ry() << " " <<
//              i.getEndPos().rx() << " " << i.getEndPos().ry() << std::endl;
//    }
    if (otherObjects[0] != nullptr) {
        fd << "Finish:\n";
        fd << otherObjects[0]->getStartPos().rx() << " " << otherObjects[0]->getStartPos().ry() << " " <<
              otherObjects[0]->getEndPos().rx() << " " << otherObjects[0]->getEndPos().ry() << std::endl;
    }
    if (otherObjects[1] != nullptr) {
        fd << "MovingObjects:\n";
        fd << otherObjects[1]->getStartPos().rx() << " " << otherObjects[1]->getStartPos().ry() << " " <<
              otherObjects[1]->getEndPos().rx() << " " << otherObjects[1]->getEndPos().ry() << std::endl;
    }
    printVectorToF(fd, "KillingObjects:", nullptr,  &killingObjects);
    printVectorToF(fd, "JumpingObjects:", nullptr, &jumpingObjects);
    if (otherObjects[2] != nullptr) {
            fd << "KeyObjects:\n";
            fd << otherObjects[2]->getStartPos().rx() << " " << otherObjects[2]->getStartPos().ry() << " " <<
                  otherObjects[2]->getEndPos().rx() << " " << otherObjects[2]->getEndPos().ry() << " " << elementIndex <<  std::endl;
    }

}

bool Level::isMovePossible() {
    if (this->getCharStartPos().rx() < 1 || this->getCharEndPos().rx() > 1920 ||
        this->getCharStartPos().ry() < 1  || this->getCharEndPos().ry() > 900) {
        return false;
    }
    for (auto & i : barriers) {
        if (i.isCrossed(this->getCharStartPos(), this->getCharEndPos())) {
            return false;
        }
    }
    return true;
}

void Level::setPicture(std::string path, QLabel *pic) {
    window->setPicture(path, pic);
}

void Level::setCharacter(Character *_character) {
    character = _character;
}

bool Level::isFinish() {
    if (otherObjects[0]->isCrossed(character->getStartPos(), character->getEndPos())) {
        return true;
    }
    return false;
}

bool Level::isMovingCameraNeed() {
    if (otherObjects[1]->isCrossed(character->getStartPos(), character->getEndPos())) {
        return true;
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
    window->resetLevel();
}

void Level::increaseCharacterJumpCount() {
    character->increaseJumpCount();
}

void Level::moveAllObjects(Move move) {
    // Let's add finish in barriers for simplifying code
    // Then delete it from there
//    for (auto &i : otherObjects) {
//        barriers.push_back(*i);
//    }
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
          i.move(move);
      }
      leftObject->move(move);
      rightObject->move(move);

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
    if (elementIndex < 0) {
        return;
    }
    unsigned i = elementIndex;
    if(i < barriers.size()) {
        barriers[i].deactivate();
    }
}

void Level::activateObject() {
    if (elementIndex < 0) {
        return;
    }
    unsigned i = elementIndex;
    if(i < barriers.size()) {
        barriers[i].activate();
    }
}

void Level::keyDisappear() {
    otherObjects[2]->deactivate();
}

void Level::setNewCheckpoint() {
    window->setNewCheckpoint(character->getStartPos(), character->getEndPos());
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
    for (Barrier& i: barriers) {
        if (x > i.getStartPos().rx() && x < i.getEndPos().rx() &&
            y > i.getStartPos().ry() && y < i.getEndPos().ry()) {
//            i.deactivate();
                changingObject = &i;
                return;
        }
    }
    for (Barrier*& i: otherObjects) {
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
    changingObject->resize(pos);
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
        barriers.push_back(*b);
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
