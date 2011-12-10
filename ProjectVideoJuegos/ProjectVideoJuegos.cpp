// ProjectVideoJuegos.cpp : Defines the entry point for the console application.
//

#include <windows.h>
#include "Game.h"


//*************************************************************
//Eliminar la consola para que el juego se encargue de la creación y la gestión
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
*	Función que se ejecuta en cada ciclo durante la ejecución del juego
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
*	Función encargada de inicializar y configurar la ventana del juego a 
*	través de GLUT
**/
void _GLUT_InitializationWindow()
{
	int res_x,res_y,pos_x,pos_y;

	//Configura el modo de video
	glutInitDisplayMode(GLUT_RGBA | GLUT_ALPHA | GLUT_DOUBLE);

	//Obtener las dimensiones de la pantalla
	res_x = glutGet(GLUT_SCREEN_WIDTH);
	res_y = glutGet(GLUT_SCREEN_HEIGHT);
	//Calcula la posición donde debe mostrarse la ventana para que se muestre centrada
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
*	Función encargada de REGISTRAR las funciones propias que manipularán los eventos
**/
void _GLUT_Register()
{
	//Indica cual será la función encargada de visualización
	glutDisplayFunc(AppRender);			
	//Indica cuales serán la funciones de control de entrada
	glutKeyboardFunc(AppKeyboard);		
	glutKeyboardUpFunc(AppKeyboardUp);	
	glutSpecialFunc(AppSpecialKeys);	
	glutSpecialUpFunc(AppSpecialKeysUp);
	//Indica cual será la función encargada gestionar la lógica del juego
	glutIdleFunc(AppIdle);
}
//**************************************************************************

int main(int argc, char* argv[])
{
    //Inicializa la Librería GLUT
	glutInit(&argc, argv);
	
	//Configurar la ventana del Juego
	_GLUT_InitializationWindow();
	
	//Registrar las funciones que manipularán los eventos 
	_GLUT_Register();

    //Inicialización del Juego
	Game::get_instance().status = GAME_DISPLAY_MENU;

    //Controlar la Velocidad del Juego
	guiLastTime= timeGetTime();
	
	//Ciclo de la Aplicación 
	glutMainLoop();
	
	return 0;
}

