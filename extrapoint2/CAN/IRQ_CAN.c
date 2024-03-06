/*----------------------------------------------------------------------------
 * Name:    Can.c
 * Purpose: CAN interface for for LPC17xx with MCB1700
 * Note(s): see also http://www.port.de/engl/canprod/sv_req_form.html
 *----------------------------------------------------------------------------
 * This file is part of the uVision/ARM development tools.
 * This software may only be used under the terms of a valid, current,
 * end user licence from KEIL for a compatible version of KEIL software
 * development tools. Nothing else gives you the right to use this software.
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 * Copyright (c) 2009 Keil - An ARM Company. All rights reserved.
 *----------------------------------------------------------------------------*/

#include <lpc17xx.h>                  /* LPC17xx definitions */
#include "CAN.h"                      /* LPC17xx CAN adaption layer */
#include "../GLCD/GLCD.h"
#include <stdlib.h> 
#include "../JOYSTICK/joystick.h"

extern uint8_t icr ; 										//icr and result must be global in order to work with both real and simulated landtiger.
extern uint32_t result;
extern CAN_msg       CAN_TxMsg;    /* CAN message for sending */
extern CAN_msg       CAN_RxMsg;    /* CAN message for receiving */   
extern uint16_t x1_P1;
extern uint16_t y1_P1;
extern uint16_t x1_P2;
extern uint16_t y1_P2;

static int puntiRicevuti1 = 0;
static int puntiInviati1 = 0;

static int puntiRicevuti2 = 0;
static int puntiInviati2 = 0;
char id1;
char id2;
char mode1;


uint16_t val_RxCoordX = 0;            /* Locals used for display */
uint16_t val_RxCoordY = 0;

/*----------------------------------------------------------------------------
  CAN interrupt handler
 *----------------------------------------------------------------------------*/
void CAN_IRQHandler (void)  {

  /* check CAN controller 1 */
	icr = 0;
  icr = (LPC_CAN1->ICR | icr) & 0xFF;               /* clear interrupts */
	
  if (icr & (1 << 0)) {                          		/* CAN Controller #1 meassage is received */
		CAN_rdMsg (1, &CAN_RxMsg);	                		/* Read the message */
    LPC_CAN1->CMR = (1 << 2);                    		/* Release receive buffer */
		
		val_RxCoordX = (CAN_RxMsg.data[0] << 8)  ;
		val_RxCoordX = val_RxCoordX | CAN_RxMsg.data[1];
	
		val_RxCoordY = (CAN_RxMsg.data[2] << 8);
		val_RxCoordY = val_RxCoordY | CAN_RxMsg.data[3];
		
		mode1=CAN_RxMsg.data[4];
		
		//ID1 è l'id del can1, se è 1 allora in giocatore rosso usa il can1,
		id1=CAN_RxMsg.id;

		
		if(id1==1 && puntiRicevuti1 ==0){
			id1=2;
		}
		
		if(mode1==0){
			//l'avversario ha mosso la pedina
			if(id1==1){
				//sei il giocatore 1, quello che ti arriva quindi è il giocatore 2
					x1_P2=val_RxCoordX;
					y1_P2=val_RxCoordY;
					color_box(x1_P2,y1_P2,Red);
			}else{
				//sei il giocatore 2, ti arriva il rosso
					x1_P1=val_RxCoordX;
					y1_P1=val_RxCoordY;
					color_box(x1_P1,y1_P1,Blue2);
			}
			
		}else if (mode1==1){
			//l'avversario ha piazzato un muro
			if(id1==1){
				//sei il giocatore 1, quello che ti arriva quindi è il giocatore 2
					if(CAN_RxMsg.data[5]==1){
						//il muro è orizzontale
			      build_wall_h(val_RxCoordX,val_RxCoordY,Magenta);
					}else {
						//il muro è verticale
						build_wall_v(val_RxCoordX,val_RxCoordY,Magenta);
					}
			}else{
				//sei il giocatore 2, ti arriva il rosso
					if(CAN_RxMsg.data[5]==1){
						//il muro è orizzontale
			      build_wall_h(val_RxCoordX,val_RxCoordY,Magenta);
					}else {
					  //il muro è verticale
						build_wall_v(val_RxCoordX,val_RxCoordY,Magenta);
					}
			}
		}
	
		puntiRicevuti1++;
  }
	if (icr & (1 << 1)) {                         /* CAN Controller #1 meassage is transmitted */
		// do nothing in this example
		puntiInviati1++;
	}
		
	/* check CAN controller 2 */
	icr = 0;
	icr = (LPC_CAN2->ICR | icr) & 0xFF;             /* clear interrupts */

	if (icr & (1 << 0)) {                          	/* CAN Controller #2 meassage is received */
		CAN_rdMsg (2, &CAN_RxMsg);	                		/* Read the message */
    LPC_CAN2->CMR = (1 << 2);                    		/* Release receive buffer */
		
		val_RxCoordX = (CAN_RxMsg.data[0] << 8);
		val_RxCoordX = val_RxCoordX | CAN_RxMsg.data[1];
		
		val_RxCoordY = (CAN_RxMsg.data[2] << 8);
		val_RxCoordY = val_RxCoordY | CAN_RxMsg.data[3];
		
		mode1=CAN_RxMsg.data[4];
		
		//ID2 è l'id del can2, se è 1= player rosso, 2= player blue 
		id2=CAN_RxMsg.id;
		
		if(id2==1 && puntiRicevuti2==0){
			id2=2;
		}
		
	if(mode1==0){
			//l'avversario ha mosso la pedina
			if(id2==1){
				//sei il giocatore 1
					x1_P2=val_RxCoordX;
					y1_P2=val_RxCoordY;
					color_box(x1_P2,y1_P2,Red);
			}else{
				//sei il giocatore 2
				x1_P1=val_RxCoordX;
				y1_P1=val_RxCoordY;
				color_box(x1_P1,y1_P1,Blue2);
			}
			
		}else if (mode1==1){
			//l'avversario ha piazzato un muro
			if(id2==1){
				//sei il giocatore 1, quello che ti arriva quindi è il giocatore 2
					if(CAN_RxMsg.data[5]==1){
						//il muro è orizzontale
			      build_wall_h(val_RxCoordX,val_RxCoordY,Magenta);
					}else {
						//il muro è verticale
						build_wall_v(val_RxCoordX,val_RxCoordY,Magenta);
					}
			}else{
				//sei il giocatore 2, ti arriva il rosso
					if(CAN_RxMsg.data[5]==1){
						//il muro è orizzontale
			      build_wall_h(val_RxCoordX,val_RxCoordY,Magenta);
					}else {
					  //il muro è verticale
						build_wall_v(val_RxCoordX,val_RxCoordY,Magenta);
					}
			}
		}
		
		puntiRicevuti2++;
	}
	if (icr & (1 << 1)) {                         /* CAN Controller #2 meassage is transmitted */
		// do nothing in this example
		puntiInviati2++;
	}
}
