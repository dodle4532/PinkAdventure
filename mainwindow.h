#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "header.h"
#include "character.h"
#include "barrier.h"

namespace Ui {
class MainWindow;
}

class Character;
class Barrier;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setPicture(std::string path, QLabel* pic);
    bool isMovePossible();

private slots:
    void fall();
    void move();

private:
    Ui::MainWindow *ui;
    Character* character;
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void keyReleaseEvent(QKeyEvent *event);
    std::vector <Barrier> barriers;
};

#endif // MAINWINDOW_H
