#ifndef _KEYBOARD
#define _KEYBOARD

/**
*	ESTE ARCHIVO PERMITE GESTIONAR LA ENTRADA DESDE EL TECLADO,
*	CREANDO UN NIVEL DE INDEPENDENCIA DE LA APLICACION
**/


//***************CONSTANTES***************
/**
*	Cantidad m�xima de canales de entrada (teclas) que se podr�n procesar
**/
const int ki_MAX_COUNT_KEY=256;

//*************ENUMERATIVOS***************
/**
*	Tipo enumerativo auxiliar para determinar los c�digos de las
*	posibles teclas que se obtendr�n del buffer de entrada
**/
enum eInputKeys
{
	eKey_Esc  = VK_ESCAPE,
	eKey_Up   = GLUT_KEY_UP,
	eKey_Down = GLUT_KEY_DOWN,
	eKey_Left = GLUT_KEY_LEFT,
	eKey_Right= GLUT_KEY_RIGHT,
	eKey_Space= VK_SPACE,
	eKey_Enter= VK_RETURN
};

//**************ESTRUCTURAS***************
/**
*	Define los elementos b�sicos para el control del teclado
*	como dispositivo de entrada.
**/
class Keyboard
{
public:
	/**
	*	Inicializar el arreglo de teclas
	**/
	Keyboard();
	~Keyboard();

	/**
	*	Dada una entrada (tecla) determina si esta ha sido presionada
	**/
	bool check(int)
	{
		return  mabKeys[liEntry];
	}

	/**
	*	Actualiza el arreglo de teclas de la estructura, 
	*	para an�lisis posteriores durante el juego
	**/
	void process_key(char, bool);

private:
	/**
		Almacena las teclas disponibles a utilizar.  Max: 256
		0-> indica que la tecla no ha sido presionada
		1-> indica que la tecla ha sido presionada
	*/
	bool mabKeys[ki_MAX_COUNT_KEY];


};

#endif _KEYBOARD