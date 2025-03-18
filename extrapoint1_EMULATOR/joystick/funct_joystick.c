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
#include "../led/led.h"
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
						return 0;
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
								return 0;
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
						return 0;
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
							return 0;
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
						return 0;
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
						return 0;
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
						return 0;
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
						return 0;
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
		else{
				//colora box a destra
				color_box(x1_P1+33, y1_P1, Color);
		}
		if(control_left()==0);
		else if(control_left()==2){
			//colora box a 2 sinistra
			color_box(x1_P1-66, y1_P1, Color);
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
		else{
				//colora box sopra
				color_box(x1_P1, y1_P1-33, Color);
			}
			
		if(control_down()==0);
		else if(control_down()==2){
			//colora box a 2 down
			color_box(x1_P1, y1_P1+66, Color);
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
		else{
				//colora box a destra
				color_box(x1_P2+33, y1_P2, Color);
		}
		
		if(control_left()==0);
		else if(control_left()==2){
			//colora box a 2 sinistra
			color_box(x1_P2-66, y1_P2, Color);
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
		else{
				//colora box sopra
				color_box(x1_P2, y1_P2-33, Color);
			}
			
		if(control_down()==0);
		else if(control_down()==2){
			//colora box a 2 down
			color_box(x1_P2, y1_P2+66, Color);
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
			GUI_Text(40, 235, (uint8_t *) "NO WALL ALLOWED ", Blue2, White);
			init_timer(0,0x17D7840); 		//1s at 25MHz
			enable_timer(0);
		return;
	}
	if(trap_check_p2(x1_P2,y1_P2)==0){
			GUI_Text(40, 235, (uint8_t *) "NO WALL ALLOWED ", Blue2, White);
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
				x_wall=104;
				y_wall=100;
				break;
			}
	}
	finish_turn();
}

char token_path_right(uint16_t x,uint16_t y,int wall_e[17][2]){
	char i;
	//char player=(move>>24)&1;
	
		if(x>200){
			return 3;
		}
		//muro
		for(i=0; i<17; i++){
			if(wall_e[i][0]==x+28){
					if(wall_e[i][1]==y-34 || wall_e[i][1]==y-1){
						return 0;
					}
				}
		}
		// se non c'è niente returna 1
		//color_box(x,y,Blue2);
		//color_box(x,y,White);
		return 1;		
} 

char token_path_left(uint16_t x,uint16_t y,int wall_e[17][2]){
	char i;
//	char player=(move>>24)&1;
	
		if(x<10){
			return 3;
		}
		//muro
		for(i=0; i<17; i++){
			if(wall_e[i][0]==x-5){
					if(wall_e[i][1]==y-34 || wall_e[i][1]==y-1){
						return 0;
					}
				}
		}
		// se non c'è niente returna 1
		//color_box(x,y,Blue2);
		//color_box(x,y,White);
		return 1;	
	
}

char token_path_up(uint16_t x,uint16_t y,int wall_e[17][2]){
	char i;
	//char player=(move>>24)&1;
	
		if(y<10){
			return 3;
		}
		//muro
		for(i=0; i<17; i++){
			if(wall_e[i][0]==x-34 || wall_e[i][0]==x-1){
					if(wall_e[i][1]==y-5){
						return 0;
					}
				}
		}
		// se non c'è niente returna 1
		//color_box(x,y,Blue2);
		//color_box(x,y,White);
		return 1;			
	}


char token_path_down(uint16_t x,uint16_t y,int wall_e[17][2]){
	char i;
	//char player=(move>>24)&1;

		if(y>200){
			return 3; //sotto non è possibile
		}
		//muro
		for(i=0; i<17; i++){
			if(wall_e[i][0]==x-34 || wall_e[i][0]==x-1){
					if(wall_e[i][1]==y+28){
						return 0;
					}
				}
		}
		// se non c'è niente returna 1
		//color_box(x,y,Blue2);
		//color_box(x,y,White);
		return 1;	
}

 
	
char trap_check_p1(uint16_t x_start,uint16_t y_start){
	uint16_t x= x_start;
	uint16_t y= y_start;
	uint16_t x_wall_right=220;
	uint16_t x_wall_left=10;
	char a=0;
	char b=0;
	char c=0;
	char w=0;
	char left=0;
	char right=1;
	char up=1;
	int i=0;
	int e=0;
	int f=0;
	int wall_e[17][2];
	
	for(e=0;e<17;e++){
		for(f=0;f<2;f++){
			wall_e[e][f]=walls[e][f];
		}
	}
	
	for(i=0; i<17; i++){
			if(wall_e[i][0]==0){
				wall_e[i][0]=x_wall;
				wall_e[i][1]=y_wall;
				break;
			}
	}
	for(i=0;i<1000;i++){
		/*if(i>0 && x_start==x && y_start==y ){
			//sono in trappola
			return 0;
		}	*/
		if(up==1){
			a=token_path_up(x,y,wall_e);
			if(a==1){
				y-=33;
				continue;
			}
			else if(a==3){
				//condizione di vittoria
				return 1;
			}
			else if(a==0){
				if(left==0 && right==1){
					b=token_path_right(x,y,wall_e);
					if(b==1){
						x+=33;
						if(x>x_wall_right) {
							up=1;
							left=0;
							right=1;							
							continue;
						}
						continue;
					}
					if(b==0 || b==3){
						if(b==0){
							if(x+32>x_wall_right){
								x_wall_right=0;
								x_wall_right=x+32;
							}
						}
						if(b==3){
							x_wall_right=0;
						}				
						
						left=1;
						right=0;
						c=token_path_left(x,y,wall_e);
						if(c==1){
							x-=33;
							if(x<x_wall_left) {
								up=1;
								left=0;
								right=1;
								continue;
							}
							continue;
						}
						else if(c==3 || c==0){ 
								if(c==0){
									if(x-32<x_wall_left){
										x_wall_left=240;
										x_wall_left=x-32;
									}
								}
								if(c==3){
									x_wall_left=240;
								}	
								up=0;
							
						}
					}
				}
				if(left==1 && right==0){
					c=token_path_left(x,y,wall_e);
					if(c==1){
						x-=33;
						if(x<x_wall_left) {
								up=1;
								left=0;
								right=1;
								continue;
						}
						continue;
					}
					else if(c==0 || c==3){
						if(c==0){
							if(x-32<x_wall_left){
								x_wall_left=240;
								x_wall_left=x-32;
							}
						}
						if(c==3){
							x_wall_left=240;
						}	
						up=0;
						left=0;
						right=1;
						continue;
					}
				}
			}
		}
		else if(up==0){
			w= token_path_down(x,y,wall_e);
			if(w==1){
				y+=33;
				if(left==0 && right==1){
					b=token_path_right(x,y,wall_e);
					if(b==1){
						x+=33;
						if(x>x_wall_right) {
							up=1;
							left=0;
							right=1;
							continue;
						}
						continue;
					}	
					if(b==0 || b==3){
						if(b==0){
							if(x+32>x_wall_right){
								x_wall_right=0;
								x_wall_right=x+32;
							}
						}
						if(b==3){
							x_wall_right=0;
						}	
						left=1;
						right=0;
						c=token_path_left(x,y,wall_e);
						if(c==1){
							x-=33;
							if(x<x_wall_left) {
								up=1;
								left=0;
								right=1;
								continue;
							}
							continue;
						}
						else{
							if(c==0){
								if(x-32<x_wall_left){
									x_wall_left=240;
									x_wall_left=x-32;
								}
							}
						if(c==3){
							x_wall_left=240;
						}	
							left=0;
							right=1;
							continue;
						}
					}
				}
				if(left==1 && right==0){
					c=token_path_left(x,y,wall_e);
					if(c==1){
							x-=33;
							if(x<x_wall_left) {
								up=1;
								left=0;
								right=1;
								continue;
							}
					}
					else if(c==0 || c==3){
						if(c==0){
							if(x-32<x_wall_left){
								x_wall_left=240;
								x_wall_left=x-32;
							}
						}
						if(c==3){
							x_wall_left=240;
						}	
						left=0;
						right=1;
						continue;
					}
				}
			}
			if(w==0 || w==3){
				if(left==0 && right==1){
					b=token_path_right(x,y,wall_e);
					if(b==1){
						x+=33;
						up=1;
						left=0;
						right=1;
						if(x>x_wall_right) {
							up=1;
							left=0;
							right=1;
							continue;
						}
						continue;
					}	
					if(b==0 || b==3){
						if(b==0){
							if(x+32>x_wall_right){
								x_wall_right=0;
								x_wall_right=x+32;
							}
						}
						if(b==3){
							x_wall_right=0;
						}	
						left=1;
						right=0;
						c=token_path_left(x,y,wall_e);
						if(c==1){
							x-=33;
							if(x<x_wall_left) {
								up=1;
								left=0;
								right=1;
								continue;
							}
							continue;
						}else if(c==0 || c==3){
							//condizione sono intrappolato
							return 0;
						}
					}
				}
				if(left==1 && right==0){
					c=token_path_left(x,y,wall_e);
					if(c==1){
						x-=33;
						if(x<x_wall_left) {
							up=1;
							left=0;
							right=1;
							left=0;
							right=1;
							continue;
						}
						continue;
					}
					else if(c==0 || c==3){
						up=1;
						left=0;
						right=1;
						continue;
					}
				}
			}
		}
	}
	return 0;
}
char trap_check_p2(uint16_t x_start,uint16_t y_start){
	uint16_t x= x_start;
	uint16_t y= y_start;
	uint16_t x_wall_right=220;
	uint16_t x_wall_left=10;
	char a=0;
	char b=0;
	char c=0;
	char w=0;
	char left=0;
	char right=1;
	char down=1;
	int i=0;
	int e=0;
	int f=0;
	int wall_e[17][2];
	
	for(e=0;e<17;e++){
		for(f=0;f<2;f++){
			wall_e[e][f]=walls[e][f];
		}
	}
	
	for(i=0; i<17; i++){
			if(wall_e[i][0]==0){
				wall_e[i][0]=x_wall;
				wall_e[i][1]=y_wall;
				break;
			}
	}
	for(i=0;i<1000;i++){
		/*if(i>0 && x_start==x && y_start==y ){
			//sono in trappola
			return 0;
		}	*/
		if(down==1){
			a=token_path_down(x,y,wall_e);
			if(a==1){
				y+=33;
				continue;
			}
			else if(a==3){
				//condizione di vittoria
				return 1;
			}
			else if(a==0){
				if(left==0 && right==1){
					b=token_path_right(x,y,wall_e);
					if(b==1){
						x+=33;
						if(x>x_wall_right) {
							down=1;
							left=0;
							right=1;							
							continue;
						}
						continue;
					}
					if(b==0 || b==3){
						if(b==0){
							if(x+32>x_wall_right){
								x_wall_right=0;
								x_wall_right=x+32;
							}
						}
						if(b==3){
							x_wall_right=0;
						}				
						
						left=1;
						right=0;
						c=token_path_left(x,y,wall_e);
						if(c==1){
							x-=33;
							if(x<x_wall_left) {
								down=1;
								left=0;
								right=1;
								continue;
							}
							continue;
						}
						else if(c==3 || c==0){ 
								if(c==0){
									if(x-32<x_wall_left){
										x_wall_left=240;
										x_wall_left=x-32;
									}
								}
								if(c==3){
									x_wall_left=240;
								}	
								down=0;
							
						}
					}
				}
				if(left==1 && right==0){
					c=token_path_left(x,y,wall_e);
					if(c==1){
						x-=33;
						if(x<x_wall_left) {
								down=1;
								left=0;
								right=1;
								continue;
						}
						continue;
					}
					else if(c==0 || c==3){
						if(c==0){
							if(x-32<x_wall_left){
								x_wall_left=240;
								x_wall_left=x-32;
							}
						}
						if(c==3){
							x_wall_left=240;
						}	
						down=0;
						left=0;
						right=1;
						continue;
					}
				}
			}
		}
		else if(down==0){
			w= token_path_up(x,y,wall_e);
			if(w==1){
				y+=33;
				if(left==0 && right==1){
					b=token_path_right(x,y,wall_e);
					if(b==1){
						x+=33;
						if(x>x_wall_right) {
							down=1;
							left=0;
							right=1;
							continue;
						}
						continue;
					}	
					if(b==0 || b==3){
						if(b==0){
							if(x+32>x_wall_right){
								x_wall_right=0;
								x_wall_right=x+32;
							}
						}
						if(b==3){
							x_wall_right=0;
						}	
						left=1;
						right=0;
						c=token_path_left(x,y,wall_e);
						if(c==1){
							x-=33;
							if(x<x_wall_left) {
								down=1;
								left=0;
								right=1;
								continue;
							}
							continue;
						}
						else{
							if(c==0){
								if(x-32<x_wall_left){
									x_wall_left=240;
									x_wall_left=x-32;
								}
							}
						if(c==3){
							x_wall_left=240;
						}	
							left=0;
							right=1;
							continue;
						}
					}
				}
				if(left==1 && right==0){
					c=token_path_left(x,y,wall_e);
					if(c==1){
							x-=33;
							if(x<x_wall_left) {
								down=1;
								left=0;
								right=1;
								continue;
							}
					}
					else if(c==0 || c==3){
						if(c==0){
							if(x-32<x_wall_left){
								x_wall_left=240;
								x_wall_left=x-32;
							}
						}
						if(c==3){
							x_wall_left=240;
						}	
						left=0;
						right=1;
						continue;
					}
				}
			}
			if(w==0 || w==3){
				if(left==0 && right==1){
					b=token_path_right(x,y,wall_e);
					if(b==1){
						x+=33;
						down=1;
						left=0;
						right=1;
						if(x>x_wall_right) {
							down=1;
							left=0;
							right=1;
							continue;
						}
						continue;
					}	
					if(b==0 || b==3){
						if(b==0){
							if(x+32>x_wall_right){
								x_wall_right=0;
								x_wall_right=x+32;
							}
						}
						if(b==3){
							x_wall_right=0;
						}	
						left=1;
						right=0;
						c=token_path_left(x,y,wall_e);
						if(c==1){
							x-=33;
							if(x<x_wall_left) {
								down=1;
								left=0;
								right=1;
								continue;
							}
							continue;
						}else if(c==0 || c==3){
							//condizione sono intrappolato
							return 0;
						}
					}
				}
				if(left==1 && right==0){
					c=token_path_left(x,y,wall_e);
					if(c==1){
						x-=33;
						if(x<x_wall_left) {
							down=1;
							left=0;
							right=1;
							left=0;
							right=1;
							continue;
						}
						continue;
					}
					else if(c==0 || c==3){
						down=1;
						left=0;
						right=1;
						continue;
					}
				}
			}
		}
	}
	return 0;
}


