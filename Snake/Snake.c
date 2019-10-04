/*
	Application template for Amazfit Bip BipOS
	(C) Maxim Volkov  2019 <Maxim.N.Volkov@ya.ru>
	
	Application template loader for the BipOS
	
*/

#include <libbip.h>
#include <stdlib.h>
#include "Snake.h"

//Velocidad actual del juego
int velocidad = 150;
//Puntos obtenidos
int puntos = 0;
//Posiciones de la serpiente
int serpienteX[100] = {88,87,86,85,84,83,82,81,80,79,72};
int serpienteY[100] = {60,60,60,60,60,60,60,60,60,60,60};
int posicionXCabeza = 88;
int posicionYCabeza = 60;
int tamSerpiente = 11;
//Orientacion de la serpiente:  comienza a la izquierda
int orientacion = 2; //1= subir, -1 bajar, 2 derecha, -2 izquierda
int gira = 0;
int orientacionAnterior = -2;
int posicionXComida = 0;
int posicionYComida = 0;
//Buffer aux

//	screen menu structure - each screen has its own
struct regmenu_ screen_data = {
						55,							//	main screen number, value 0-255, for custom windows it is better to take from 50 and above
						1,							//	auxiliary screen number (usually 1)
						0,							//	0
						dispatch_screen,			//	pointer to the function handling touch, swipe, long press
						key_press_screen, 			//	pointer to the function handling pressing the button
						screen_job,					//	pointer to the callback function of the timer  
						0,							//	0
						show_screen,				//	pointer to the screen display function
						0,							//	
						0							//	long press of the button
					};
int main(int param0, char** argv){	//	here the variable argv is not defined
	show_screen((void*) param0);
}

void show_screen (void *param0){
struct app_data_** 	app_data_p = get_ptr_temp_buf_2(); 	//	pointer to a pointer to screen data
struct app_data_ *	app_data;					//	pointer to screen data

Elf_proc_* proc;

// check the source at the procedure launch
//Esto sirve para regresar al menu de donde viene
if ( (param0 == *app_data_p) && get_var_menu_overlay()){ // return from the overlay screen (incoming call, notification, alarm, target, etc.)

	app_data = *app_data_p;					//	the data pointer must be saved for the deletion 
											//	release memory function reg_menu
	*app_data_p = NULL;						//	reset the pointer to pass it to the function reg_menu		

	// 	create a new screen when the pointer temp_buf_2 is equal to 0 and the memory is not released		
	reg_menu(&screen_data, 0); 				// 	menu_overlay=0
	
	*app_data_p = app_data;						//	restore the data pointer after the reg_menu function
	
	//   here we perform actions when returning from the overlay screen: restore data, etc.
	
	
} else { // if the function is started for the first time i.e. from the menu 

	// create a screen (register in the system) 
	reg_menu(&screen_data, 0);

	// allocate the necessary memory and place the data in it (the memory by the pointer stored at temp_buf_2 is released automatically by the function reg_menu of another screen)
	*app_data_p = (struct app_data_ *)pvPortMalloc(sizeof(struct app_data_));
	app_data = *app_data_p;		//	data pointer
	
	// clear the memory for data
	_memclr(app_data, sizeof(struct app_data_));
	
	//	param0 value contains a pointer to the data of the running process structure Elf_proc_
	proc = param0;
	
	// remember the address of the pointer to the function you need to return to after finishing this screen
	if ( param0 && proc->ret_f ) 			//	if the return pointer is passed, then return to it
		app_data->ret_f = proc->elf_finish;
	else					//	if not, to the watchface
		app_data->ret_f = show_watchface;
	
	// here we perform actions that are necessary if the function is launched for the first time from the menu: filling all data structures, etc.
	
	app_data->col=0;
	
}

// here we do the interface drawing, there is no need to update (move to video memory) the screen

//draw_screen(app_data->col);

//Inicializa todo:
inicializar();

// if necessary, set the call timer screen_job in ms
//Timer para actualizar
set_update_period(1, velocidad);
}

void key_press_screen(){
struct app_data_** 	app_data_p = get_ptr_temp_buf_2(); 	//	pointer to a pointer to screen data 
struct app_data_ *	app_data = *app_data_p;				//	pointer to screen data

// call the return function (usually this is the start menu), specify the address of the function of our application as a parameter
show_menu_animate(app_data->ret_f, (unsigned int)show_screen, ANIMATE_RIGHT);	
};
void screen_job(){
// if necessary, you can use the screen data in this function
struct app_data_** 	app_data_p = get_ptr_temp_buf_2(); 	//	pointer to pointer to screen data  
struct app_data_ *	app_data = *app_data_p;				//	pointer to screen data


//Refresca la pantalla:
refrescar_juego();

// if necessary, set the screen_job call timer again
set_update_period(1, velocidad);

}

