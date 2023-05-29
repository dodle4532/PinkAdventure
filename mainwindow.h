#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "header.h"
#include "character.h"

namespace Ui {
class MainWindow;
}

class Character;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setPicture(std::string path, QLabel* pic);


private:
    Ui::MainWindow *ui;
    Character* character;
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void keyReleaseEvent(QKeyEvent *event);
};

#endif // MAINWINDOW_H
