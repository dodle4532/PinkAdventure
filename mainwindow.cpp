#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "header.h"
#include "menu.h"
#include <QDebug>
#define BUTTONS_COUNT 5
QString buttonsLabels[] = {BARRIER_LABEL, FINISH_LABEL, MOVING_OBJECT_LABEL,
                           KILLING_OBJECT_LABEL, JUMPING_OBJECT_LABEL};


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    level = nullptr;
    this->setWindowState(Qt::WindowMaximized);
//    this->setWindowState(Qt::WindowFullScreen);   полноэкранный режим

//    this->setStyleSheet("#centralWidget { "
//                        " border-image: url(:/new/prefix1/pictures/background.jpg) 0 0 0 0 stretch stretch;"
//                        "}");

//    labels.resize(MAX_LABELS);
//    for (auto & i : labels) {
//        i = new QLabel(this);
//    }

    for (int i = 0; i < 1; ++i) {
        QLabel* background = new QLabel(this);
        background->setStyleSheet("border-image: url(:/new/prefix1/pictures/background.jpg)");
        background->resize(1920, 1080);
        background->move(1920 * i, 0);
        background->setVisible(false);
        backgrounds.push_back(background);
    }

    QTimer *moveTimer = new QTimer(this);
    connect(moveTimer, SIGNAL(timeout()), this, SLOT(move()));
    QTimer *fallTimer = new QTimer(this);
    connect(fallTimer, SIGNAL(timeout()), this, SLOT(fall()));
    moveTimer->start(MOVE_TIMER);
    fallTimer->start(FALL_TIMER);
    QSignalMapper* signalMapper = new QSignalMapper(this) ;
    for (int i = 0; i < BUTTONS_COUNT; ++i) {
        buttons.push_back(new QPushButton(this));
        buttons[i]->setVisible(false);
        buttons[i]->move(100 + 150 * i, 0);
        buttons[i]->resize(100, 50);
        buttons[i]->setStyleSheet(buttonsLabels[i]);
        connect(buttons[i], SIGNAL(clicked(bool)), signalMapper, SLOT(map()));
        signalMapper->setMapping(buttons[i], i);
    }
    connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(buttonPressed(int))) ;
    QPushButton* playButton = new QPushButton(this);
    connect(playButton, SIGNAL(clicked(bool)), this, SLOT(resetLevel()));
    playButton->move(100, 440);
    playButton->resize(400, 200);
    playButton->setText("Играть");
    QPushButton* closeButton = new QPushButton(this);
    connect(closeButton, SIGNAL(clicked(bool)), this, SLOT(closeGame()));
    closeButton->move(1400, 440);
    closeButton->resize(400, 200);
    closeButton->setText("Выход");
    QPushButton* instructionButton = new QPushButton(this);
    connect(instructionButton, SIGNAL(clicked(bool)), this, SLOT(showInstuction()));
    instructionButton->move(750, 440);
    instructionButton->resize(400, 200);
    instructionButton->setText("Инфо");
    menu = new Menu(playButton, closeButton, instructionButton, new QLabel(this));
}

void MainWindow::fall() {
    if (level != nullptr)
        level->fall();
}

void MainWindow::move() {
    if (level != nullptr)
        level->move();
}

void MainWindow::closeGame() {
    std::exit(0);
}

void MainWindow::showInstuction() {
    isInstruction = true;
    resetLevel(true);
}

