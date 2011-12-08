#ifndef _GLOBALS
#define _GLOBALS



/**
    Estructura para almacenar la información de los objetos
*/
typedef struct sSpecialCell
{
    char mcId;  
    int  miX;    
    int  miY; 
    int  miW;    
    int  miH; 
    int  miIdImage;
	eObjectState  miState;
	int  miFRAME_DELAY;
	int	 miSeq;
	int  miDelay;
}TSpecialCell;



#endif _GLOBALS