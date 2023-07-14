#include "level.h"
#include <QTimer>
#include <fstream>
#include <sstream>
#include <iostream>

Level::Level(Character* _character, std::vector <Barrier> _barriers, MainWindow* _window, Barrier* _finish) :
    character(_character), barriers(_barriers), window(_window), finish(_finish)
{
//    QTimer *timer = new QTimer(this);
//    connect(timer, SIGNAL(timeout()), this, SLOT(fall()));
//    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
//    timer->start(5);
}

Level::Level(std::string path, MainWindow* _window, Character* _character) :
    character(_character), window(_window)
{
    std::ifstream fd;
    std::string str;
    std::stringstream ss;
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

    if (str == "Barriers:" || str == "Barriers:\n") {
        while (!(fd.eof())) {
            std::getline(fd, str);
            if (str == "Finish:" || str == "Finish\n") {
                break;
            }
            ss.clear();
            ss.str(str);
            std::getline(ss, startX, ' ');
            std::getline(ss, startY, ' ');
            std::getline(ss, endX, ' ');
            std::getline(ss, endY, ' ');
            //labels.append(new QLabel(window));
            window->labels[i]->setStyleSheet("background-color: rgb(0, 170, 0);");
            Barrier barrier(window->labels[i],
                    QPoint(std::stoi(startX), std::stoi(startY)), QPoint(std::stoi(endX), std::stoi(endY)));
            ++i;
            barriers.push_back(barrier);
        }
    }
    std::getline(fd, str);
    ss.clear();
    ss.str(str);
    std::getline(ss, startX, ' ');
    std::getline(ss, startY, ' ');
    std::getline(ss, endX, ' ');
    std::getline(ss, endY, ' ');
    //labels.append(new QLabel(window));
    window->labels[i]->setStyleSheet("background-color: rgb(170, 0, 0);");
    //window->getNewVector("background-color: rgb(170, 0, 0);");
    finish = new Barrier(window->labels[i],
                         QPoint(std::stoi(startX), std::stoi(startY)), QPoint(std::stoi(endX), std::stoi(endY)));
    ++i;
    //barriers.resize(1);
}

void Level::fall() {
    character->fall();
}

void Level::move() {
    character->move();
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
    fd << finish->getStartPos().rx() << " " << finish->getStartPos().ry() << " " <<
          finish->getEndPos().rx() << " " << finish->getEndPos().ry() << std::endl;
}

bool Level::isMovePossible() {
    if (this->getCharStartPos().rx() < 1 || this->getCharEndPos().rx() > 1920 ||
        this->getCharStartPos().ry() < 1  || this->getCharEndPos().ry() > 900) {
        return false;
    }
    for (auto & i : barriers) {
//         if (!(i.isMovePosible(this->getCharStartPos(), this->getCharEndPos()))) {
//             return false;
//         }
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
    if (finish->isCrossed(character->getStartPos(), character->getEndPos())) {
        return true;
    }
    return false;
}

void Level::resetLevel(std::string path) {
//    for (auto &i : labels) {
//        delete i;
//    }
//    labels.clear();
    window->resetLevel(path);
}
