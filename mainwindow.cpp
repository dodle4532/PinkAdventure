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

    labels.resize(100);
    for (auto & i : labels) {
        i = new QLabel(this);
    }
    resetLevel();

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(fall()));
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(5);
    ui->floor->resize(10000, 1000);
    ui->floor->move(ui->floor->pos() + QPoint(0, 200));
//    std::vector <Barrier> barriers;
//    barriers.push_back(Barrier(ui->barrier_1, QPoint(300, 700), QPoint(550, 750)));
//    barriers.push_back(Barrier(ui->barrier_2, QPoint(400, 650), QPoint(550, 700)));
//    level = new Level(character, barriers, this);
//    level->recordToFile("Test.txt");
//    setPicture(":/new/prefix1/pictures/floor.png", ui->floor);
}

void MainWindow::fall() {
    level->fall();
}

void MainWindow::move() {
    level->move();
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    int key = event->key();
//    std::cout << key;
//    std::cout << ui->character->pos().rx() << " " << ui->character->pos().ry() << " " << character->getStartPos().rx() << " " << character->getStartPos().ry() << std::endl;
    if (key == Qt::Key_Escape) {
        std::cout << ui->character->pos().rx() << " " << ui->character->pos().ry() << std::endl;
        std::exit(0);
    }
    if (key == Qt::Key_R) {
        resetLevel();
    }
    if(GetAsyncKeyState(Qt::Key_W)) {
        level->setMove(Move::UP);
    }
    if (GetAsyncKeyState(Qt::Key_A)) {
        level->setMove(Move::LEFT);
    }
    if (GetAsyncKeyState(Qt::Key_S)) {
        level->setMove(Move::DOWN);
    }
    if (GetAsyncKeyState(Qt::Key_D)) {
        level->setMove(Move::RIGHT);
    }

}

void MainWindow::keyReleaseEvent(QKeyEvent *event) {
    int key = event->key();
    if(key == Qt::Key_W || key == 1062) {
        level->resetMove(Move::UP);
    }
    if (key == Qt::Key_A || key == 1060) {
        level->resetMove(Move::LEFT);
    }
    if (key == Qt::Key_S || key == 1067) {
        level->resetMove(Move::DOWN);
    }
    if (key == Qt::Key_D || key == 1042) {
        level->resetMove(Move::RIGHT);
    }
//    if (ui->character->pos() != character->getStartPos()) {
//       // std::exit(0);
//    }
}


void MainWindow::setPicture(std::string path, QLabel* pic) {
    QPixmap pix;
    pix.load(QString::fromStdString(path));
    int w = pic->width();
    int h = pic->height();
    pic->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio));
    return;
}

void MainWindow::setNewCheckpoint(QPoint startPos, QPoint endPos) {
    charCheckPointPos.first = startPos;
    charCheckPointPos.second = endPos;
}

void MainWindow::resetLevel() {

//    if (level != nullptr) {
//        delete level;
//        for (auto &i : labels) {
//            delete i;
//        }
//        labels.clear();
//    }
    if (levelNumber == 5) {
        std::exit(0);
    }
    level = new Level("Test" + std::to_string(levelNumber) + ".txt", this);
    Character* character = new Character(":/new/prefix1/pictures/character.png",
                              ":/new/prefix1/pictures/character(mirrored).png",  ui->character, level,
                              charCheckPointPos.first, charCheckPointPos.second);
    level->setCharacter(character);
    if (checkpointNumber > 0) {
        level->moveCamera();
    }

}

QLabel* MainWindow::getNewVector(std::string style) {
    QLabel* label = new QLabel(this);
    //label->setStyleSheet(QString::fromStdString(style));
    labels.push_back(label);
    labels[labels.size() - 1]->setStyleSheet(QString::fromStdString(style));
    return labels[labels.size() - 1];
}

QVector <QLabel*> MainWindow::getLabels() {
    return labels;
}

void MainWindow::nextLevel() {
    levelNumber++;
    checkpointNumber = 0;
    charCheckPointPos = {QPoint(10,600), QPoint(100, 710)};
}

void MainWindow::increaseCheckpointNumber() {
    checkpointNumber++;
}

MainWindow::~MainWindow()
{
    delete ui;
}

