#include "stdafx.h"
#include "game.h"
//**************FUNCIONES*****************
/**
*	Inicializa todos los componentes del juego y reserva la memoria necesaria
**/
void Game_Init(TGAME * lsGame)
{
	lsGame->mbFinish=false;
	lsGame->mfAcumulatedTime = 0.0f;

	Keyboard_Init(&(lsGame->mKeyboard));
	GraphicManager_Init(&(lsGame->mGraphic));

	if (!Scene_Init(&(lsGame->mScene),&(lsGame->mGraphic),kiFIRST_LEVEL))
		lsGame->mbFinish=true;	
}
/**
*	Libera los recursos reservados durante el juego
**/
void Game_Deinit(TGAME * lsGame)
{
	Keyboard_Deinit(&(lsGame->mKeyboard));
	GraphicManager_Deinit(&(lsGame->mGraphic));
	Scene_Deinit(&(lsGame->mScene));
}
/**
*	Actualiza los elementos que componen el juego y las variables auxiliares
**/
void Game_Update(TGAME * lsGame, float lfTimeStep)
{
	//controlando la velocidad
    lsGame->mfAcumulatedTime += lfTimeStep;
    if ( lsGame->mfAcumulatedTime < kfTimeLimit )
    {
        return;
    }
    lsGame->mfAcumulatedTime = 0.0f;
	
	//Validar si el usuario quiere salir del juego ESC
	lsGame->mbFinish= Keyboard_Check(&(lsGame->mKeyboard),eKey_Esc);

	Scene_Update(&(lsGame->mScene), &(lsGame->mKeyboard),lfTimeStep);
}
/**
*	Pinta el estado actual del juego
**/
void Game_Render(TGAME * lsGame)
{
	//*****************************************************************************
	//Limpiar los buffers
	GraphicManager_ClearBuffer(&(lsGame->mGraphic));

	//Visualizar la escena
	Scene_Render(&(lsGame->mScene),&(lsGame->mGraphic));

	//Visualizar buffer
	GraphicManager_SwapBuffer(&(lsGame->mGraphic));
}
/**
*	Determina si el juego ha terminado o no
**/
bool Game_HasFinish(TGAME * lsGame)
{
	return lsGame->mbFinish;
}

//*************************************************
/*
* Actualizar la entrada de teclado 
*/
void Game_ReadKeyboard(TGAME * lsGame, char lcKey, bool lbPress)
{
	Keyboard_ProcessKey(&(lsGame->mKeyboard),lcKey, lbPress);
}