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
#include "../GLCD/GLCD.h" 
#include "../timer/timer.h"
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
int walls[17][2];


char control_right(){
	char x;
	char player=(move>>24)&1;
	if(player==0){
		if(x1_P1>200){
			return 0;
		}
		else if((x1_P1+33)==x1_P2 && y1_P1==y1_P2){
			for(x=0; x<17; x++){
			if(walls[x][0]==x1_P1+61){
					if(walls[x][1]==y1_P1-34 || walls[x][1]==y1_P1-1){
						return 3;
					}
				}
		}
			return 2;
		}
		//muro
		for(x=0; x<17; x++){
			if(walls[x][0]==x1_P1+28){
					if(walls[x][1]==y1_P1-34 || walls[x][1]==y1_P1-1){
						return 0;
					}
				}
		}
		// se non c'è niente returna 1
		return 1;		
	} 
	else {
			if(x1_P2>200){
				return 0;
			}
			else if((x1_P2+33)==x1_P1 && y1_P1==y1_P2){
				for(x=0; x<17; x++){
					if(walls[x][0]==x1_P2+61){
							if(walls[x][1]==y1_P2-34 || walls[x][1]==y1_P2-1){
								return 3;
							}
						}
				}
				return 2;
			}
			//muro
		for(x=0; x<17; x++){
			if(walls[x][0]==x1_P2+28){
					if(walls[x][1]==y1_P2-34 || walls[x][1]==y1_P2-1){
						return 0;
					}
				}
		}
		// se non c'è niente returna 1
		return 1;		
	}
} 

char control_left(){
	char x;
	char player=(move>>24)&1;
	if(player==0){
		if(x1_P1<10){
			return 0;
		}
		else if((x1_P1-33)==x1_P2 && y1_P1==y1_P2){
			for(x=0; x<17; x++){
			if(walls[x][0]==x1_P1-38){
					if(walls[x][1]==y1_P1-34 || walls[x][1]==y1_P1-1){
						return 3;
					}
				}
			}
			return 2;
		}
		//muro
		for(x=0; x<17; x++){
			if(walls[x][0]==x1_P1-5){
					if(walls[x][1]==y1_P1-34 || walls[x][1]==y1_P1-1){
						return 0;
					}
				}
		}
		// se non c'è niente returna 1
		return 1;		
	}
	else {
		if(x1_P2<10){
			return 0;
		}
		else if((x1_P2-33)==x1_P1 && y1_P1==y1_P2){
			for(x=0; x<17; x++){
				if(walls[x][0]==x1_P2-38){
						if(walls[x][1]==y1_P2-34 || walls[x][1]==y1_P2-1){
							return 3;
						}
					}
			}
			return 2;
		}
		//muro
		for(x=0; x<17; x++){
			if(walls[x][0]==x1_P2-5){
					if(walls[x][1]==y1_P2-34 || walls[x][1]==y1_P2-1){
						return 0;
					}
				}
		}
		// se non c'è niente returna 1
		return 1;		
	}
}

char control_up(){
	char x;
	char player=(move>>24)&1;
	if (player==0){
		if(y1_P1<10){
			return 0;
		}
		else if((y1_P1-33)==y1_P2 && x1_P1==x1_P2){
			for(x=0; x<17; x++){
			if(walls[x][0]==x1_P1-34 || walls[x][0]==x1_P1-1){
					if(walls[x][1]==y1_P1-38){
						return 3;
					}
				}
			}
			return 2;
		}
		//muro
		for(x=0; x<17; x++){
			if(walls[x][0]==x1_P1-34 || walls[x][0]==x1_P1-1){
					if(walls[x][1]==y1_P1-5){
						return 0;
					}
				}
		}
		// se non c'è niente returna 1
		return 1;	
			
	}else {
				if(y1_P2<10){
			return 0;
		}
		else if((y1_P2-33)==y1_P1 && x1_P1==x1_P2){
			for(x=0; x<17; x++){
			if(walls[x][0]==x1_P2-34 || walls[x][0]==x1_P2-1){
					if(walls[x][1]==y1_P2-38){
						return 3;
					}
				}
			}
			
			return 2;
		}
		//muro
		for(x=0; x<17; x++){
			if(walls[x][0]==x1_P2-34 || walls[x][0]==x1_P2-1){
					if(walls[x][1]==y1_P2-5){
						return 0;
					}
				}
		}
		// se non c'è niente returna 1
		return 1;	
	}
}

char control_down(){
	char x;
	char player=(move>>24)&1;
	if(player==0){
		if(y1_P1>200){
			return 0; //sotto non è possibile
		}
		else if((y1_P1+33)==y1_P2 && x1_P1==x1_P2){
			for(x=0; x<17; x++){
			if(walls[x][0]==x1_P1-34 || walls[x][0]==x1_P1-1){
					if(walls[x][1]==y1_P1+61){
						return 3;
					}
				}
			}
			return 2;
		}
		//muro
		for(x=0; x<17; x++){
			if(walls[x][0]==x1_P1-34 || walls[x][0]==x1_P1-1){
					if(walls[x][1]==y1_P1+28){
						return 0;
					}
				}
		}
		// se non c'è niente returna 1
		return 1;	
	}else {
		if(y1_P2>200){
			return 0; //sotto non è possibile
		}
		else if((y1_P2+33)==y1_P1 && x1_P1==x1_P2){
			for(x=0; x<17; x++){
			if(walls[x][0]==x1_P2-34 || walls[x][0]==x1_P2-1){
					if(walls[x][1]==y1_P2+61){
						return 3;
					}
				}
			}
			return 2;
		}
		//muro
		for(x=0; x<17; x++){
			if(walls[x][0]==x1_P2-34 || walls[x][0]==x1_P2-1){
					if(walls[x][1]==y1_P2+28){
						return 0;
					}
				}
		}
		// se non c'è niente returna 1
		return 1;	
	}
}


