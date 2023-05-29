#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "header.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowState(Qt::WindowMaximized);
//    this->setWindowState(Qt::WindowFullScreen);   полноэкранный режим

    character = new Character(":/new/prefix1/pictures/char1.png", ui->character, this);
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    int key = event->key();
    if (key == Qt::Key_Escape) {
        std::exit(0);
    }
    else if(GetAsyncKeyState(Qt::Key_W)) {
        character->setMove(Move::UP);
    }
    else if (GetAsyncKeyState(Qt::Key_A)) {
        character->setMove(Move::LEFT);
    }
    else if (GetAsyncKeyState(Qt::Key_S)) {
        character->setMove(Move::DOWN);
    }
    else if (GetAsyncKeyState(Qt::Key_D)) {
        character->setMove(Move::RIGHT);
    }
    else {
        character->move();
    }

}

void MainWindow::keyReleaseEvent(QKeyEvent *event) {
    int key = event->key();
    if(key == Qt::Key_W || key == 1062) {
        character->resetMove(Move::UP);
    }
    if (key == Qt::Key_A || key == 1060) {
        character->resetMove(Move::LEFT);
    }
    if (key == Qt::Key_S || key == 1067) {
        character->resetMove(Move::DOWN);
    }
    if (key == Qt::Key_D || key == 1042) {
        character->resetMove(Move::RIGHT);
    }
}


void MainWindow::setPicture(std::string path, QLabel* pic) {
    QPixmap pix;
    pix.load(QString::fromStdString(path));
    int w = pic->width();
    int h = pic->height();
    pic->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio));
    return;
}

MainWindow::~MainWindow()
{
    delete ui;
}
