#ifndef MAINWINDOW_H
#define MAINWINDOW_H
//“Зимний лес”: Герой спасает маленького эльфа от злых троллей. Текстуры содержат заснеженные леса, ледяные замки и зимних животных.
//Главный герой - это маленький робот, который может прыгать и бегать. Он отправляется в опасное путешествие, чтобы спасти своего друга, который был захвачен злыми монстрами.

//На своем пути он должен преодолеть различные препятствия, такие как пропасти, шипы и враги. Также он должен собирать монеты и бонусы, которые помогут ему в борьбе с врагами и решении головоломок.

//Один из уровней будет проходить в зимнем лесу, где герой должен будет прыгать по заснеженным деревьям и избегать ловушек, расставленных троллями. В конце уровня он должен будет сразиться с боссом - огромным троллем, который охраняет вход в ледяной замок.

//В замке герой должен будет пройти через множество комнат, заполненных ловушками и врагами. В конце замка он найдет своего друга, которого держат в плену тролли. После освобождения друга они вместе должны будут победить последнего босса - огромного ледяного тролля, который является королем всех троллей.

#include <QMainWindow>
#include "header.h"
#include "character.h"
#include "barrier.h"
#include "level.h"
#include <QVector>

namespace Ui {
class MainWindow;
}

class Character;
class Barrier;
class Level;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setPicture(std::string path, QLabel* pic);
    void resetLevel();
    void setNewCheckpoint(QPoint startPos, QPoint endPos);
    void increaseCheckpointNumber();
    QLabel* getNewVector(std::string style);
    QVector <QLabel*> getLabels();
    QVector <QLabel*> labels;

    void nextLevel();

private slots:
    void fall();
    void move();

private:
    Ui::MainWindow *ui;
    int levelNumber = 0;
    //Character* character;
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void keyReleaseEvent(QKeyEvent *event);
    //std::vector <Barrier> barriers;
    Level* level;
    std::pair <QPoint, QPoint> charCheckPointPos = {QPoint(10,600), QPoint(100, 710)}; // startPos, endPos
    size_t checkpointNumber = 0;
};

#endif // MAINWINDOW_H
