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

    this->setStyleSheet("#centralWidget { "
                        " border-image: url(:/new/prefix1/pictures/background.jpg) 0 0 0 0 stretch stretch;"
                        "}");

    character = new Character(":/new/prefix1/pictures/1character.png",
                              ":/new/prefix1/pictures/1character(mirrored).png",  ui->character, this,
                              QPoint(10,200), QPoint(100, 310));
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(fall()));
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(5);
    ui->floor->resize(10000, 1000);
    ui->floor->move(ui->floor->pos() + QPoint(0, 200));
    barriers.push_back(Barrier(ui->barrier_1, QPoint(300, 700), QPoint(550, 750), this));
//    setPicture(":/new/prefix1/pictures/floor.png", ui->floor);
}

void MainWindow::fall() {
    character->fall();
}

void MainWindow::move() {
    character->move();
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    int key = event->key();
//    std::cout << key;
    std::cout << ui->character->pos().rx() << " " << ui->character->pos().ry() << " " << character->getStartPos().rx() << " " << character->getStartPos().ry() << std::endl;
    if (key == Qt::Key_Escape) {
        std::cout << ui->character->pos().rx() << " " << ui->character->pos().ry() << std::endl;
        std::exit(0);
    }
    if(GetAsyncKeyState(Qt::Key_W)) {
        character->setMove(Move::UP);
    }
    if (GetAsyncKeyState(Qt::Key_A)) {
        character->setMove(Move::LEFT);
    }
    if (GetAsyncKeyState(Qt::Key_S)) {
        character->setMove(Move::DOWN);
    }
    if (GetAsyncKeyState(Qt::Key_D)) {
        character->setMove(Move::RIGHT);
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
    if (ui->character->pos() != character->getStartPos()) {
       // std::exit(0);
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

bool MainWindow::isMovePossible() {
    for (auto & i : barriers) {
//         if (!(i.isMovePosible(character->getStartPos(), character->getEndPos()))) {
//             return false;
//         }
        if (i.isCrossed(character->getStartPos(), character->getEndPos())) {
            return false;
        }
    }
    return true;
}

MainWindow::~MainWindow()
{
    delete ui;
}
