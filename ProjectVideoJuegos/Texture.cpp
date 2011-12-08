#include "stdafx.h"
#include "Texture.h"

//**************FUNCIONES*****************
/**
*	Se encarga de cargar la Textura que indica el FILENAME
**/
bool Texture::load(const char * lacFilename,
				  int type, int wraps, int wrapt,
			      int magf, int minf, bool mipmap)
{
	//Declaración de variables
	corona::Image * lImg;
	int		liComponents;	//numero de componentes de color

	//Cargar la imagen
	lImg = corona::OpenImage(lacFilename);
	if(lImg==NULL) 
		return false;


	if(type==GL_RGB)
		liComponents = (int)eRGB;
	else if(type==GL_RGBA)
		liComponents = (int)eRGBA;
	else 
		return false;

	//actualizar las dimensiones de la imagen cargada
	miWidth			= lImg->getWidth();
	miHeight		= lImg->getHeight();

	//Se crea un ID para la textura y se guarda en mglID
	//El primer parametro indica la cantidad de ID de texturas que se van a crear
	glGenTextures(1, &mglID);
	//Se le indica al OpenGl cual es el ID de la textura activa
	glBindTexture(GL_TEXTURE_2D,mglID);

    // Funciones que determinan el color de un pixel en funcion de si el pixel correspondiente 
	//de la imagen debe cubrir un area mayor en pantalla o si debe cubrir un area menor 
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,wraps);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,wrapt);

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,magf);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,minf);
	//********************************************************************

	//se le indica al OpenGl cual es la imagen que se utilizará como textura
	if(!mipmap)
	{
		glTexImage2D(GL_TEXTURE_2D,0,liComponents,miWidth,miHeight,0,type,
					 GL_UNSIGNED_BYTE,lImg->getPixels());
	}
	else
	{
		//crea una serie de imagenes iguales pero de diferentes tamaños para hacer más eficiente
		//el tratamiento de las texturas cuando estén a diferentes distancias (proyección es perspectiva)
		gluBuild2DMipmaps(GL_TEXTURE_2D,liComponents,miWidth,miHeight,type,
						  GL_UNSIGNED_BYTE,lImg->getPixels());
	}

	return true;
}
/**
*	Devuelve el ID de la Textura
**/
int  Texture::getID()
{
	return mglID;
}
/**
*	Devuelve las dimensiones de la Textura
**/
void Texture::get_size(int *liW, int *liH)
{
	*liW = miWidth;
	*liH = miHeight;
}