#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
