#ifndef CHARACTER_H
#define CHARACTER_H

#include <QWidget>
#include <QLabel>
#include <string>
#include <vector>
#include <set>
#include "level.h"
#include "gameobject.h"

class MainWindow;
class Level;

class Character : public GameObject
{
public:
    Character(std::string _url, std::string url_2, QLabel* _label, QPoint _startPos, QPoint _endPos);
    void move();
    void move(Move move);
    void resetMove(Move move);
    void setMove(Move move);
    void fall();
    void resetJumpCount();
    int getJumpCount();
    void increaseJumpCount();
    void setLevel(Level* level);

private:
    std::string url;
    std::string urlMirror;
    std::set <Move> moves;
    Level* level;

    int jumpCount;
    bool isMirrored;
};

#endif // CHARACTER_H
