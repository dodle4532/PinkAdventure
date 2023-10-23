#ifndef HEADER_H
#define HEADER_H

#include <QApplication>
#include <QLabel>
#include <QKeyEvent>
#include <iostream>
#include <QTimer>
#include <QPoint>
#include "windows.h"
#define HORIZONTAL_MOVEMENT 2
#define DOWN_MOVEMENT 1
#define UP_MOVEMENT 5
#define SCREEN_BOARD_START_X 0
#define SCREEN_BOARD_START_Y 0
#define SCREEN_BOARD_END_X 1920
#define SCREEN_BOARD_END_Y 900
#define PARAM_TO_OUT_OF_BOARD 2000
#define MAX_JUMP_COUNT 50
#define FALL_MOVEMENT 1
#define MOVE_TIMER 5
#define FALL_TIMER 3
#define MAX_LABELS 100
#define FINAL_LEVEL 7
#define FIRST_LEVEL 5
#define BARRIER_LABEL "background-color: rgb(0, 170, 0);"
#define FINISH_LABEL "background-color: rgb(170, 0, 0);"
#define MOVING_OBJECT_LABEL "background-color: rgb(0, 0, 170);"
#define KILLING_OBJECT_LABEL "background-color: rgb(0, 170, 170);"
#define JUMPING_OBJECT_LABEL "background-color: rgb(170, 170, 0);"
#define KEY_OBJECT_LABEL "background-color: rgb(170, 100, 170);"

#endif // HEADER_H