void show_moves(uint16_t Color){
	char player=(move>>24)&1;
	if(player==0){
		if (control_right()==0);
		else if(control_right()==2){
			//colora box a 2 destra
			color_box(x1_P1+66, y1_P1, Color);
		}
		else if(control_right()==3){
			move=move|16777216; // da 0 a 1
			if (control_up()==1) color_box(x1_P1+33, y1_P1-33, Color);
			if(control_down()==1) color_box(x1_P1+33, y1_P1+33, Color);
			move=move&16777215; //da 1 a 0
		}
		else{
				//colora box a destra
				color_box(x1_P1+33, y1_P1, Color);
		}
		if(control_left()==0);
		else if(control_left()==2){
			//colora box a 2 sinistra
			color_box(x1_P1-66, y1_P1, Color);
		}
		else if(control_left()==3){
			move=move|16777216; // da 0 a 1
			if (control_up()==1) color_box(x1_P1-33, y1_P1-33, Color);
			if(control_down()==1) color_box(x1_P1-33, y1_P1+33, Color);
			move=move&16777215; //da 1 a 0
		}
		else{
			//colora box a sinistra
			color_box(x1_P1-33, y1_P1, Color);
		}
			
		if(control_up()==0);
		else if(control_up()==2){
			//colora box a 2 up
			color_box(x1_P1, y1_P1-66, Color);
		}
		else if(control_up()==3){
			move=move|16777216; // da 0 a 1
			if (control_left()==1) color_box(x1_P1-33, y1_P1-33, Color);
			if(control_right()==1) color_box(x1_P1+33, y1_P1-33, Color);
			move=move&16777215; //da 1 a 0
		}
		else{
				//colora box sopra
				color_box(x1_P1, y1_P1-33, Color);
			}
			
		if(control_down()==0);
		else if(control_down()==2){
			//colora box a 2 down
			color_box(x1_P1, y1_P1+66, Color);
		}
		else if(control_down()==3){
			move=move|16777216; // da 0 a 1
			if (control_left()==1) color_box(x1_P1-33, y1_P1+33, Color);
			if(control_right()==1) color_box(x1_P1+33, y1_P1+33, Color);
			move=move&16777215; //da 1 a 0
		}
		else{
			//colora box sotto
			color_box(x1_P1, y1_P1+33, Color);
		}
			
	}else if(player==1){
		
		if (control_right()==0);
		else if(control_right()==2){
			//colora box a 2 destra
			color_box(x1_P2+66, y1_P2, Color);
		}
		else if(control_right()==3){
			move=move&16777215; //da 1 a 0
			if (control_up()==1) color_box(x1_P2+33, y1_P2-33, Color);
			if(control_down()==1) color_box(x1_P2+33, y1_P2+33, Color);
			move=move|16777216; // da 0 a 1
		}
		else{
				//colora box a destra
				color_box(x1_P2+33, y1_P2, Color);
		}
		
		if(control_left()==0);
		else if(control_left()==2){
			//colora box a 2 sinistra
			color_box(x1_P2-66, y1_P2, Color);
		}
		else if(control_left()==3){
			move=move&16777215; //da 1 a 0
			if (control_up()==1) color_box(x1_P2-33, y1_P2-33, Color);
			if(control_down()==1) color_box(x1_P2-33, y1_P2+33, Color);
			move=move|16777216; // da 0 a 1
		}
		else{
			//colora box a sinistra
			color_box(x1_P2-33, y1_P2, Color);
		}
			
		if(control_up()==0);
		else if(control_up()==2){
			//colora box a 2 up
			color_box(x1_P2, y1_P2-66, Color);
		}
		else if(control_up()==3){
			move=move&16777215; //da 1 a 0
			if (control_left()==1) color_box(x1_P2-33, y1_P2-33, Color);
			if(control_right()==1) color_box(x1_P2+33, y1_P2-33, Color);
			move=move|16777216; // da 0 a 1
		}
		else{
				//colora box sopra
				color_box(x1_P2, y1_P2-33, Color);
			}
			
		if(control_down()==0);
		else if(control_down()==2){
			//colora box a 2 down
			color_box(x1_P2, y1_P2+66, Color);
		}
		else if(control_down()==3){
			move=move&16777215; //da 1 a 0
			if (control_left()==1) color_box(x1_P2-33, y1_P2+33, Color);
			if(control_right()==1) color_box(x1_P2+33, y1_P2+33, Color);
			move=move|16777216; // da 0 a 1
		}
		else{
			//colora box sotto
			color_box(x1_P2, y1_P2+33, Color);
		}
	}
}


void color_box(uint16_t x1,uint16_t y1, uint16_t color){
	uint16_t x2=x1+26;
	char j=0;
	for(j=0;j<27;j++){
					LCD_DrawLine( x1, y1, x2, y1, color);
					y1+=1;
				}
}


