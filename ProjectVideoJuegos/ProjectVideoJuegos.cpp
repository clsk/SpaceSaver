// ProjectVideoJuegos.cpp : Defines the entry point for the console application.
//

#include <windows.h>
#include "Game.h"


//*************************************************************
//Eliminar la consola para que el juego se encargue de la creaci�n y la gesti�n
// #pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")


//**************************GLOBALES***************************
//Variables para controlar la velocidad del juego
unsigned long guiLastTime;	
unsigned long guiActualTime;
float gfTimestep;


//**************************************************************
//********FUNCIONES PARA LA MANIPULACION DE LOS EVENTOS*********
void AppRender()
{
	Game::get_instance().render();
}
void AppKeyboard(unsigned char lcKey, int x, int y)
{
	Game::get_instance().m_keyboard.process_key(lcKey, true);
	Game::get_instance().m_keyboard.set_modifiers(glutGetModifiers());
}
void AppKeyboardUp( unsigned char lcKey, int x, int y)
{
	Game::get_instance().m_keyboard.process_key(lcKey, false);
	Game::get_instance().m_keyboard.set_modifiers(glutGetModifiers());
}
void AppSpecialKeys(int liKey, int x, int y)
{
	Game::get_instance().m_keyboard.process_key(liKey, true);
	Game::get_instance().m_keyboard.set_modifiers(glutGetModifiers());
}
void AppSpecialKeysUp(int liKey, int x, int y)
{
	Game::get_instance().m_keyboard.process_key(liKey, false);
	Game::get_instance().m_keyboard.set_modifiers(glutGetModifiers());
}

/**
*	Funci�n que se ejecuta en cada ciclo durante la ejecuci�n del juego
**/
void AppIdle()
{
	if (Game::get_instance().status == GAME_DISPLAY_MENU)
	{
			Game::get_instance().load_scene("Level1.xml");
			Game::get_instance().status = GAME_PLAYING;

	}
	if(Game::get_instance().status != GAME_TERMINATED) 		
	{
		//Controlar la velocidad del juego
		guiActualTime=timeGetTime();
	    gfTimestep=((float)(guiActualTime-guiLastTime)/1000.0f);
	    guiLastTime=guiActualTime;
		//Actualizar y Pintar el juego
		Game::get_instance().update(gfTimestep);
		Game::get_instance().render();
	}
	else
	{
		exit(0);
	}
}
//*********************************************************************
//***********************MANIPULACION GLUT*****************************
/**
*	Funci�n encargada de inicializar y configurar la ventana del juego a 
*	trav�s de GLUT
**/
void _GLUT_InitializationWindow()
{
	int res_x,res_y,pos_x,pos_y;

	//Configura el modo de video
	glutInitDisplayMode(GLUT_RGBA | GLUT_ALPHA | GLUT_DOUBLE);

	//Obtener las dimensiones de la pantalla
	res_x = glutGet(GLUT_SCREEN_WIDTH);
	res_y = glutGet(GLUT_SCREEN_HEIGHT);
	//Calcula la posici�n donde debe mostrarse la ventana para que se muestre centrada
	//desplazamiento a la derecha equivale a div 2
	pos_x = (res_x>>1)-(GAME_WIDTH>>1);
	pos_y = (res_y>>1)-(GAME_HEIGHT>>1);
	
	//Configura las propiedades de la ventana
	glutInitWindowPosition(pos_x,pos_y);
	glutInitWindowSize(GAME_WIDTH,GAME_HEIGHT);
	glutCreateWindow("Space Saver");

	//Oculta el cursor
	glutSetCursor(GLUT_CURSOR_NONE);
}
/**
*	Funci�n encargada de REGISTRAR las funciones propias que manipular�n los eventos
**/
void _GLUT_Register()
{
	//Indica cual ser� la funci�n encargada de visualizaci�n
	glutDisplayFunc(AppRender);			
	//Indica cuales ser�n la funciones de control de entrada
	glutKeyboardFunc(AppKeyboard);		
	glutKeyboardUpFunc(AppKeyboardUp);	
	glutSpecialFunc(AppSpecialKeys);	
	glutSpecialUpFunc(AppSpecialKeysUp);
	//Indica cual ser� la funci�n encargada gestionar la l�gica del juego
	glutIdleFunc(AppIdle);
}
//**************************************************************************

int main(int argc, char* argv[])
{
    //Inicializa la Librer�a GLUT
	glutInit(&argc, argv);
	
	//Configurar la ventana del Juego
	_GLUT_InitializationWindow();
	
	//Registrar las funciones que manipular�n los eventos 
	_GLUT_Register();

    //Inicializaci�n del Juego
	Game::get_instance().status = GAME_DISPLAY_MENU;

    //Controlar la Velocidad del Juego
	guiLastTime= timeGetTime();
	
	//Ciclo de la Aplicaci�n 
	glutMainLoop();
	
	return 0;
}

