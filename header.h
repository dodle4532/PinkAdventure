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
#define MAX_JUMP_COUNT 45
#define FALL_MOVEMENT 1
#define MOVE_TIMER 5
#define FALL_TIMER 3
#define MAX_LABELS 100
#define FINAL_LEVEL 7
#define FIRST_LEVEL 5
#define OTHER_OBJECTS_COUNT 3
#define BARRIER_LABEL "background-color: rgb(0, 170, 0);"
#define FINISH_LABEL "background-color: rgb(170, 0, 0);"
#define MOVING_OBJECT_LABEL "background-color: rgb(0, 0, 170);"
#define KILLING_OBJECT_LABEL "background-color: rgb(0, 170, 170);"
#define JUMPING_OBJECT_LABEL "background-color: rgb(170, 170, 0);"
#define KEY_OBJECT_LABEL "background-color: rgb(170, 100, 170);"

#define CHAR_SIZE_X 90
#define CHAR_SIZE_Y 110
#define CHAR_START_X 10
#define CHAR_START_Y 600
#define CAMERA_MOVE_PAR_RIGHT_X 0.45
#define CAMERA_MOVE_PAR_RIGHT_Y 0.9
#define CAMERA_MOVE_PAR_LEFT_X 0.3
#define CAMERA_MOVE_PAR_LEFT_Y 0.05
#define HITBOX_CORRECTION_X 15

#endif // HEADER_H
