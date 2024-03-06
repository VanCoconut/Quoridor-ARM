/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           funct_joystick.h
** Last modified Date:  2018-12-30
** Last Version:        V1.00
** Descriptions:        High level joystick management functions
** Correlated files:    lib_joystick.c, funct_joystick.c
**--------------------------------------------------------------------------------------------------------       
*********************************************************************************************************/

#include "lpc17xx.h"
#include "joystick.h"
#include "../../GLCD/GLCD.h" 
#include "../../timer/timer.h"
#include <string.h>

extern uint16_t x1_P1;
extern uint16_t y1_P1;
extern uint16_t x1_P2;
extern uint16_t y1_P2;
extern uint16_t x_wall;
extern uint16_t y_wall;
extern unsigned int move;
extern char n_walls_P1;
extern char n_walls_P2;
char right;
char left;
char down;
char up;
extern char left_up;
extern char left_down;
extern char right_up;
extern char right_down;
extern char up_left;
extern char up_right;
extern char down_left;
extern char down_right;


