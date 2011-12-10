#ifndef _GRAPHIC_MANAGER
#define _GRAPHIC_MANAGER

/**
*	ESTE ARCHIVO PERMITE MANIPULAR LOS GRAFICOS (SALIDA|VISUALIZACION),
*	CREANDO UN NIVEL DE INDEPENDENCIA DE LA APLICACION
**/
#include <string>
#include <gl/glut.h>
#include "Texture.h"

//***************CONSTANTES***************
//Indica el size de las letras, medido en pixeles  
#define ESPAI		20.0	
//Constantes para definir el size de la ventana en la ejecución
#define   GAME_WIDTH		640		
#define   GAME_HEIGHT		480
//Define la cantidad máxima de texturas que se pueden cargar
const int kiMAX_TEXTURE=10;

//**************ESTRUCTURAS***************
/**
*	Define los elementos básicos para el control de los gráficos
**/
template<typename T = int>
struct Point
{
	Point(const T& _x = 0, const T& _y = 0) : x(_x), y(_y) {}
	T x, y;
};

class GraphicManager
{
public:
	/**
	*	Se encarga de inicializar el arreglo de texturas
	**/
	GraphicManager();
	~GraphicManager();

	void SwapBuffer();
	void ClearBuffer();
	
	//*****************************************************************************
	//Visualizar el objeto en la pantalla

	void DrawObject(int liIdTex, int liObjW, int liObjH ,float xo,float yo,float xf,float yf, int liScreen_X, int liScreen_Y);
	/*
	 *  Opciones de fonts
	 *	GLUT_BITMAP_8_BY_13
	 *	GLUT_BITMAP_9_BY_15
	 *	GLUT_BITMAP_TIMES_ROMAN_10
	 *	GLUT_BITMAP_TIMES_ROMAN_24
	 *	GLUT_BITMAP_HELVETICA_10
	 *	GLUT_BITMAP_HELVETICA_12
	 *	GLUT_BITMAP_HELVETICA_18
	 */
	void DrawMessage(const char *, int, int, void* font = GLUT_BITMAP_HELVETICA_12);
	void DrawMessage(std::string& str, int x, int y, void* font = GLUT_BITMAP_HELVETICA_12)
	{
		DrawMessage(str.c_str(), x, y, font);
	}
	void DrawMap(int liIdImg, int);


private:
};

#endif