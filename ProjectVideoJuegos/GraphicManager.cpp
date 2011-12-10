#include <gl/glut.h>
#include "GraphicManager.h"


//**************FUNCIONES*****************
/**
*	Funci�n encargada de inicializar los gr�ficos
**/
GraphicManager::GraphicManager()
{	
	//Inicializar la gesti�n de los gr�ficos por OpenGL
	glClearColor(0.0f,0.0f,0.0f,0.0f);			//Establece el color de fondo 
	
	//Gesti�n de la matriz de proyecci�n (perspectiva o vista)
	glMatrixMode(GL_PROJECTION);//activar la matriz de PROJECTION
	glLoadIdentity();			//se inicializa la matriz de PROJECTION en la Identidad
	
	//define una perspectiva ortonormal -> Param: x_m�nima, x_m�xima, y_m�nima, y_m�xima, z_m�nima, z_m�xima
	//sirve para delimitar el volumen de vista
	glOrtho(0,GAME_WIDTH,0,GAME_HEIGHT,0,1);

	//Gesti�n de la matriz de visi�n del modelo (modelado)
	glMatrixMode(GL_MODELVIEW);	

	//Habilitar el uso de la componente ALPHA
	glAlphaFunc(GL_GREATER, 0.05f);
	glEnable(GL_ALPHA_TEST);
}
/**
*	Libera los recursos que se reservan en el Init
**/
GraphicManager::~GraphicManager()
{
}

//******************MANIPULACION DEL BUFFER***********
/**
*  Funci�n encargada de intercambiar los buffers para actualizar la pantalla  
*/
void GraphicManager::SwapBuffer()
{
    glutSwapBuffers();
}

/**
*    Funci�n encargada de limpiar los buffers
*/
void GraphicManager::ClearBuffer()
{
    glClear(GL_COLOR_BUFFER_BIT);	//limpia el buffer de color
	glLoadIdentity();				//carga la matriz identidad
}

//****************************************************************
//Visualizar el objeto en la pantalla
void GraphicManager::DrawObject(int liIdTex, int liObjW, int liObjH ,float xo,float yo,float xf,float yf, int liScreen_X, int liScreen_Y)
{	
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,liIdTex); //Activa la textura con la que se va a trabajar
	//Se monta la textura sobre el poligono que la renderizar�
	glBegin(GL_QUADS);	//cuadrado
		glTexCoord2f(xo,yo);	glVertex2i(liScreen_X				,liScreen_Y);
		glTexCoord2f(xf,yo);	glVertex2i(liScreen_X+liObjW		,liScreen_Y);
		glTexCoord2f(xf,yf);	glVertex2i(liScreen_X+liObjW		,liScreen_Y+liObjH);
		glTexCoord2f(xo,yf);	glVertex2i(liScreen_X				,liScreen_Y+liObjH);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}


//Visualizar el mapa en la pantalla
void GraphicManager::DrawMap(int liIdImg, int liNivel)	
{
	glEnable(GL_TEXTURE_2D);
		//Activar la textura con la que se va a trabajar
		glBindTexture(GL_TEXTURE_2D,liIdImg);
		glCallList(liNivel);
	glDisable(GL_TEXTURE_2D);
}

//Visualizar los mensajes en la pantalla
void GraphicManager::DrawMessage(const char * lacText,int liX, int liY, void* font )
{           
	int liIndex;
	for(liIndex=0; liIndex < strlen(lacText); liIndex++) 
	{         
		//determina la posici�n donde ser� mostrado el car�cter
		glRasterPos2f(liX + liIndex*ESPAI,liY );
		//dibuja un caracter con un formato y tama�o dado
		glutBitmapCharacter(font,(int)(lacText[liIndex]));
	}
}


