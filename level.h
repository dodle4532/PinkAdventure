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

enum class Object {
    BARRIER = 0,
    FINISH,
    MOVING_OBJECT,
    KILLING_OBJECT,
    JUMPING_OBJECT
};



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

    bool isMovePossible(Move move);

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
    bool isCheckpoint();
    void increaseCheckpointNumber();

    bool isTextLevel = false;
    bool isMoveCameraNeeded;

    int textCount();

    Barrier* getNewObject(Object o);

    int getLabelMaxIndex();

    void setChangingObject(QPoint pos);
    void moveChangingObject(QPoint pos);
    void resizeChangingObject(QPoint pos);
    void updateLeftAndRightObject(int& min, int& max, Barrier* barrier);

    int getRightPosX();
    int getLeftPosX();

private:
    Character* character;
    Barrier* changingObject;
    std::vector <Barrier> barriers;
    std::vector <Barrier> text;
    MainWindow* window;

    /*
    finish - 0
    moveCameraObject - 1
    keyObject - 2
    */
    std::vector<Barrier*> otherObjects;

    std::vector <Barrier*> killingObjects;

    std::vector <Barrier*> jumpingObjects;

    Barrier* leftObject;
    Barrier* rightObject;

    int elementIndex = -1;
    Barrier* keyConnectedObject;
    int labelMaxIndex = 0;

//private slots:
};

#endif // LEVEL_H
