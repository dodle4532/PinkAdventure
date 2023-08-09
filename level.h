#ifndef LEVEL_H
#define LEVEL_H
#include <vector>
#include <QPoint>
#include "barrier.h"
#include "character.h"

class Character;
enum class Move;
class Barrier;
class MainWindow;



class Level
{
public:
    Level() = default;
    Level(Character* _character, std::vector <Barrier> _barriers, MainWindow* _window);
    Level(std::string path, MainWindow* _window, Character* _character = nullptr);

    void fall();
    void move();

    void setMove(Move move);
    void resetMove(Move move);

    QPoint getCharStartPos();
    QPoint getCharEndPos();

    std::vector <Barrier> getBarriers();

    void recordToFile(std::string path);

    bool isMovePossible();

    void setPicture(std::string path, QLabel* pic);
    void setCharacter(Character* _character);

    bool isFinish();
    bool isDead();
    bool isJumpReset();
    bool isKey();

    void resetLevel();

    void moveAllObjects(Move move);

    bool isMovingCameraNeed();

    void moveCamera();

    void increaseCharacterJumpCount();

    void nextLevel();

    void deactivateObject();
    void activateObject();
    void keyDisappear();

    void setNewCheckpoint();
    void increaseCheckpointNumber();

private:
    Character* character;
    std::vector <Barrier> barriers;
    MainWindow* window;

    /*
    finish - 0
    moveCameraObject - 1
    keyObject - 2
    */
    std::vector<Barrier*> otherObjects;

    std::vector <Barrier*> killingObjects;

    std::vector <Barrier*> jumpingObjects;

    int elementIndex = -1;

//private slots:
};

#endif // LEVEL_H
