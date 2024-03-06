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
#include "../GLCD/GLCD.h" 
#include "joystick.h"
#include "../timer/timer.h"
#include <string.h>
#include <time.h>
#include <stdlib.h>

extern unsigned int move;
extern uint16_t x1_P1;
extern uint16_t y1_P1;
extern uint16_t x1_P2;
extern uint16_t y1_P2;
extern uint16_t x_wall;
extern uint16_t y_wall;
int walle[17][2];
extern char left_up;
extern char left_down;
extern char right_up;
extern char right_down;
extern char up_left;
extern char up_right;
extern char down_left;
extern char down_right; 
extern char right;
extern char left;
extern char down;
extern char up;
extern char npc;
char num_movement;
int orientation;

void plus_condition(void){
	char player=(move>>24)&1;
	if(player==0){
		if(left_up==1){
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
			 color_box(x1_P1+33, y1_P1-33, Yellow);
			up_right=0;
		}else if(up_left==1){
			 color_box(x1_P1-33, y1_P1-33, Yellow);
			up_left=0;
		}else if(down_right==1){
			 color_box(x1_P1+33, y1_P1+33, Yellow);
			down_right=0;
		}else if(down_left==1){
			 color_box(x1_P1-33, y1_P1+33, Yellow);
			down_left=0;
		}
	}
	else if(player==1){
		if(left_up==1){
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
			 color_box(x1_P2+33, y1_P2-33, Yellow);
			up_right=0;
		}else if(up_left==1){
			 color_box(x1_P2-33, y1_P2-33, Yellow);
			up_left=0;
		}else if(down_right==1){
			 color_box(x1_P2+33, y1_P2+33, Yellow);
			down_right=0;
		}else if(down_left==1){
			 color_box(x1_P2-33, y1_P2+33, Yellow);
			down_left=0;
		}
	}
}




int random_number(){
	int val_int;
		disable_timer(1);
		val_int= LPC_TIM1 -> TC; 
		enable_timer(1);
		return val_int;
}

int choose_npc_move(){
	char flag;
	int valore;
	flag=1;
	while(flag){
		valore=random_number();
		//valore=4;
		switch(valore % 6){
			case 0:
				if(control_right()==0) continue;
				else {
					right=1;
					npc=0;
					move_direction();
					flag=0;
					return 1;
				}
			case 1:
				if(control_left()==0) continue;
				else {
					left=1;
					npc=0;
					move_direction();
					flag=0;
					return 1;
				}
			case 2:
				if(control_up()==0) continue;
				else {
					up=1;
					npc=0;
					move_direction();
					flag=0;
					return 1;
				}
			case 3: 
				if(control_down()==0) continue;
				else {
					down=1;
					npc=0;
					move_direction();
					flag=0;
					return 1;
				}
			case 4: 
				valore=random_number();
				switch(valore % 4){
					case 0:
						if(control_left()==3 || control_up()==3) continue;
						else {
							left_up=1;
							npc=0;
							move_direction();
							flag=0;
							return 1;
						}
					case 1:
						if(control_right()==3 || control_up()==3) continue;
						else {
							right_up=1;
							npc=0;
							move_direction();
							flag=0;
							return 1;
						}
					case 2:
						if(control_left()==3 || control_down()==3) continue;
						else {
							left_down=1;
							npc=0;
							move_direction();
							flag=0;
						}
						return 1;
					case 3:
						if(control_right()==3 || control_down()==3) continue;
						else {
							right_down=1;
							npc=0;
							move_direction();
							flag=0;
							return 1;
						}
					default: return 1;
				}
				
			case 5: 
				//MUOVI MURO
				num_movement=valore%10+1;
				x_wall=104;
				y_wall=100;
				move=move|65536; //Setta a 1 il 17esmino bit
				place_wall(x_wall,y_wall, Green);
				while(num_movement!=0){
					valore=random_number();
					switch(valore%5){
						case 0:
							move_wall_left();
							num_movement--;
							break;
						case 1:
							move_wall_right();
							num_movement--;
							break;
						case 2:
							move_wall_up();
							num_movement--;
							break;
						case 3:
							move_wall_down();
							num_movement--;
							break;
						case 4:
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
							num_movement--;
							break;
						default: break;
					}
				}
				perma_wall();
				flag=0;
				return 1;
			default: break;
		}
	}
	return 1;
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
			wall_e[e][f]=walle[e][f];
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
			wall_e[e][f]=walle[e][f];
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