void MainWindow::setButtonsVisible(bool par) {
    for (auto &i : buttons) {
        i->setVisible(par);
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    int key = event->key();
//    std::cout << key << std::endl;
//    std::cout << ui->character->pos().rx() << " " << ui->character->pos().ry() << " " << character->getStartPos().rx() << " " << character->getStartPos().ry() << std::endl;
    if (key == Qt::Key_Escape) {
 //       std::cout << ui->character->pos().rx() << " " << ui->character->pos().ry() << std::endl;
        std::exit(0);
    }

    if (key == Qt::Key_E) {
        if (isEdit) {
            setButtonsVisible(false);
            isEdit = false;
        }
        else {
            setButtonsVisible(true);
            isEdit = true;
        }
    }

    if (key == Qt::Key_Y) {
        if (isResizeMode) {
            isResizeMode = false;
        }
        else {
            isResizeMode = true;
        }
    }

    if (key == Qt::Key_P) {
        level->recordToFile("Test" + std::to_string(levelNumber) + ".txt");
    }

    if (key == Qt::Key_R) {
        level->resetLevel();
    }

    if (key == 16777220) {
        if (level != nullptr) {
            if (level->isTextLevel) {
                if (isInstruction) {
                    for (auto & i : labels) {
                        i->setVisible(false);
                    }
                    menu->setVisible(true);
                    isInstruction = false;
                }
                else {
                    nextLevel();
                    level->resetLevel();
                }
            }
        }
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
        if (!(GetKeyState('W') & 0x8000)){
            level->resetMove(Move::UP);
        }
    }
    if (key == Qt::Key_A || key == 1060) {
        if (!(GetKeyState('A') & 0x8000)){
            level->resetMove(Move::LEFT);
        }
    }
    if (key == Qt::Key_S || key == 1067) {
        if (!(GetKeyState('S') & 0x8000)){
            level->resetMove(Move::DOWN);
        }
    }
    if (key == Qt::Key_D || key == 1042) {
        if (!(GetKeyState('D') & 0x8000)){
            level->resetMove(Move::RIGHT);
        }
    }
//    if (ui->character->pos() != character->getStartPos()) {
//       // std::exit(0);
//    }
}

void MainWindow::mousePressEvent(QMouseEvent *e) {
    if (isEdit) {
       level->setChangingObject(e->pos());
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *e) {
    if (isEdit) {
        if (isResizeMode)
            level->resizeChangingObject(e->pos());
        else
            level->moveChangingObject(e->pos());
    }
}


void MainWindow::setPicture(std::string path, QLabel* pic) {
    QPixmap pix;
    pix.load(QString::fromStdString(path));
    int w = pic->width();
    int h = pic->height();
    pic->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio));
    pic->setScaledContents(true);
    return;
}

void MainWindow::setNewCheckpoint(QPoint startPos, QPoint endPos) {
    charCheckPointPos.first = startPos;
    charCheckPointPos.second = endPos;
}

void MainWindow::resetLevel(bool isInstruction) {

    if (level != nullptr) {
        if (level->isTextLevel) {
            for (int i = 0; i < level->textCount(); ++i) {
                labels[i]->setText("");
            }
        }
    }
//    labels.clear();
    labels.resize(MAX_LABELS);
    for (auto & i : labels) {
        i = new QLabel(this);
    }
    if (levelNumber > 0) {
        for (int i = 0; i < labels.size(); ++i) {
            labels[i]->setVisible(true);
        }
    }
    if (levelNumber == FINAL_LEVEL) {
        menu->setVisible(true);
        return;
    }
    menu->setVisible(false);
    for (int i = 0; i < labels.size(); ++i) {
        labels[i]->setVisible(true);
    }
    garbage.push_back(level);
    if (isInstruction)
        level = new Level("Test0.txt", this, backgrounds);
    else
        level = new Level("Test" + std::to_string(levelNumber) + ".txt", this, backgrounds);

//    Character* character = new Character(":/new/prefix1/pictures/character.png",
//                              ":/new/prefix1/pictures/character(mirrored).png",  ui->character,
//                              charCheckPointPos.first, charCheckPointPos.second, level);

    if (level->isTextLevel) {
        level->getCharLabel()->setVisible(false);
    }
    else {
        level->getCharLabel()->setVisible(true);
    }
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

void MainWindow::buttonPressed(int o) {
    level->getNewObject(static_cast<Object>(o));
}

std::pair<QPoint, QPoint> MainWindow::getCheckpoint() {
    return charCheckPointPos;
}

MainWindow::~MainWindow()
{
    delete ui;
    for (auto & i : garbage) {
        delete i;
    }
    delete menu;
}