int dispatch_screen (void *param){
struct app_data_** 	app_data_p = get_ptr_temp_buf_2(); 	//	pointer to a pointer to screen data 
struct app_data_ *	app_data = *app_data_p;				//	pointer to screen data

// in case of rendering the interface, update (transfer to video memory) the screen

struct gesture_ *gest = param;
int result = 0;

switch (gest->gesture){
	case GESTURE_CLICK: {		
//Click en izquieda	
		if ( ( gest->touch_pos_y >128) &&  ( gest->touch_pos_y < 168) && ( gest->touch_pos_x >90) &&  ( gest->touch_pos_x < 130)){ 
	
					// touchscreen center
					// Perform the actions
					vibrate(1,70,0);
					//app_data->col = (app_data->col+1)%COLORS_COUNT;
					//draw_screen(app_data->col);
					//repaint_screen_lines(0, 176);
						if(orientacion != 2){
							orientacionAnterior = orientacion;
							orientacion =-2;
							gira = 1;
						}
			}else if (( gest->touch_pos_y >118) &&  ( gest->touch_pos_y < 158) && (gest->touch_pos_x >110) &&  ( gest->touch_pos_x < 150) ){ //Arriba
				vibrate(1,70,0);
					//app_data->col = (app_data->col+1)%COLORS_COUNT;
					//draw_screen(app_data->col);
					//repaint_screen_lines(0, 176);
						if(orientacion != -1){
							orientacionAnterior = orientacion;
							orientacion =1;
							gira = 1;
						}
			}else if (( gest->touch_pos_y >128) &&  ( gest->touch_pos_y < 168) && (gest->touch_pos_x >120) &&  ( gest->touch_pos_x < 170) ){//Derecha
				vibrate(1,70,0);
					//app_data->col = (app_data->col+1)%COLORS_COUNT;
					//draw_screen(app_data->col);
					//repaint_screen_lines(0, 176);
						if(orientacion != -2){
						orientacionAnterior = orientacion;
						orientacion =2;
						gira = 1;
					}
			}else if (( gest->touch_pos_y >128) &&  ( gest->touch_pos_y < 178) && (gest->touch_pos_x >110) &&  ( gest->touch_pos_x < 150) ){//Abajo
				vibrate(1,70,0);
					//app_data->col = (app_data->col+1)%COLORS_COUNT;
					//draw_screen(app_data->col);
					//repaint_screen_lines(0, 176);
						if(orientacion != 1){
							orientacionAnterior = orientacion;
							orientacion =-1;
							gira = 1;
						}
			}
			break;
		};
		case GESTURE_SWIPE_RIGHT: {	//	swipe to the right
			if(orientacion != -2){
				orientacionAnterior = orientacion;
				orientacion =2;
				gira = 1;
			}
			break;
		};
		case GESTURE_SWIPE_LEFT: {	// swipe to the left
			if(orientacion != 2){
				orientacionAnterior = orientacion;
				orientacion =-2;
				gira = 1;
			}
			break;
		};
		case GESTURE_SWIPE_UP: {	// swipe up
			if(orientacion != -1){
				orientacionAnterior = orientacion;
				orientacion =1;
				gira = 1;
			}
			break;
		};
		case GESTURE_SWIPE_DOWN: {	// swipe down
			if(orientacion != 1){
				orientacionAnterior = orientacion;
				orientacion =-1;
				gira = 1;
			}
			break;
		};		
		default:{	// something went wrong ...
			
			break;
		};		
		
	}
	return result;
};

//Crear el fondo de color blanco:

void inicializar(){
	//Color del font
	load_font();
	set_fg_color(COLOR_BLACK);
	
	crearCoordenadasFruta();
	//Pinta serpiente
	/*for(int i=0;i<tamSerpiente;i++){
		draw_horizontal_line(serpienteY[i] , serpienteX[i], serpienteX[i]);
	}*/
	refrescar_juego();
	
};