void select_right(){
	char player=(move>>24)&1;
	if(player==0){
			if(left==1){
				if(control_left()==2) color_box(x1_P1-66, y1_P1, Yellow);
				else color_box(x1_P1-33, y1_P1, Yellow);
				left=0;
			}else if(down==1){
				if(control_down()==2) color_box(x1_P1, y1_P1+66, Yellow); 
				else color_box(x1_P1, y1_P1+33, Yellow);
				down=0;
			}else if(up==1){
				if(control_up()==2) color_box(x1_P1, y1_P1-66, Yellow);
				else color_box(x1_P1, y1_P1-33, Yellow);
				up=0;
			}else if(left_up==1){
					 color_box(x1_P1-33, y1_P1-33, Yellow);
					left_up=0;
				}else if(left_down==1){
					 color_box(x1_P1-33, y1_P1+33, Yellow);
					left_down=0;
				}else if(right_up==1){
					 color_box(x1_P1+33, y1_P1-33, Yellow);
					right_up=0;
				}else if(right_down==1){
					 color_box(x1_P1+33, y1_P1+33, Yellow);
					right_down=0;
				}else if(up_right==1){
					 color_box(x1_P1-33, y1_P1-33, Yellow);
					left_up=0;
				}else if(up_left==1){
					 color_box(x1_P1+33, y1_P1-33, Yellow);
					left_down=0;
				}else if(down_right==1){
					 color_box(x1_P1-33, y1_P1+33, Yellow);
					right_up=0;
				}else if(down_left==1){
					 color_box(x1_P1-33, y1_P1+33, Yellow);
					right_down=0;
				}
			
			if(control_right()==1){
				color_box(x1_P1+33, y1_P1, Magenta);
				right=1;
			}
			if(control_right()==2){
				color_box(x1_P1+66, y1_P1, Magenta);
				right=1;
			}
	}else if(player==1){
				if(left==1){
					if(control_left()==2) color_box(x1_P2-66, y1_P2, Yellow);
					else color_box(x1_P2-33, y1_P2, Yellow);
				left=0;
			}else if(down==1){
				if(control_down()==2) color_box(x1_P2, y1_P2+66, Yellow);
				else color_box(x1_P2, y1_P2+33, Yellow);
				down=0;
			}else if(up==1){
				if(control_up()==2) color_box(x1_P2, y1_P2-66, Yellow);
				else color_box(x1_P2, y1_P2-33, Yellow);
				up=0;
			}else if(left_up==1){
					 color_box(x1_P2-33, y1_P2-33, Yellow);
					left_up=0;
				}else if(left_down==1){
					 color_box(x1_P2-33, y1_P2+33, Yellow);
					left_down=0;
				}else if(right_up==1){
					 color_box(x1_P2+33, y1_P2-33, Yellow);
					right_up=0;
				}else if(right_down==1){
					 color_box(x1_P2+33, y1_P2+33, Yellow);
					right_down=0;
				}else if(up_right==1){
					 color_box(x1_P2-33, y1_P2-33, Yellow);
					left_up=0;
				}else if(up_left==1){
					 color_box(x1_P2+33, y1_P2-33, Yellow);
					left_down=0;
				}else if(down_right==1){
					 color_box(x1_P2-33, y1_P2+33, Yellow);
					right_up=0;
				}else if(down_left==1){
					 color_box(x1_P2-33, y1_P2+33, Yellow);
					right_down=0;
				}
			
			if(control_right()==1){
				color_box(x1_P2+33, y1_P2, Magenta);
				right=1;
			}
			if(control_right()==2){
				color_box(x1_P2+66, y1_P2, Magenta);
				right=1;
			}
		}
			
}

void select_left(){
		char player=(move>>24)&1;
		if(player==0){
				if(right==1){
					if(control_right()==2) color_box(x1_P1+66, y1_P1, Yellow);
					else color_box(x1_P1+33, y1_P1, Yellow);
					right=0;
				}else if(down==1){
					if(control_down()==2) color_box(x1_P1, y1_P1+66, Yellow);
					else color_box(x1_P1, y1_P1+33, Yellow);
					down=0;
				}else if(up==1){
					if(control_up()==2) color_box(x1_P1, y1_P1-66, Yellow);
					else color_box(x1_P1, y1_P1-33, Yellow);
					up=0;
				}
				plus_condition();
				if(control_left()==1){
					color_box(x1_P1-33, y1_P1, Magenta);
					left=1;
				}
				if(control_left()==2){
					color_box(x1_P1-66, y1_P1, Magenta);
					left=1;
				}
		}else if(player==1){
				if(right==1){
						if(control_right()==2) color_box(x1_P2+66, y1_P2, Yellow);
						else color_box(x1_P2+33, y1_P2, Yellow);
						right=0;
				}else if(down==1){
					if(control_down()==2) color_box(x1_P2, y1_P2+66, Yellow);
					else color_box(x1_P2, y1_P2+33, Yellow);
					down=0;
				}else if(up==1){
					if(control_up()==2) color_box(x1_P2, y1_P2-66, Yellow);
					else color_box(x1_P2, y1_P2-33, Yellow);
					up=0;
				}
				plus_condition();
				
				if(control_left()==1){
					color_box(x1_P2-33, y1_P2, Magenta);
					left=1;
				}
				if(control_left()==2){
					color_box(x1_P2-66, y1_P2, Magenta);
					left=1;
				}
		}
}
void select_down(){
	char player=(move>>24)&1;
	if(player==0){
			if(right==1){
				if(control_right()==2) color_box(x1_P1+66, y1_P1, Yellow);
				else color_box(x1_P1+33, y1_P1, Yellow);
				right=0;
			}else if(left==1){
				if(control_left()==2) color_box(x1_P1-66, y1_P1, Yellow);
				else color_box(x1_P1-33, y1_P1, Yellow);
				left=0;
			}else if(up==1){
				if(control_up()==2) color_box(x1_P1, y1_P1-66, Yellow);
				else color_box(x1_P1, y1_P1-33, Yellow);
				up=0;
			}
			plus_condition();
			
			if(control_down()==1){
				color_box(x1_P1, y1_P1+33, Magenta);
				down=1;
			}
			if(control_down()==2){
				color_box(x1_P1, y1_P1+66, Magenta);
				down=1;
			}
	}else if(player==1){
		if(right==1){
			if(control_up()==2) color_box(x1_P2+66, y1_P2, Yellow);
			else color_box(x1_P2+33, y1_P2, Yellow);
			right=0;
		}else if(left==1){
			if(control_up()==2) color_box(x1_P2-66, y1_P2, Yellow);
			else color_box(x1_P2-33, y1_P2, Yellow);
			left=0;
		}else if(up==1){
			if(control_up()==2) color_box(x1_P2, y1_P2-66, Yellow);
			else color_box(x1_P2, y1_P2-33, Yellow);
			up=0;
		}
		plus_condition();
		
		if(control_down()==1){
			color_box(x1_P2, y1_P2+33, Magenta);
			down=1;
		}
		if(control_down()==2){
				color_box(x1_P2, y1_P2+66, Magenta);
				down=1;
			}
	}
}

