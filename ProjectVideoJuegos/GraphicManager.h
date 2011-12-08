#ifndef _GRAPHIC_MANAGER
#define _GRAPHIC_MANAGER

/**
*	ESTE ARCHIVO PERMITE MANIPULAR LOS GRAFICOS (SALIDA|VISUALIZACION),
*	CREANDO UN NIVEL DE INDEPENDENCIA DE LA APLICACION
**/

#include "Texture.h"

//***************CONSTANTES***************
//Indica el size de las letras, medido en pixeles  
#define ESPAI		20.0	
//Constantes para definir el size de la ventana en la ejecuci�n
#define   GAME_WIDTH		640		
#define   GAME_HEIGHT		480
//Define la cantidad m�xima de texturas que se pueden cargar
const int kiMAX_TEXTURE=10;

//**************ESTRUCTURAS***************
/**
*	Define los elementos b�sicos para el control de los gr�ficos
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
	void DrawMessage(char *, int, int);
	void DrawMap(int liIdImg, int);


private:
};

#endif