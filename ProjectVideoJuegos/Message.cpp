#include "stdafx.h"
#include "message.h"

//**************FUNCIONES*****************
/**
*	Se encarga de inicializar el mensaje
**/
void Message_Init	(TMESSAGE * lsMessage, int liX, int liY, char * lacText)
{
	//inicializando la posición y la información a mostrar
    lsMessage->miX=liX; 
    lsMessage->miY=liY; 
    strcpy(lsMessage->macText,lacText); 
	//iniciando el contador del tiempo en cero
    lsMessage->mfDelay=0.0f;
	//permitir que el mensaje sea mostrado
    lsMessage->mbShow=true;  
}
/**
*	Liberar los recursos que se reservan en el Init
**/
void Message_Deinit	(TMESSAGE * lsMessage)
{

}
/**
	Actualizar el estado del mensaje, tener el cuenta el tiempo que será mostrado
*/
void Message_Update	(TMESSAGE * lsMessage, float lfTimestep)
{
if (lsMessage->mbShow==true)	//si el mensaje se esta mostrando
    {
        //acumulador del tiempo
		lsMessage->mfDelay += lfTimestep;      
        if ( lsMessage->mfDelay < kfDelay )
            return;
		//si ya cumplió el tiempo a ser mostrado, reiniciar el contador del tiempo y dejar de mostrarlo
        lsMessage->mfDelay = 0.0f;
        lsMessage->mbShow = false;
    }
}
/**
	Visualizar el mensaje 
*/
void Message_Render	(TMESSAGE * lsMessage,TGRAPHICS * lsGraphic)
{
	//solo si el mensaje puede ser mostrado
    if (lsMessage->mbShow==true)
    {            
		GraphicManager_DrawMessage(lsGraphic,lsMessage->macText, lsMessage->miX, lsMessage->miY);       
    }
}