void select_up(){
	char player=(move>>24)&1;
	if(player==0){
			if(right==1){
				if(control_right()==2) color_box(x1_P1+66, y1_P1, Yellow);
				else color_box(x1_P1+33, y1_P1, Yellow);
				right=0;
			}else if(left==1){
				if(control_left()==2) color_box(x1_P1-66, y1_P1, Yellow);
				else color_box(x1_P1-33, y1_P1, Yellow);
				left=0;
			}else if(down==1){
				if(control_up()==2) color_box(x1_P1, y1_P1+66, Yellow);
				else color_box(x1_P1, y1_P1+33, Yellow);
				down=0;
			}
			plus_condition();
			
			if(control_up()==1){
				color_box(x1_P1, y1_P1-33, Magenta);
				up=1;
			}
			if(control_up()==2){
				color_box(x1_P1, y1_P1-66, Magenta);
				up=1;
			}
	}else if(player==1){
			if(right==1){
				if(control_right()==2) color_box(x1_P2+66, y1_P2, Yellow);
				else color_box(x1_P2+33, y1_P2, Yellow);
				right=0;
			}else if(left==1){
				if(control_right()==2) color_box(x1_P2-66, y1_P2, Yellow);
				else color_box(x1_P2-33, y1_P2, Yellow);
				left=0;
			}else if(down==1){
				if(control_down()==2) color_box(x1_P2, y1_P2+66, Yellow);
				else color_box(x1_P2, y1_P2+33, Yellow);
				down=0;
			}
			plus_condition();
			
			if(control_up()==1){
				color_box(x1_P2, y1_P2-33, Magenta);
				up=1;
			}
			if(control_up()==2){
				color_box(x1_P2, y1_P2-66, Magenta);
				up=1;
			}
	}
}
void select_left_plus(){
		char player=(move>>24)&1;
		if(player==0){
				if(right==1){
					if(control_right()==2) color_box(x1_P1+66, y1_P1, Yellow);
					else color_box(x1_P1+33, y1_P1, Yellow);
					right=0;
				} if(down==1){
					if(control_down()==2) color_box(x1_P1, y1_P1+66, Yellow);
					else color_box(x1_P1, y1_P1+33, Yellow);
					down=0;
				} if(up==1){
					if(control_up()==2) color_box(x1_P1, y1_P1-66, Yellow);
					else color_box(x1_P1, y1_P1-33, Yellow);
					up=0;
				}if(left==1){
					if(control_left()==2) color_box(x1_P1-66, y1_P1, Yellow);
					else color_box(x1_P1-33, y1_P1, Yellow);
					left=0;
				}
				
				if(control_up()==3){
					move=move|16777216; // da 0 a 1
					if(control_left()==1) color_box(x1_P1-33, y1_P1-33, Magenta);
					move=move&16777215; //da 1 a 0
					left_up=1;
				}
				else if(control_down()==3){
					move=move|16777216; // da 0 a 1
					if(control_left()==1) color_box(x1_P1-33, y1_P1+33, Magenta);
					move=move&16777215; //da 1 a 0
					left_down=1;
				}
			
		}else if(player==1){
				if(right==1){
						if(control_right()==2) color_box(x1_P2+66, y1_P2, Yellow);
						else color_box(x1_P2+33, y1_P2, Yellow);
						right=0;
				}else if(down==1){
					if(control_down()==2) color_box(x1_P2, y1_P2+66, Yellow);
					else color_box(x1_P2, y1_P2+33, Yellow);
					down=0;
				}else if(up==1){
					if(control_up()==2) color_box(x1_P2, y1_P2-66, Yellow);
					else color_box(x1_P2, y1_P2-33, Yellow);
					up=0;
				}if(left==1){
					if(control_left()==2) color_box(x1_P1-66, y1_P1, Yellow);
					else color_box(x1_P2-33, y1_P2, Yellow);
					left=0;
				}
				
				if(control_up()==3){
					move=move&16777215; //da 1 a 0
					if(control_left()==1) color_box(x1_P2-33, y1_P2-33, Magenta);
					move=move|16777216; // da 0 a 1
					left_up=1;
				}
				else if(control_down()==3){
					move=move&16777215; //da 1 a 0
					if(control_left()==1) color_box(x1_P2-33, y1_P2+33, Magenta);
					move=move|16777216; // da 0 a 1
					left_down=1;
				}
		}
}
void select_right_plus(){
		char player=(move>>24)&1;
		if(player==0){
				if(right==1){
					if(control_right()==2) color_box(x1_P1+66, y1_P1, Yellow);
					else color_box(x1_P1+33, y1_P1, Yellow);
					right=0;
				}else if(down==1){
					if(control_down()==2) color_box(x1_P1, y1_P1+66, Yellow);
					else color_box(x1_P1, y1_P1+33, Yellow);
					down=0;
				}else if(up==1){
					if(control_up()==2) color_box(x1_P1, y1_P1-66, Yellow);
					else color_box(x1_P1, y1_P1-33, Yellow);
					up=0;
				}
				
				if(control_up()==3){
					move=move|16777216; // da 0 a 1
					if(control_right()==1) color_box(x1_P1+33, y1_P1-33, Magenta);
					move=move&16777215; //da 1 a 0
					right_up=1;
				}
				else if(control_down()==3){
					move=move|16777216; // da 0 a 1
					if(control_right()==1) color_box(x1_P1+33, y1_P1+33, Magenta);
					move=move&16777215; //da 1 a 0
					right_down=1;
				}
			
		}else if(player==1){
				if(right==1){
						if(control_right()==2) color_box(x1_P2+66, y1_P2, Yellow);
						else color_box(x1_P2+33, y1_P2, Yellow);
						right=0;
				}else if(down==1){
					if(control_down()==2) color_box(x1_P2, y1_P2+66, Yellow);
					else color_box(x1_P2, y1_P2+33, Yellow);
					down=0;
				}else if(up==1){
					if(control_up()==2) color_box(x1_P2, y1_P2-66, Yellow);
					else color_box(x1_P2, y1_P2-33, Yellow);
					up=0;
				}
				
				if(control_up()==3){
					move=move&16777215; //da 1 a 0
					if(control_right()==1) color_box(x1_P2+33, y1_P2-33, Magenta);
					move=move|16777216; // da 0 a 1
					right_up=1;
				}
				else if(control_down()==3){
					move=move&16777215; //da 1 a 0
					if(control_right()==1) color_box(x1_P2+33, y1_P2+33, Magenta);
					move=move|16777216; // da 0 a 1
					right_down=1;
				}
		}
}
void select_up_plus(){
		char player=(move>>24)&1;
		if(player==0){
				if(right==1){
					if(control_right()==2) color_box(x1_P1+66, y1_P1, Yellow);
					else color_box(x1_P1+33, y1_P1, Yellow);
					right=0;
				}else if(down==1){
					if(control_down()==2) color_box(x1_P1, y1_P1+66, Yellow);
					else color_box(x1_P1, y1_P1+33, Yellow);
					down=0;
				}else if(up==1){
					if(control_up()==2) color_box(x1_P1, y1_P1-66, Yellow);
					else color_box(x1_P1, y1_P1-33, Yellow);
					up=0;
				}
				
				if(control_left()==3){
					move=move|16777216; // da 0 a 1
					if(control_up()==1) color_box(x1_P1-33, y1_P1-33, Magenta);
					move=move&16777215; //da 1 a 0
					up_left=1;
				}
				else if(control_right()==3){
					move=move|16777216; // da 0 a 1
					if(control_up()==1) color_box(x1_P1+33, y1_P1-33, Magenta);
					move=move&16777215; //da 1 a 0
					up_right=1;
				}
			
		}else if(player==1){
				if(right==1){
						if(control_right()==2) color_box(x1_P2+66, y1_P2, Yellow);
						else color_box(x1_P2+33, y1_P2, Yellow);
						right=0;
				}else if(down==1){
					if(control_down()==2) color_box(x1_P2, y1_P2+66, Yellow);
					else color_box(x1_P2, y1_P2+33, Yellow);
					down=0;
				}else if(up==1){
					if(control_up()==2) color_box(x1_P2, y1_P2-66, Yellow);
					else color_box(x1_P2, y1_P2-33, Yellow);
					up=0;
				}
				
				if(control_left()==3){
					move=move&16777215; //da 1 a 0
					if(control_up()==1) color_box(x1_P2-33, y1_P2-33, Magenta);
					move=move|16777216; // da 0 a 1
					up_left=1;
				}
				else if(control_right()==3){
					move=move&16777215; //da 1 a 0
					if(control_up()==1) color_box(x1_P2+33, y1_P2-33, Magenta);
					move=move|16777216; // da 0 a 1
					up_right=1;
				}
		}
}
void select_down_plus(){
		char player=(move>>24)&1;
		if(player==0){
				if(right==1){
					if(control_right()==2) color_box(x1_P1+66, y1_P1, Yellow);
					else color_box(x1_P1+33, y1_P1, Yellow);
					right=0;
				}else if(down==1){
					if(control_down()==2) color_box(x1_P1, y1_P1+66, Yellow);
					else color_box(x1_P1, y1_P1+33, Yellow);
					down=0;
				}else if(up==1){
					if(control_up()==2) color_box(x1_P1, y1_P1-66, Yellow);
					else color_box(x1_P1, y1_P1-33, Yellow);
					up=0;
				}
				
				if(control_right()==3){
					move=move|16777216; // da 0 a 1
					if(control_down()==1) color_box(x1_P1+33, y1_P1+33, Magenta);
					move=move&16777215; //da 1 a 0
					down_right=1;
				}
				else if(control_left()==3){
					move=move|16777216; // da 0 a 1
					if(control_down()==1) color_box(x1_P1-33, y1_P1+33, Magenta);
					move=move&16777215; //da 1 a 0
					down_left=1;
				}
			
		}else if(player==1){
				if(right==1){
						if(control_right()==2) color_box(x1_P2+66, y1_P2, Yellow);
						else color_box(x1_P2+33, y1_P2, Yellow);
						right=0;
				}else if(down==1){
					if(control_down()==2) color_box(x1_P2, y1_P2+66, Yellow);
					else color_box(x1_P2, y1_P2+33, Yellow);
					down=0;
				}else if(up==1){
					if(control_up()==2) color_box(x1_P2, y1_P2-66, Yellow);
					else color_box(x1_P2, y1_P2-33, Yellow);
					up=0;
				}
				
				if(control_right()==3){
					move=move&16777215; //da 1 a 0
					if(control_down()==1) color_box(x1_P2+33, y1_P2+33, Magenta);
					move=move|16777216; // da 0 a 1
					down_right=1;
				}
				else if(control_left()==3){
					move=move&16777215; //da 1 a 0
					if(control_down()==1) color_box(x1_P2-33, y1_P2+33, Magenta);
					move=move|16777216; // da 0 a 1
					down_left=1;
				}
		}
}
void move_direction(){
	show_moves(White);
	if(right==1){
		move_right();
	}else if(left==1){
		move_left();
	}else if(up==1){
		move_up();
	}else if(down==1){
		move_down();
	}else if(up_left==1 || left_up==1){
		move_left_up();
	}else if(up_right==1 || right_up==1){
		move_right_up();
	}else if(down_left==1 || left_down==1){
		move_left_down();
	}else if(down_right==1 || right_down==1){
		move_right_down();
	}
	
	up=0;
	down=0;
	left=0;
	right=0;
	finish_turn();
}

