																			 /*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           joystick.h
** Last modified Date:  2018-12-30
** Last Version:        V1.00
** Descriptions:        Prototypes of functions included in the lib_joystick, funct_joystick .c files
** Correlated files:    lib_joystick.c, funct_joystick.c
**--------------------------------------------------------------------------------------------------------       
*********************************************************************************************************/
#include "LPC17xx.h"

/* lib_joystick */
void joystick_init(void);
void show_moves(uint16_t);
void color_box(uint16_t ,uint16_t , uint16_t);
char control_up(void);
char control_left(void);
char control_right(void);
char control_down(void);
void select_right(void);
void select_left(void);
void select_up(void);
void select_down(void);
void select_left_plus(void);
void select_right_plus(void);
void select_up_plus(void);
void select_down_plus(void);
void move_direction(void);
void move_right(void);
void move_left(void);
void move_up(void);
void move_down(void);
void move_wall_right(void);
void move_wall_left(void);
void move_wall_up(void);
void move_wall_down(void);
void move_right_up(void);
void move_right_down(void);
void move_left_up(void);
void move_left_down(void);
void break_wall(uint16_t, uint16_t);
void rotate_wall_to_horizontal(void);
void rotate_wall_to_vertical(void);
void place_wall(uint16_t, uint16_t, uint16_t);
void perma_wall(void);
char trap_check_p1(uint16_t x_start,uint16_t y_start);
char trap_check_p2(uint16_t x_start,uint16_t y_start);
void plus_condition(void);
int choose_npc_move(void);

