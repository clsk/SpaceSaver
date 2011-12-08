#include "stdafx.h"
#include "keyboard.h"

//**************FUNCIONES*****************
/**
*	Inicializar el arreglo de teclas
**/
Keyboard::Keyboard()
{	
	/**
		Inicializar el arreglo de teclas a 0 para indicar que ninguna tecla ha sido presionada
	*/
	memset(mabKeys, 0, ki_MAX_COUNT_KEY);
}
/**
*	Liberar los recursos reservados en el Init
**/
Keyboard::~Keyboard()
{
}
/**
*	Actualiza el arreglo de teclas de la estructura, 
*	para análisis posteriores durante el juego
**/
void Keyboard::process_key(char lcKey, bool lbPress)
{
	mabKeys[lcKey]=lbPress;
}