void move_right(){
	char player=(move>>24)&1;
	if(player==0){
		if (control_right()==0){
			return;
		}	
		else if (control_right()==1){
			color_box(x1_P1,y1_P1, White);
			x1_P1=x1_P1+33;
			color_box(x1_P1,y1_P1,Blue2);
		}	
		else if (control_right()==2){
			color_box(x1_P1,y1_P1, White);
			x1_P1=x1_P1+66;
			color_box(x1_P1,y1_P1,Blue2);
		}	
	} 
	else if(player==1) {
		if (control_right()==0){
			return;
		}	
		else if (control_right()==1){
			color_box(x1_P2,y1_P2, White);
			x1_P2=x1_P2+33;
			color_box(x1_P2,y1_P2,Red);
		}	
		else if (control_right()==2){
			color_box(x1_P2,y1_P2, White);
			x1_P2=x1_P2+66;
			color_box(x1_P2,y1_P2,Red);
		}	
	}
	return;
}

void move_left(){
	
	char player=(move>>24)&1;
	if(player==0){
		if (control_left()==0){
			return;
		}	
		else if (control_left()==1){
			color_box(x1_P1,y1_P1, White);
			x1_P1=x1_P1-33;
			color_box(x1_P1,y1_P1, Blue2);
		}	
		else if (control_left()==2){
			color_box(x1_P1,y1_P1, White);
			x1_P1=x1_P1-66;
			color_box(x1_P1,y1_P1, Blue2);
		}	
	
	} 
	else if (player==1){
		if (control_left()==0){
			return;
		}	
		else if (control_left()==1){
			color_box(x1_P2,y1_P2, White);
			x1_P2=x1_P2-33;
			color_box(x1_P2,y1_P2, Red);
		}	
		else if (control_left()==2){
			color_box(x1_P2,y1_P2, White);
			x1_P2=x1_P2-66;
			color_box(x1_P2,y1_P2, Red);
		}	
	}
	return;
}

