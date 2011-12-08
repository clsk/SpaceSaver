#include "stdafx.h"
#include "Scene.h"

//**************FUNCIONES*****************
/**
*	Inicializa la escena del juego, se encarga de inicializar las estructuras y 
*	leer el XML.
**/
bool Scene_Init(TSCENE * lsScene, TGRAPHICS * lsGraphic, int liLevel)
{
	//inicializa la gestión de los mensajes
	Message_Init(&(lsScene->mMessage),10,10,"Mi primer videojuego en 2D");
	
	//configurar la escena
	lsScene->miBLOCK_SIZE=24;
	lsScene->miTILE_SIZE=16;
	lsScene->miSCENE_HEIGHT=480;
	lsScene->miSCENE_WIDTH=640;

	//configurar al Player
	lsScene->msPlayer.mcId=1;
	lsScene->msPlayer.miFRAME_DELAY=8;
	
	lsScene->msPlayer.miW=32;
	lsScene->msPlayer.miH=32;
	lsScene->msPlayer.miX=16;
	lsScene->msPlayer.miY=20;

	lsScene->msPlayer.miSeq=0;
	lsScene->msPlayer.miDelay=0;

	GraphicManager_LoadImage(lsGraphic,1,".\\IMAGES\\Bub.png",GL_RGBA);
	lsScene->msPlayer.miIdImage=1;
	lsScene->msPlayer.miState=eSTATE_LOOKRIGHT;
	return true;
}
/**
*	Libera los recursos reservados durante la escena
**/
bool Scene_Deinit(TSCENE * lsScene)
{
	//liberar la memoria reservada para el mensaje
	Message_Deinit(&(lsScene->mMessage));
	return true;
}
/**
*	Actualiza las variables, estruturas, entidades, etc de la escena.
**/
void Scene_Update(TSCENE * lsScene, TKEYBOARD * lsKeyBoard, float lfTimeStep)
{
	int liYaux, liXaux;
	if(lsKeyBoard->mabKeys[GLUT_KEY_LEFT])	
	{
		if( (lsScene->msPlayer.miX % lsScene->miTILE_SIZE) == 0)
		{
		liXaux = lsScene->msPlayer.miX;
		lsScene->msPlayer.miX -= kiSTEP_LENGTH;
		if(lsScene->msPlayer.miX<=0)
			{
				lsScene->msPlayer.miX = liXaux;
				lsScene->msPlayer.miState = eSTATE_LOOKLEFT;
			}
		}	
		else
		{
		lsScene->msPlayer.miX -=kiSTEP_LENGTH;
		if( lsScene->msPlayer.miState != eSTATE_WALKLEFT )
			{
				lsScene->msPlayer.miState = eSTATE_WALKLEFT;
				lsScene->msPlayer.miSeq = 0;
				lsScene->msPlayer.miDelay = 0;
			}
		}
	}
	else if(lsKeyBoard->mabKeys[GLUT_KEY_RIGHT])	
	{
		if( (lsScene->msPlayer.miX % lsScene->miTILE_SIZE) == 0)
		{
		liXaux = lsScene->msPlayer.miX;
		lsScene->msPlayer.miX+= kiSTEP_LENGTH;
		if((lsScene->msPlayer.miX+lsScene->msPlayer.miW)>=(lsScene->miSCENE_WIDTH))
			{
				lsScene->msPlayer.miX = liXaux;
				lsScene->msPlayer.miState = eSTATE_LOOKRIGHT;
			}
		}	
		else
		{
		lsScene->msPlayer.miX +=kiSTEP_LENGTH;
		if( lsScene->msPlayer.miState != eSTATE_WALKRIGHT )
			{
				lsScene->msPlayer.miState = eSTATE_WALKRIGHT;
				lsScene->msPlayer.miSeq = 0;
				lsScene->msPlayer.miDelay = 0;
			}
		}
	}
	else //stop
	{		
		switch(lsScene->msPlayer.miState)
		{
		case eSTATE_WALKLEFT :	lsScene->msPlayer.miState = eSTATE_LOOKLEFT;		break;
		case eSTATE_WALKRIGHT:	lsScene->msPlayer.miState = eSTATE_LOOKRIGHT;		break;
		case eSTATE_WALKUP	 :	lsScene->msPlayer.miState = eSTATE_LOOKUP;			break;
		case eSTATE_WALKDOWN :	lsScene->msPlayer.miState = eSTATE_LOOKDOWN;		break;
		}
	}

}
/**
*	Pinta el estado actual de la escena
**/
void Scene_Render(TSCENE * lsScene, TGRAPHICS * lsGraphic)
{
	
	//Mostrar los mensajes que se debe mostrar en el juego
	Message_Render(&(lsScene->mMessage),lsGraphic);

	//Mostrar al Player
	Scene_RenderObject(lsScene, lsGraphic);
}

void Scene_RenderObject(TSCENE * lsScene, TGRAPHICS * lsGraphic)
{
	float xo=0.0f,yo=0.0f,xf=0.0f,yf=0.0f;
	/**
		Se obtiene la posición dentro del sprite que le corresponde al objeto y se determina el área a leer
	*/
	switch (lsScene->msPlayer.miState)
	{
	
		case eSTATE_LOOKLEFT:	xo = 0.0f;	yo = 0.25f;
									break;
		
		case eSTATE_LOOKRIGHT:	xo = 0.25f;	yo = 0.25f;
									break;
		
		case eSTATE_WALKLEFT:	xo = 0.0f;	yo = 0.25f+ lsScene->msPlayer.miSeq*0.25;
									Scene_NextFrame((lsScene),3);
									break;
		
		case eSTATE_WALKRIGHT:	xo = 0.25f; yo = 0.25f + lsScene->msPlayer.miSeq*0.25;
									Scene_NextFrame((lsScene),3);
									break;
		
		case eSTATE_LOOKUP:		xo = 0.50f;	yo = 0.25f;
									break;
		
		case eSTATE_LOOKDOWN:	xo = 0.75f; yo = 0.25f;						
									break;
		
		case eSTATE_WALKUP:		xo = 0.50f;	yo = 0.25f;
									Scene_NextFrame((lsScene),3);
									break;
		case eSTATE_WALKDOWN:	xo = 0.75f;	yo = 0.25f;
									Scene_NextFrame((lsScene),3);
									break;

	}
	xf = xo + 0.25f;
	yf = yo - 0.25f;


	//determinar la posición en la pantalla donde se pintará
	int liScreen_X,liScreen_Y;
	liScreen_X = lsScene->msPlayer.miX + lsScene->miSCENE_Xo;
	liScreen_Y = (lsScene->msPlayer.miY)  + lsScene->miSCENE_Yo + (lsScene->miBLOCK_SIZE - lsScene->miTILE_SIZE);
	
	//renderizar el objeto
	GraphicManager_DrawObject(lsGraphic, lsScene->msPlayer.miIdImage, lsScene->msPlayer.miW, lsScene->msPlayer.miH, xo,yo,xf,yf,liScreen_X,liScreen_Y);
}
/**
	Control de los frames que representan un movimiento
*/
void Scene_NextFrame(TSCENE * lsScene, int liMax)
{
	lsScene->msPlayer.miDelay++;
	if(lsScene->msPlayer.miDelay == lsScene->msPlayer.miFRAME_DELAY)
	{
		lsScene->msPlayer.miSeq++;
		lsScene->msPlayer.miSeq%=liMax;
		lsScene->msPlayer.miDelay = 0;
	}
}


