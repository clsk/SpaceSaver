#ifndef _MESSAGE_H
#define _MESSAGE_H


#include "GraphicManager.h"

//***************CONSTANTES***************
const float kfDelay=0.7f;	//tiempo máximo que durará en el mensaje mostrado
/**
*	Estructura para gestionar los mensajes del juego
**/
typedef struct sMessage
{
	char	macText[200];	//texto del mensaje
	int		miX;			//coordenada X donde se va a mostrar
	int		miY;			//coordenada Y donde se va a mostrar    
	float	mfDelay;		//contador del tiempo que se va a mostrar
	bool	mbShow;			//indica si de debe mostrar  o no
}TMESSAGE;
//**************FUNCIONES*****************
/**
*	Se encarga de inicializar el mensaje
**/
void Message_Init	(TMESSAGE *, int,int, char *);
/**
*	Liberar los recursos que se reservan en el Init
**/
void Message_Deinit	(TMESSAGE *);
/**
	Actualizar el estado del mensaje, tener el cuenta el tiempo que será mostrado
*/
void Message_Update	(TMESSAGE *,float);
/**
	Visualizar el mensaje 
*/
void Message_Render(TMESSAGE *, TGRAPHICS *);  

#endif