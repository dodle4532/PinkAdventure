#ifndef CHARACTER_H
#define CHARACTER_H

#include <QWidget>
#include <QLabel>
#include <string>
#include <vector>
#include <set>
#include <QMovie>
#include "level.h"
#include "gameobject.h"

class MainWindow;
class Level;

class Character : public GameObject
{
public:
    Character(std::string _url, std::string url_2, QLabel* _label, QPoint _startPos, QPoint _endPos,
              Level* level = nullptr);
    void move();
    void move(Move move);
    void resetMove(Move move);
    void setMove(Move move);
    void fall();
    void resetJumpCount();
    int getJumpCount();
    void increaseJumpCount();
    void changeMovePic();
    void changeJumpPic(int index = -1);
    void setMirrored(bool par);
    QLabel* getLabel();

private:
    std::string url;
    std::string urlMirror;
    std::set <Move> moves;
    Level* level;
    QMovie* leftMovie;
    QMovie* rightMovie;
    int picIndex = 0;

    int changePicIndex = 0;

    int jumpCount;
    bool isMirrored;
    bool isChange;
};

#endif // CHARACTER_H
