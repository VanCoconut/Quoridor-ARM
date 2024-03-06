/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_RIT.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    RIT.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "lpc17xx.h"
#include "RIT.h"
#include "../GLCD/GLCD.h" 
#include "../JOYSTICK/joystick.h"
#include "../timer/timer.h"
#include "../GLCD/GLCD.h" 
#include "../CAN/CAN.h"

/******************************************************************************
** Function name:		RIT_IRQHandler
**
** Descriptions:		REPETITIVE INTERRUPT TIMER handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/

volatile uint8_t pressed_0=0;
volatile uint8_t pressed_1=0;
volatile uint8_t pressed_2=0;
extern uint16_t x1_P1;
extern uint16_t y1_P1;
extern uint16_t x1_P2;
extern uint16_t y1_P2;
extern uint16_t x_wall;
extern uint16_t y_wall;
extern unsigned int move;
extern char n_walls_P1;
extern char n_walls_P2;
char board_selection=1;
char no_more=0;
char flag_menu=0;
char flag_int0=0;

void RIT_IRQHandler (void)
{				
	static int up=0;
	static int select=0;
	static int left=0;
	static int right=0;
	static int down=0;
	static int mode=0;
	static int orientation;

	if(flag_menu==0){
	//GESTIONE MENU PRE PARTITA
		
		if((LPC_GPIO1->FIOPIN & (1<<29)) == 0){	
			/* Joytick UP pressed */
			up++;
			switch(up){
				case 1:
					selection_board_up();
					break;
				default:
					break;
			}
		}
		else if((LPC_GPIO1->FIOPIN & (1<<26)) == 0){	
			/* Joytick DOWN pressed */
			down++;
			switch(down){
				case 1:
						selection_board_down();
				break;
				default:
					break;
			}
		}
		else if((LPC_GPIO1->FIOPIN & (1<<25)) == 0){	
			/* Joytick SELECT pressed */
			select++;
			switch(select){
				case 1:
					set_num_boards();
					break;
				default:
					break;
			}
		}
		else{
				up=0;
				select=0;
				down=0;
			}
	}
	
	
	else if(flag_menu==1 && flag_int0==1){
		if((LPC_GPIO1->FIOPIN & (1<<29)) == 0){	
			/* Joytick UP pressed */
			up++;
			switch(up){
				case 1:
					mode=move<<8;
					mode=(mode>>28)&1;
					if(mode==0) select_up();
					else move_wall_up();
					break;
				case 20:
					mode=move<<8;
					mode=(mode>>28)&1;
					if(mode==0) select_up_plus();
					break;
				default:
					break;
			}
		}
		else if((LPC_GPIO1->FIOPIN & (1<<28)) == 0){	
			/* Joytick RIGHT pressed */
			right++;
			switch(right){
				case 1:
					mode=move<<8;
					mode=(mode>>28)&1;
					if(mode==0) select_right();
					else move_wall_right();
						break;
				case 20:
					mode=move<<8;
					mode=(mode>>28)&1;
					if(mode==0) select_right_plus();
					break;
				default:
					break;
			}
		}
		else if((LPC_GPIO1->FIOPIN & (1<<27)) == 0){	
			/* Joytick LEFT pressed */
			left++;
			switch(left){
				case 1:
						mode=move<<8;
						mode=(mode>>28)&1;
						if(mode==0) select_left();
						else move_wall_left();
						break;
				
				case 20:
					mode=move<<8;
					mode=(mode>>28)&1;
					if(mode==0) select_left_plus();
					break;
				default:
					break;
			}
		}
		else if((LPC_GPIO1->FIOPIN & (1<<26)) == 0){	
			/* Joytick DOWN pressed */
			down++;
			switch(down){
				case 1:
						mode=move<<8;
						mode=(mode>>28)&1;
						if(mode==0) select_down();
						else move_wall_down();
					break;
				case 20:
					mode=move<<8;
					mode=(mode>>28)&1;
					if(mode==0) select_down_plus();
					break;
				default:
					break;
			}
		}
		else if((LPC_GPIO1->FIOPIN & (1<<25)) == 0){	
			/* Joytick SELECT pressed */
			select++;
			switch(select){
				case 1:
					mode=move<<8;
					mode=(mode>>28)&1;
					if(mode==0) move_direction();
					else perma_wall();
					break;
				default:
					break;
			}
		}
		else{
				up=0;
				select=0;
				left=0;
				right=0;
				down=0;
			}
		
		/* button management */
		if(pressed_1>1){ 
			/* KEY1 pressed */
				if((LPC_GPIO2->FIOPIN & (1<<11)) == 0){	/* KEY1 pressed */
					switch(pressed_1){				
						case 2:	
							//char player=(move>>24)&1;
							NVIC_EnableIRQ(EINT2_IRQn);
							mode=move<<8;
							mode=(mode>>28)&1;
							if(mode==0){ 
								//eravamo in token e vogliamo andare in muro
								show_moves(White);
								if( ((move>>24)&1)==0 && n_walls_P1==0){ 
									GUI_Text(50, 235, (uint8_t *) "NO MORE WALLS LEFT", Blue2, White);
									show_moves(Yellow);
									break;
								}else if( ((move>>24)&1)==1 && n_walls_P2==0){
									GUI_Text(50, 235, (uint8_t *) "NO MORE WALLS LEFT", Red, White);
									show_moves(Yellow);
									break;
								}
								move=move|1048576; //Setta a 1 il 21esimno bit 
								if(no_more==0) move=move|65536;	//La prima volta settiamo il 17 per partire in orizzontale
								place_wall(x_wall,y_wall, Green);
								
								no_more=1;
							}else if(mode==1){
									move=move&32505855; //setto a 0 il 21esimo bit (e mantengo invariato il bit del player);
									place_wall(x_wall,y_wall, White);
									show_moves(Yellow);
							}
							break;
						default:
							break;
					}
					pressed_1++;
				}
				else {	/* button released */
					pressed_1=0;			
					NVIC_EnableIRQ(EINT1_IRQn);							 /* enable Button interrupts			*/
					LPC_PINCON->PINSEL4    |= (1 << 22);     /* External interrupt 0 pin selection */
				}
		}//fine joystick
	} 
	
	if(pressed_0>1){
		/* INT0 pressed */
		if((LPC_GPIO2->FIOPIN & (1<<10)) == 0){			/* INT0 pressed */
			switch(pressed_0){				
				case 2:																	/* pay attention here: please see slides 19_ to understand value 2 */
						flag_int0=1;
						show_moves(Yellow);
						CAN_TxMsg.len = 0;
						CAN_TxMsg.id = 1;
						CAN_TxMsg.format = STANDARD_FORMAT;
						CAN_TxMsg.type = DATA_FRAME;
						CAN_wrMsg (2, &CAN_TxMsg);               // transmit message	
						init_timer(1, 0x17D7840);								// 1s time 25MHz
						enable_timer(1);
					break;
				default:
					break;
			}
			pressed_0++;
		}
		else {	/* button released */
			pressed_0=0;			
			//NVIC_EnableIRQ(EINT0_IRQn);							 /* enable Button interrupts			*/
			LPC_PINCON->PINSEL4    |= (1 << 20);     /* External interrupt 0 pin selection */
		}
	}
	
	
	
	if(pressed_2>1){
		/* KEY2 pressed */
		if((LPC_GPIO2->FIOPIN & (1<<12)) == 0){	/* KEY2 pressed */
			switch(pressed_2){				
				case 2:				/* pay attention here: please see slides 19_ to understand value 2 */
					orientation=move<<12;
					orientation=orientation>>28;  // 0 V, 1 H
					break_wall(x_wall, y_wall);
					if(orientation==0){	//da verticale diventa orizzontale
						rotate_wall_to_horizontal();
					}
					else if(orientation==1){ //da orrizzontale diventa verticale
						rotate_wall_to_vertical();
					}
				
					place_wall(x_wall,y_wall, Green);
					
					break;
				default:
					break;
			}
			pressed_2++;
		}
		else {	/* button released */
			pressed_2=0;			
			NVIC_EnableIRQ(EINT2_IRQn);							 /* enable Button interrupts			*/
			LPC_PINCON->PINSEL4    |= (1 << 24);     /* External interrupt 0 pin selection */
		}
	}
	
	else{
			if(pressed_0==1) pressed_0++;
			
			if(pressed_1==1) pressed_1++;
			
			if(pressed_2==1) pressed_2++;
	}
	
  LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
	
  return;
}


/******************************************************************************
**                            End Of File
******************************************************************************/
