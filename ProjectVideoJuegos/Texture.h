#ifndef _TEXTURE_H
#define _TEXTURE_H

#include <gl/glut.h>
#include "Libraries\Corona\corona.h"
//***********CONSTANTES Y ENUMERATIVOS***************
typedef enum eColorComponents
{
	eALPHA =1,
	eLUMINANCE,
	eRGB,
	eRGBA
};

//*******************ESTRUCTURAS*********************
/**
*	Define los elementos básicos de la Textura
**/

class Texture
{
public:
	//**************FUNCIONES*****************
	/**
	*	Se encarga de cargar la Textura que indica el FILENAME
	**/
	bool load(const char * lacFilename,
					  int type = GL_RGBA, int wraps = GL_REPEAT, int wrapt = GL_REPEAT,
				      int magf = GL_NEAREST, int minf = GL_NEAREST, bool mipmap = false);

	/**
	*	Devuelve el ID de la Textura
	**/
	int  getID() const
	{
		return mglID;
	}

	/**
	*	Devuelve las dimensiones de la Textura
	**/
	void get_size(int *,int *);
private:
	GLuint	mglID;			//id de la textura
	int		miWidth;		//dimensiones de la imagen
	int		miHeight;

};


#endif