#ifndef _GAME
#define _GAME

#include "keyboard.h"
#include "GraphicManager.h"
#include "Scene.h"



/**
*	SE ENCARGA DE CONTROLAR EL JUEGO EN SU NIVEL MAS ALTO JERARQUICAMENTE
**/
//Indica el tiempo máximo a esperar entre los updates
const float kfTimeLimit=0.1f; 
//Indica el nivel inicial del juego
const int kiFIRST_LEVEL=1;

//**************ESTRUCTURAS***************
/**
*	Define los elementos que componen un juego y las variables de control
**/
typedef struct sGAME_
{
	float			mfAcumulatedTime;	//variable utilizada para controlar la velocidad
	bool			mbFinish;			//indica si el juego a o no terminado
	
	TKEYBOARD		mKeyboard;			//manipulación de la entrada por teclado
	TGRAPHICS       mGraphic;			//manipulación de los gráficos

	TSCENE			mScene;				//controla el gameplay	
}TGAME;


//**************FUNCIONES*****************
/**
*	Inicializa todos los componentes del juego y reserva la memoria necesaria
*	1-Inicializa el la entrada por teclado
**/
void Game_Init(TGAME *);
/**
*	Libera los recursos reservados durante el juego
**/
void Game_Deinit(TGAME *);
/**
*	Actualiza los elementos que componen el juego y las variables auxiliares
**/
void Game_Update(TGAME *, float);
/**
*	Pinta el estado actual del juego
**/
void Game_Render(TGAME *);
/**
*	Determina si el juego ha terminado o no
**/
bool Game_HasFinish(TGAME *);

//**********************************************************
/*
* Actualizar la entrada de teclado 
*/
void Game_ReadKeyboard(TGAME *, char , bool);

#endif