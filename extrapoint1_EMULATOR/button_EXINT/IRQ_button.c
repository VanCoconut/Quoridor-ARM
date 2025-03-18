#include "button.h"
#include "lpc17xx.h"

extern uint8_t pressed_0;
extern uint8_t pressed_1;
extern uint8_t pressed_2;

void EINT0_IRQHandler (void)	  	/* INT0														 */
{		
	NVIC_DisableIRQ(EINT0_IRQn);
	pressed_0=1;
	LPC_PINCON->PINSEL4    &= ~(1 << 20);
	LPC_SC->EXTINT &= (1 << 0);     /* clear pending interrupt         */
}


void EINT1_IRQHandler (void)	  	/* KEY1														 */
{
	NVIC_DisableIRQ(EINT1_IRQn);		/* disable Button interrupts			 */
	pressed_1=1;
	LPC_PINCON->PINSEL4    &= ~(1 << 22);     /* GPIO pin selection */
	LPC_SC->EXTINT &= (1 << 1);     /* clear pending interrupt         */
}

void EINT2_IRQHandler (void)	  	/* KEY2														 */
{
	//ruota
	NVIC_DisableIRQ(EINT2_IRQn);
	pressed_2=1;
	LPC_PINCON->PINSEL4    &= ~(1 << 24);
  LPC_SC->EXTINT &= (1 << 2);     /* clear pending interrupt         */    
}