void move_up(){

	char player=(move>>24)&1;
	if(player==0){
		if (control_up()==0){
			return;
		}	
		else if (control_up()==1){
			color_box(x1_P1,y1_P1, White);
			y1_P1=y1_P1-33;
			color_box(x1_P1,y1_P1, Blue2);
		}	
		else if (control_up()==2){
			color_box(x1_P1,y1_P1, White);
			y1_P1=y1_P1-66;
			color_box(x1_P1,y1_P1, Blue2);
		}	
	} else{
		if (control_up()==0){
			return;
		}	
		else if (control_up()==1){
			color_box(x1_P2,y1_P2, White);
			y1_P2=y1_P2-33;
			color_box(x1_P2,y1_P2, Red);
		}	
		else if (control_up()==2){
			color_box(x1_P2,y1_P2, White);
			y1_P2=y1_P2-66;
			color_box(x1_P2,y1_P2, Red);
		}	
		
		}
}

void move_down(){
	char player=(move>>24)&1;	
	if(player==0){
		if (control_down()==0){
			return;
		}	
		else if (control_down()==1){
			color_box(x1_P1,y1_P1, White);
			y1_P1=y1_P1+33;
			color_box(x1_P1,y1_P1, Blue2);
		}	
		else if (control_down()==2){
			color_box(x1_P1,y1_P1, White);
			y1_P1=y1_P1+66;
			color_box(x1_P1,y1_P1, Blue2);
		}	
	} else{
		if (control_down()==0){
			return;
		}	
		else if (control_down()==1){
			color_box(x1_P2,y1_P2, White);
			y1_P2=y1_P2+33;
			color_box(x1_P2,y1_P2, Red);
		}	
		else if (control_down()==2){
			color_box(x1_P2,y1_P2, White);
			y1_P2=y1_P2+66;
			color_box(x1_P2,y1_P2, Red);
		}	
	}
}

