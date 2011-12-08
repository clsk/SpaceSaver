#ifndef _SCENE
#define _SCENE

#include "keyboard.h"
#include "GraphicManager.h"
#include "Message.h"
#include "Globals.h"

#define kiSTEP_LENGTH 4

/**
*	Estructura para gestionar el funcionamiento de cada escena del juego
**/
typedef struct sScene
{	
	//tamaño de los tile
	int miTILE_SIZE;
	int miBLOCK_SIZE;
	//coordenadas iniciales de la escena
	int miSCENE_Xo;			
	int miSCENE_Yo;
	//dimensiones de la escena
	int miSCENE_WIDTH;
	int miSCENE_HEIGHT;

	//Player del juego	
	TSpecialCell msPlayer;
	//Manipulador de los mensajes del juego
	TMESSAGE	mMessage;

}TSCENE;


//**************FUNCIONES*****************
/**
*	Inicializa la escena del juego, se encarga de inicializar las estructuras y 
*	leer el XML.
**/
bool Scene_Init(TSCENE *,TGRAPHICS *, int);
/**
*	Libera los recursos reservados durante la escena
**/
bool Scene_Deinit(TSCENE *);
/**
*	Actualiza las variables, estruturas, entidades, etc de la escena.
**/
void Scene_Update(TSCENE *, TKEYBOARD *, float);
/**
*	Pinta el estado actual de la escena
**/
void Scene_Render(TSCENE *, TGRAPHICS *);
void Scene_RenderObject(TSCENE *, TGRAPHICS *);
/**
	Control de los frames que representan un movimiento
*/
void Scene_NextFrame(TSCENE *, int);

#endif