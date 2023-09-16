#include "level.h"
#include <QTimer>
#include <fstream>
#include <sstream>
#include <iostream>

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

Level::Level(std::string path, MainWindow* _window, Character* _character) :
    character(_character), window(_window)
{
    otherObjects.resize(2);
    std::ifstream fd;
    std::string str;
    //std::stringstream ss;
    std::string startX;
    std::string startY;
    std::string endX;
    std::string endY;
    int i = 0;
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
            window->labels[i]->setText(QString::fromStdString(style));
            window->labels[i]->setStyleSheet("color: white;font-size:50px");

            Barrier* barrier = new Barrier(window->labels[i],
                                 QPoint(std::stoi(startX), std::stoi(startY)),
                                 QPoint(std::stoi(endX), std::stoi(endY)));
            text.push_back(*barrier);
            ++i;
            if (str == "") {
                break;
            }
        }
    }
    if (fd.eof()) {
        isTextLevel = true;
    }
    else {
        if (str == "Barriers:" || str == "Barriers:\n") {
            while (!(fd.eof())) {
                std::getline(fd, str);
                if (str == "Finish:" || str == "Finish\n") {
                    break;
                }
                Barrier* barrier;
                parse("background-color: rgb(0, 170, 0);", str, barrier, i, window,
                      startX, startY, endX, endY);
                barriers.push_back(*barrier);
            }
        }

        //Finish
        std::getline(fd, str);
        parse("background-color: rgb(170, 0, 0);", str, otherObjects[0], i, window,
              startX, startY, endX, endY);

        // MovingObject
        std::getline(fd, str);
        if (str == "MovingObjects:" || str == "MovingObjects:\n") {
            std::getline(fd, str);
            parse("background-color: rgb(0, 0, 170);", str, otherObjects[1], i, window,
                  startX, startY, endX, endY);
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
                parse("background-color: rgb(0, 170, 170);", str, killingObjects[j], i, window,
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
                parse("background-color: rgb(170, 0, 170);", str, jumpingObjects[j], i, window,
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
            window->labels[i]->setStyleSheet("background-color: rgb(170, 100, 170);");
            ss.str(str);
            std::getline(ss, startX, ' ');
            std::getline(ss, startY, ' ');
            std::getline(ss, endX, ' ');
            std::getline(ss, endY, ' ');
            otherObjects[2] = new Barrier(window->labels[i],
                                 QPoint(std::stoi(startX), std::stoi(startY)),
                                        QPoint(std::stoi(endX), std::stoi(endY)));

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
    }
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


std::vector <Barrier> Level::getBarriers() {
    return barriers;
}

void Level::recordToFile(std::string path) {
    std::ofstream fd;
    fd.open(path);
//    if (!(fd.is_open())) {
//        std::exit(0);
//    }
    fd << "Barriers:\n";
    for (Barrier & i : barriers) {
        fd << i.getStartPos().rx() << " " << i.getStartPos().ry() << " " <<
              i.getEndPos().rx() << " " << i.getEndPos().ry() << std::endl;
    }
    fd << "Finish:\n";
    fd << otherObjects[0]->getStartPos().rx() << " " << otherObjects[0]->getStartPos().ry() << " " <<
          otherObjects[0]->getEndPos().rx() << " " << otherObjects[0]->getEndPos().ry() << std::endl;
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

      character->move(move);
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
