#include "character.h"

Character::Character(std::string _url, QLabel* _label, MainWindow* _window) :
    url(_url), label(_label), window(_window)
{
    window->setPicture(url, label);
}

void Character::move() {
    for (auto & i : moves) {
        if (i == Move::RIGHT) {
            label->move(label->pos() + QPoint(10, 0));
            continue;
        }
        if (i == Move::LEFT) {
            label->move(label->pos() + QPoint(-10, 0));
            continue;
        }
        if (i == Move::DOWN) {
            label->move(label->pos() + QPoint(0, 10));
            continue;
        }
        if (i == Move::UP) {
            label->move(label->pos() + QPoint(0, -10));
            continue;
        }
    }
}

void Character::resetMove(Move move) {
    for (auto i = moves.begin(); i < moves.end() + 1; ++i) {
        if (*i == move) {
            moves.erase(i);
        }
    }
    this->move();
}

void Character::setMove(Move move) {
    for (auto &i : moves) {
        if (i == move) {
            this->move();
            break;
        }
    }
    moves.push_back(move);
    this->move();
}