void move_right_up(){
	char player=(move>>24)&1;
	if(player==0){
		if (control_right()==3 || control_up()==3){
			color_box(x1_P1,y1_P1, White);
			x1_P1=x1_P1+33;
			y1_P1=y1_P1-33;
			color_box(x1_P1,y1_P1,Blue2);
			return;
		}		
	} 
	else if(player==1){
		if (control_right()==3 || control_up()==3){
			color_box(x1_P2,y1_P2, White);
			x1_P2=x1_P2+33;
			y1_P2=y1_P2-33;
			color_box(x1_P2,y1_P2,Red);
			return;
		}		
	} 
	return;
}

void move_right_down(){
	char player=(move>>24)&1;
	if(player==0){
		if (control_right()==3 || control_down()==3){
			color_box(x1_P1,y1_P1, White);
			x1_P1=x1_P1+33;
			y1_P1=y1_P1+33;
			color_box(x1_P1,y1_P1,Blue2);
			return;
		}		
	} 
	else if(player==1){
		if (control_right()==3 || control_down()==3){
			color_box(x1_P2,y1_P2, White);
			x1_P2=x1_P2+33;
			y1_P2=y1_P2+33;
			color_box(x1_P2,y1_P2,Red);
			return;
		}		
	} 
	return;
}

void move_left_down(){
	char player=(move>>24)&1;
	if(player==0){
		if (control_left()==3 || control_down()==3){
			color_box(x1_P1,y1_P1, White);
			x1_P1=x1_P1-33;
			y1_P1=y1_P1+33;
			color_box(x1_P1,y1_P1,Blue2);
			return;
		}		
	} 
	else if(player==1){
		if (control_left()==3 || control_down()==3){
			color_box(x1_P2,y1_P2, White);
			x1_P2=x1_P2-33;
			y1_P2=y1_P2+33;
			color_box(x1_P2,y1_P2,Red);
			return;
		}		
	} 
	return;
}

void move_left_up(){
	char player=(move>>24)&1;
	if(player==0){
		if (control_left()==3 || control_up()==3){
			color_box(x1_P1,y1_P1, White);
			x1_P1=x1_P1-33;
			y1_P1=y1_P1-33;
			color_box(x1_P1,y1_P1,Blue2);
			return;
		}		
	} 
	else if(player==1){
		if (control_left()==3 || control_up()==3){
			color_box(x1_P2,y1_P2, White);
			x1_P2=x1_P2-33;
			y1_P2=y1_P2-33;
			color_box(x1_P2,y1_P2,Red);
			return;
		}		
	} 
	return;
}

void place_wall(uint16_t x,uint16_t y, uint16_t color){
	int orientation=move<<12;
	orientation=orientation>>28;  // 0 V, 1 H
	
	if(orientation==0){
		build_wall_v(x,y, color);
	}
	else if(orientation==1){
		build_wall_h(x,y, color);
	}
	return;
}

void break_wall(uint16_t x,uint16_t y){
	int orientation=move<<12;
	orientation=orientation>>28;  // 0 V, 1 H
	
	if(orientation==0){
		delete_wall_v(x,y);
	}
	else if(orientation==1){
		delete_wall_h(x,y);
	}
	return;
}

void rotate_wall_to_horizontal(){
	char x;
	for(x=0; x<17; x++){
		if(walls[x][0]==x_wall+4 || walls[x][0]==x_wall-62)
				if(walls[x][1]==y_wall+29){
					return;
				}
	}
	
	x_wall-=29;
	y_wall+=29;
	move=move|65536; //Setta a 1 il 17esmino bit
}

void rotate_wall_to_vertical(){
	char x;
	for(x=0; x<17; x++){
		if(walls[x][0]==x_wall+29)
				if(walls[x][1]==y_wall+4 || walls[x][1]==y_wall-62){
					return;
				}
	}
	x_wall+=29;
	y_wall-=29;
	move=move & 0xFFFEFFFF;
}

void check_spawn_wall(){
	char x;
	for(x=0; x<17; x++){
		if(walls[x][0]==71  && walls[x][1]==100) build_wall_h(71, 100, Magenta);
		if(walls[x][0]==104 && walls[x][1]==100) build_wall_h(104, 100, Magenta);
		if(walls[x][0]==137 && walls[x][1]==100) build_wall_h(137, 100, Magenta);
		if(walls[x][0]==133 && walls[x][1]==71) build_wall_v(133, 71, Magenta);
		if(walls[x][0]==133 && walls[x][1]==38) build_wall_v(133, 38, Magenta);
		if(walls[x][0]==133 && walls[x][1]==104) build_wall_v(133, 104, Magenta);
	}
	return;
}

char control_wall_right(){
	char x=0;
	int orientation=move<<12;
	orientation=orientation>>28;  // 0 V, 1 H
	
	if(orientation==0) { //è verticale
		for(x=0; x<17; x++){
			if(walls[x][0]==x_wall+4 || walls[x][0]==x_wall+33)
					if(walls[x][1]==y_wall || walls[x][1]==y_wall+33 || walls[x][1]==y_wall-33 || walls[x][1]==y_wall+29){
						return 0;
					}
		}
	}else if(orientation==1){ //orizzontale
			for(x=0; x<17; x++){
			if(walls[x][0]==x_wall+66 || walls[x][0]==x_wall+62)
					if(walls[x][1]==y_wall || walls[x][1]==y_wall-29){
						return 0;
					}
		}
	}
	
	if(x_wall>169){
		return 0;
	}	
	
	//se i controlli vanno bene ritorna 1
	return 1;
}

