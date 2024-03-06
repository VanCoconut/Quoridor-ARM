/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           joystick.h
** Last modified Date:  2018-12-30
** Last Version:        V1.00
** Descriptions:        Atomic joystick init functions
** Correlated files:    lib_joystick.c, funct_joystick.c
**--------------------------------------------------------------------------------------------------------       
*********************************************************************************************************/

#include "lpc17xx.h"
#include "joystick.h"

/*----------------------------------------------------------------------------
  Function that initializes joysticks and switch them off
 *----------------------------------------------------------------------------*/
uint16_t x_wall;
uint16_t y_wall;
char n_walls_P1;
char n_walls_P2;
char left_up;
char left_down;
char right_up;
char right_down;
char up_left;
char up_right;
char down_left;
char down_right;

void joystick_init(void) {
	/* joystick select functionality */
  LPC_PINCON->PINSEL3 &= ~(3<<26);	//PIN mode GPIO (00b value per P1.29)
	LPC_GPIO1->FIODIR   &= ~(1<<29);	//P1.25 Input (joysticks on PORT1 defined as Input) 
	x_wall=104;
	y_wall=100;
	n_walls_P1=8;
  n_walls_P2=8;
}
