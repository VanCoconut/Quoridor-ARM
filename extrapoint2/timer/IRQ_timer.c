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
#include "../JOYSTICK/joystick.h"
#include "../RIT/RIT.h"
#include "../CAN/CAN.h"

/******************************************************************************
** Function name:		Timer0_IRQHandler
**
** Descriptions:		Timer/Counter 0 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/

extern unsigned int move;
extern char npc;
extern uint16_t x1_P1;
extern uint16_t y1_P1;
extern uint16_t x1_P2;
extern uint16_t y1_P2;
extern char n_walls_P1;
extern char n_walls_P2;
extern char id;
int mode;
extern char multiplayer;
extern uint16_t x_wall;
extern uint16_t y_wall;
extern char no_more;
int i =20;
int use_npc=0;
static int orientation;

void TIMER0_IRQHandler (void)
{
	GUI_Text(40, 235, (uint8_t *) "NO WALL ALLOWED HERE", White, White);
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
		int mode;
		mode=move<<8;
		mode=(mode>>28)&1;

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
	
		if(n_walls_P1==0 || n_walls_P2==0) GUI_Text(50, 235, (uint8_t *) "NO MORE WALLS LEFT", White, White);
	
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
			
			if(npc==1){
				//NPC FA UNA MOSSA
				use_npc=choose_npc_move();
			}
		}
		//mostriamo le mosse possibili
		if(multiplayer==1){
				if(player==1){
					//da 0 a 1
					if(mode==0){
						CAN_TxMsg.data[0] = ((x1_P1) & 0xFF00) >> 8;
						CAN_TxMsg.data[1] = (x1_P1) & 0xFF;
						CAN_TxMsg.data[2] = (y1_P1 & 0xFF00 ) >> 8;
						CAN_TxMsg.data[3] = (y1_P1) & 0xFF;
						CAN_TxMsg.data[4] = 0; //bit del mode
						CAN_TxMsg.len = 5;
						CAN_TxMsg.id = 1;
						CAN_TxMsg.format = STANDARD_FORMAT;
						CAN_TxMsg.type = DATA_FRAME;
						CAN_wrMsg (2, &CAN_TxMsg);               // transmit message
						//puntiSpediti1+=1;
					}else if(mode==1){
						orientation=move<<12;
						orientation=orientation>>28;
						CAN_TxMsg.data[0] = ((x_wall) & 0xFF00) >> 8;
						CAN_TxMsg.data[1] = (x_wall) & 0xFF;
						CAN_TxMsg.data[2] = (y_wall & 0xFF00 ) >> 8;
						CAN_TxMsg.data[3] = (y_wall) & 0xFF;
						CAN_TxMsg.data[4] = 1;  //bit del mode
						if(orientation==1) CAN_TxMsg.data[5] = 1;  //bit del mode
						else CAN_TxMsg.data[5] = 0;

						CAN_TxMsg.len = 6;
						CAN_TxMsg.id = 1;
						CAN_TxMsg.format = STANDARD_FORMAT;
						CAN_TxMsg.type = DATA_FRAME;
						CAN_wrMsg (2, &CAN_TxMsg);               // transmit message
						//puntiSpediti1+=1;
					
					}
				}else if(player==0){
					//da 1 a 0 
					if(mode==0){ //abbiamo mosso la pedina
						CAN_TxMsg.data[0] = (( x1_P2) & 0xFF00) >> 8;
						CAN_TxMsg.data[1] = (x1_P2 ) & 0xFF;
						CAN_TxMsg.data[2] = (y1_P2 & 0xFF00 ) >> 8;
						CAN_TxMsg.data[3] = y1_P2 & 0xFF;
						CAN_TxMsg.data[4] = 0; //bit del mode
						CAN_TxMsg.len = 5;
						CAN_TxMsg.id = 2;
						CAN_TxMsg.format = STANDARD_FORMAT;
						CAN_TxMsg.type = DATA_FRAME;
						CAN_wrMsg (1, &CAN_TxMsg);               // transmit message
						//puntiSpediti1+=1;
					}else if(mode==1){ //abbiamo piazzato un muro
						orientation=move<<12;
						orientation=orientation>>28;
						CAN_TxMsg.data[0] = (( x_wall) & 0xFF00) >> 8;
						CAN_TxMsg.data[1] = (x_wall ) & 0xFF;
						CAN_TxMsg.data[2] = (y_wall & 0xFF00 ) >> 8;
						CAN_TxMsg.data[3] = y_wall & 0xFF;
						CAN_TxMsg.data[4] = 1; //bit del mode
						if(orientation==1) CAN_TxMsg.data[5] = 1;  //bit del mode
						else CAN_TxMsg.data[5] = 0; 
						CAN_TxMsg.len = 5;
						CAN_TxMsg.id = 2;
						CAN_TxMsg.format = STANDARD_FORMAT;
						CAN_TxMsg.type = DATA_FRAME;
						CAN_wrMsg (1, &CAN_TxMsg);  
					}
				}
		}
		move=move&4293918719; //Setta a 0 il 21esmino bit, and con tutti 1 tranne il bit 21 a 0
		x_wall=104;
		y_wall=100;
		show_moves(Yellow);
		enable_timer(1);
		if(use_npc==1) npc=1;
}


/* 
	if(display.y < 280 && display.y > 140){ // BIANCO
			// send from CAN2 to CAN1
			if(display.x != precX1 || display.y != precY1){
				precX2 = display.x;
				precY2 = display.y;
				CAN_TxMsg.data[0] = ((display.x ) & 0xFF00) >> 8;
				CAN_TxMsg.data[1] = (display.x ) & 0xFF;
				CAN_TxMsg.data[2] = (display.y & 0xFF00 ) >> 8;
				CAN_TxMsg.data[3] = display.y & 0xFF;
				CAN_TxMsg.len = 4;
				CAN_TxMsg.id = 1;
				CAN_TxMsg.format = STANDARD_FORMAT;
				CAN_TxMsg.type = DATA_FRAME;
				CAN_wrMsg (2, &CAN_TxMsg);               // transmit message
				puntiSpediti1+=1;				
				TP_DrawPoint_Magnifier(&display);
				}

			clear = 0;
	}
*/


/******************************************************************************
**                            End Of File
******************************************************************************/
