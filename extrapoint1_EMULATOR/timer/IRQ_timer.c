/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_timer.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    timer.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include <string.h>
#include "lpc17xx.h"
#include "timer.h"
#include "../GLCD/GLCD.h" 
#include "../TouchPanel/TouchPanel.h"
#include "../JOYSTICK/joystick.h"
#include "../RIT/RIT.h"

/******************************************************************************
** Function name:		Timer0_IRQHandler
**
** Descriptions:		Timer/Counter 0 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
int i =20;
extern unsigned int move;
extern uint16_t x1_P1;
extern uint16_t y1_P1;
extern uint16_t x1_P2;
extern uint16_t y1_P2;
extern char n_walls_P1;
extern char n_walls_P2;
int mode;
extern uint16_t x_wall;
extern uint16_t y_wall;
extern char no_more;


void TIMER0_IRQHandler (void)
{
	GUI_Text(40, 235, (uint8_t *) "NO WALL ALLOWED ", White, White);
	disable_timer(0);
	reset_timer(0);
  LPC_TIM0->IR = 1;		
  return; 
}


/******************************************************************************
** Function name:		Timer1_IRQHandler
**
** Descriptions:		Timer/Counter 1 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
void TIMER1_IRQHandler (void)
{
  char int_str1[20];
  sprintf(int_str1, "%d", i);
	
	if(i==0){
		GUI_Text(115, 280, (uint8_t *) int_str1, Black, White);
		mode=move<<8;
		mode=(mode>>28)&1;
		if(mode==1) place_wall(x_wall,y_wall,White);
		//se scade il tempo setto playermove a 0 e vertical/horizontal a 1 
		move=move>>24;
		move=move<<8;
		move=move+1;
		move=move<<16;
		show_moves(White);
		finish_turn();
		x_wall=104;
		y_wall=100;
		
	}
	else{
		if(i<=9){
			GUI_Text(112, 280, (uint8_t *) "    ", Black, White);
			GUI_Text(116, 280, (uint8_t *) int_str1, Black, White);
			i--;
		}
		else {
			GUI_Text(112, 280, (uint8_t *) "    ", Black, White);
			GUI_Text(112, 280, (uint8_t *) int_str1, Black, White);
			i--;
		}
	}

  LPC_TIM1->IR = 1;			/* clear interrupt flag */
	enable_timer(1);
  return;
}

void finish_turn(void){
		char player;
		no_more=0;
		NVIC_DisableIRQ(EINT2_IRQn);
		disable_timer(1);
		//reset_timer(1);
		i=20;
		player=(move>>24)&1;
		if(check_win_condition(player)==1) {
			disable_RIT();
			disable_timer(1);
			return;
		}
	
		if(n_walls_P1==0 || n_walls_P2==0) GUI_Text(2, 235, (uint8_t *) "NO MORE WALLS, MOVE THE TOKEN", White, White);
	
		player = (player==0) ? 1 : 0; //se player è uguale a 0 diventa 1, altrimenti diventa 0
		if(player==0){//da 1 deve diventare 0
			//inseriamo le coordinate di x e y
			move=move>>16;
			move=move<<8;
			move=move+y1_P2;
			move=move<<8;
			move=move+x1_P2; 
			
			move=move&16777215; //Setta a 0 il 25esmino bit, and con tutti 1 tranne il bit 25 a 0
			
		}
		else{ // da 0 deve diventare 1
			//inseriamo le coordinate di x e y
			move=move>>16;
			move=move<<8;
			move=move+y1_P1;
			move=move<<8;
			move=move+x1_P1;
			
			move=move|16777216; //Setta a 1 il 25esmino bit, tutti 0 tranne il bit 25 a 1 
		}
		//mostriamo le mosse possibili
		move=move&4293918719; //Setta a 0 il 21esmino bit, and con tutti 1 tranne il bit 21 a 0
		show_moves(Yellow);
		enable_timer(1);
}

/******************************************************************************
**                            End Of File
******************************************************************************/