// custom function
void refrescar_juego(){
//Refresca el fondo de pantalla
set_bg_color(COLOR_WHITE);
fill_screen_bg();
set_graph_callback_to_ram_1();

//Numero aleatorio (no funciona):
//int numero = rand() % 11; 
//Concatena numero y cadena de texto

//Muestra por pantalla la puntuacion
char puntosPantalla[15];

_sprintf(puntosPantalla, "Puntos %i",puntos);
text_out_center(puntosPantalla, 120, 0);


//Dibuja la serpiente en su totalidad
for(int i=tamSerpiente-1;i>0;i--){
	/*if(gira == 0){
		if(orientacion == 1){//Sube
			posicionCuerpoX = posicionCuerpoXAnterior;
			posicionCuerpoY = posicionCuerpoYAnterior-1;
		}else if(orientacion == -1){//Baja
			posicionCuerpoX = posicionCuerpoXAnterior;
			posicionCuerpoY = posicionCuerpoYAnterior+1;
		}else if(orientacion == 2){//Derecha
			posicionCuerpoX = posicionCuerpoXAnterior + 1;
			posicionCuerpoY = posicionCuerpoYAnterior;
		}else if(orientacion == -2){//Izquierda
			posicionCuerpoX = posicionCuerpoXAnterior - 1;
			posicionCuerpoY = posicionCuerpoYAnterior;
		}
	}else if(gira == 1){
			if(orientacionAnterior == 1){//Sube
			posicionCuerpoX = posicionCuerpoXAnterior;
			posicionCuerpoY = posicionCuerpoYAnterior-1;
		}else if(orientacionAnterior == -1){//Baja
			posicionCuerpoX = posicionCuerpoXAnterior;
			posicionCuerpoY = posicionCuerpoYAnterior+1;
		}else if(orientacionAnterior == 2){//Derecha
			posicionCuerpoX = posicionCuerpoXAnterior + 1;
			posicionCuerpoY = posicionCuerpoYAnterior;
		}else if(orientacionAnterior == -2){//Izquierda
			posicionCuerpoX = posicionCuerpoXAnterior - 1;
			posicionCuerpoY = posicionCuerpoYAnterior;
		}
	}*/
	serpienteY[i]  = serpienteY[i-1];
	serpienteX[i]  = serpienteX[i-1];
	//draw_horizontal_line(serpienteY[i] , serpienteX[i], serpienteX[i]);
	draw_rect(serpienteX[i], serpienteY[i], serpienteX[i]+2, serpienteY[i]+2); 
	//show_res_by_id(1313,posicionCuerpoX, posicionCuerpoY);  
	//Resetea a posicion:
	
}

//Mueve solo la cabeza
if(orientacion == 1){//Sube
	serpienteY[0] = serpienteY[0]-1;
}else if(orientacion == -1){//Baja
	serpienteY[0] = serpienteY[0]+1;
}else if(orientacion == 2){//Derecha
	serpienteX[0] = serpienteX[0]+1;
}else if(orientacion == -2){//Izquierda
	serpienteX[0] = serpienteX[0]-1;
}

//draw_horizontal_line(serpienteY[0], serpienteX[0], serpienteX[0]);
draw_rect(serpienteX[0], serpienteY[0], serpienteX[0]+2, serpienteY[0]+2); 

detectarColision();


//show_res_by_id(1313,posicionXCabeza, posicionYCabeza);  

//text_out_center(".", posicionXCabeza, posicionYCabeza);
crearFruta();
pintarCruceta();
//text_out_center(snake, posX, posY);
//Pinta la comida dentro de la pantalla:

//text_out_center(buffer, posX, posY);
repaint_screen_lines(0, 176);

};

void pintarCruceta(){
	//POS X AND POS Y
	text_out_center("L", 110, 148);
	text_out_center("R", 150, 148);
	//show_res_by_id(ARROW_UP,130, 138); 
	text_out_center("U", 130, 138);
	//show_res_by_id(ARROW_DOWN,130, 158); 
	text_out_center("D", 130, 158);
};

void crearFruta(){
	draw_rect(posicionXComida, posicionYComida, posicionXComida+3, posicionYComida+3); 
	//text_out_center("#", posicionXComida, posicionYComida);
};

void crearCoordenadasFruta(){
	 posicionXComida = get_tick_count() % 170;
	 posicionYComida = (get_tick_count()+5) % 170;
}

void detectarColision(){
	if(serpienteX[0] == posicionXComida && serpienteY[0] == posicionYComida
	||serpienteX[0]-1 == posicionXComida && serpienteY[0]-1 == posicionYComida
	||serpienteX[0]+1 == posicionXComida && serpienteY[0]+1 == posicionYComida
	||serpienteX[0] == posicionXComida+1 && serpienteY[0] == posicionYComida+1
	||serpienteX[0] == posicionXComida+1 && serpienteY[0] == posicionYComida-1
	||serpienteX[0] == posicionXComida-1 && serpienteY[0] == posicionYComida+1
	||serpienteX[0]-1 == posicionXComida+1 && serpienteY[0]-1 == posicionYComida+1
	||serpienteX[0]+1 == posicionXComida+1 && serpienteY[0]+1 == posicionYComida-1
	||serpienteX[0]-1 == posicionXComida && serpienteY[0]-1 == posicionYComida+1
	||serpienteX[0]+1 == posicionXComida+1 && serpienteY[0]+1 == posicionYComida){
		tamSerpiente++;
		velocidad = velocidad -5;
		crearCoordenadasFruta();
		
	}
	
}
