/*
	Application template for Amazfit Bip BipOS
	(C) Maxim Volkov  2019 <Maxim.N.Volkov@ya.ru>
	
	Application template, header file

*/

#ifndef __APP_TEMPLATE_H__
#define __APP_TEMPLATE_H__

#define COLORS_COUNT	4
#define MAX_VERTICAL	175
#define MAX_HORIZONTAL	150
#define MIN_VERTICAL	2
#define MIN_HORIZONTAL	2
// the data structure for our screen
struct app_data_ {
			void* 	ret_f;					//	the address of the return function
			int		col;					//	the current color of the font
};

// template.c
void 	show_screen (void *return_screen);
void 	key_press_screen();
int 	dispatch_screen (void *param);
void 	inicializar();
void 	screen_job();
void    pinta_datos();
void	refrescar_juego();
void	pintarCruceta();
void	crearFruta();
void    crearCoordenadasFruta();
void    detectarColision();
//void    dibujar();
//void    pinta_datos();
#endif