char control_wall_left(){
	char x=0;
	int orientation=move<<12;
	orientation=orientation>>28;  // 0 V, 1 H
	
	if(orientation==0) { //è verticale
		for(x=0; x<17; x++){
			if(walls[x][0]==x_wall-4 || walls[x][0]==x_wall-33)
					if(walls[x][1]==y_wall || walls[x][1]==y_wall+33 || walls[x][1]==y_wall-33 || walls[x][1]==y_wall+29){
						return 0;
					}
		}
	}else if(orientation==1){ //orizzontale
			for(x=0; x<17; x++){
			if(walls[x][0]==x_wall-66 || walls[x][0]==x_wall-62)
					if(walls[x][1]==y_wall || walls[x][1]==y_wall-29){
						return 0;
					}
		}
	}
	
	if(x_wall<38){
		return 0;
	}	
	
	//se i controlli vanno bene ritorna 1
	return 1;
}

char control_wall_up(){
	char x=0;
	int orientation=move<<12;
	orientation=orientation>>28;  // 0 V, 1 H

	if(orientation==0){//è verticale
		for(x=0; x<17; x++){
			if(walls[x][0]==x_wall || walls[x][0]==x_wall-29){
					if(walls[x][1]==y_wall-66|| walls[x][1]==y_wall-4){
						return 0;
					}
				}
		}
	}else if(orientation==1){//orizzontale
		for(x=0; x<17; x++){
			if(walls[x][0]==x_wall || walls[x][0]==x_wall +33 || walls[x][0]==x_wall-33 || walls[x][0]==x_wall+29){
					if(walls[x][1]==y_wall-33|| walls[x][1]==y_wall-62){
						return 0;
					}
				}
		}
	}
	
	if(y_wall<38){
		return 0;
	}	
	
	//se i controlli vanno bene ritorna 1
	return 1;
}

char control_wall_down(){
	char x=0;
	int orientation=move<<12;
	orientation=orientation>>28;  // 0 V, 1 H

	
	if(orientation==0){//è verticale
		for(x=0; x<17; x++){
			if(walls[x][0]==x_wall || walls[x][0]==x_wall-29){
					if(walls[x][1]==y_wall+66|| walls[x][1]==y_wall+4){
						return 0;
					}
				}
		}
	}else if(orientation==1){//orizzontale
		for(x=0; x<17; x++){
			if(walls[x][0]==x_wall || walls[x][0]==x_wall +33 || walls[x][0]==x_wall-33 || walls[x][0]==x_wall+29){
					if(walls[x][1]==y_wall+33|| walls[x][1]==y_wall+62){
						return 0;
					}
				}
		}
	}
	
	
	if(y_wall>169){
		return 0;
	}	
	
	//se i controlli vanno bene ritorna 1
	return 1;
}

void move_wall_right(){
	if(control_wall_right()==0)return;
	
	break_wall(x_wall, y_wall);
	x_wall=x_wall+33;
	place_wall(x_wall, y_wall, Green);
	
	check_spawn_wall();
}

void move_wall_left(){
	if(control_wall_left()==0)return;
	
	break_wall(x_wall, y_wall);
	x_wall=x_wall-33;
	place_wall(x_wall, y_wall, Green);
	check_spawn_wall();
}

void move_wall_up(){
	if(control_wall_up()==0)return;
	
	break_wall(x_wall, y_wall);
	y_wall=y_wall-33;
	place_wall(x_wall, y_wall, Green);
	check_spawn_wall();
}

void move_wall_down(){
	if(control_wall_down()==0)return;
	
	break_wall(x_wall, y_wall);
	y_wall=y_wall+33;
	place_wall(x_wall, y_wall, Green);
	check_spawn_wall();
}

void perma_wall(){
	char i=0;
	char x;
	char int_str1[20];
	char player=(move>>24)&1;
	int orientation=move<<12;
	orientation=orientation>>28;  // 0 V, 1 H
	
	//controllo che non sono sovrapposto ad un muro a destra o sinistra
	if(orientation==0){//verticale
		for(x=0; x<17; x++){
			if(walls[x][0]==x_wall || walls[x][0]==x_wall-29){
					if(walls[x][1]==y_wall || walls[x][1]==y_wall+33 || walls[x][1]==y_wall-33 || walls[x][1]==y_wall+29){
						return;
					}
				}
		}
	}else if(orientation==1){//orizzontale
		for(x=0; x<17; x++){
			if(walls[x][0]==x_wall || walls[x][0]==x_wall +33 || walls[x][0]==x_wall-33 || walls[x][0]==x_wall+29){
					if(walls[x][1]==y_wall || walls[x][1]==y_wall-29){
						return;
					}
				}
		}
	}
	
	if(trap_check_p1(x1_P1,y1_P1)==0){
			GUI_Text(40, 235, (uint8_t *) "NO WALL ALLOWED HERE", Blue2, White);
			init_timer(0,0x17D7840); 		//1s at 25MHz
			enable_timer(0);
		return;
	}
	if(trap_check_p2(x1_P2,y1_P2)==0){
			GUI_Text(40, 235, (uint8_t *) "NO WALL ALLOWED HERE", Blue2, White);
			init_timer(0,0x17D7840); 		//1s at 25MHz
			enable_timer(0);
		return;
	}
	
	if(player==0){
		n_walls_P1--;
		sprintf(int_str1, "%d", n_walls_P1);
		GUI_Text(42, 280, (uint8_t *) int_str1, Black, White);
	}
	else{
		n_walls_P2--;
		sprintf(int_str1, "%d", n_walls_P2);
		GUI_Text(192, 280, (uint8_t *) int_str1, Black, White);
	}
	place_wall(x_wall, y_wall, Magenta);
	for(i=0; i<17; i++){
			if(walls[i][0]==0){
				walls[i][0]=x_wall;
				walls[i][1]=y_wall;
				break;
			}
	}
	finish_turn();
}



