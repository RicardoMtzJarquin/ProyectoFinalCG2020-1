/*ooooo    WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW	UNAM
#ooooooo       WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW	Facultad de Ingenieria
#oo#ooo ooooo   WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
 ###oo//oo o      WWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
 ##oo o///oooooo    WWWWWWWWW              WWWWW
  # oooo///o/ oo      WWWW       /ooooooo   WWWW
W ##o##oo//////o  o          //oooo/////oo/ WWWW	CImage: Clase para carga de Imagenes ahora solo con
W  ###oo  ////// oooo       oooooooooo///o/ WWWW	formato TGA.
WW ##ooo#oo///////oo     oooo/ oooo//oo//oo  WWW
WW  ##o##oooo/ooo/ooBBBBBB//o///oooo/oo///o  WWW	NOTA: Estas funciones no se deben llamar directamente,
WW   #o#oo o##/oooooBBBBB//ooooo//oooooo//o  WWW	para ello se ocupa la clase CModel.
WW   ###ooo## ooo BBBBB //oooo/ooooooooo//o   WW	
WW   ## o### ooBBBBBB /// o oooooooooooo//o   WW	
WWW   ##o#ooooBBBBBB////#######oo#oooooo /o   WW	
WWW    ###ooBBBBBB/////########oooooo/oo / o  WW
WWWW   o## BBBBB// ///###########o#oo o////o  WW	
WWWW    ##BBBBBB////#####  ### ## oo/ o////o  WW
WWWWW    ##BBBB////######   ##  #ooo/oo// /o  WW	
WWWWWW  ###B/// / #######   ##  #oooooo////o  WW	Desarrollada por:
WWWWWW  ##B// // /#######   ##  ##oooo////o  WWW	
WWWWWW ###o/  / ooo######   ##  ##/ooo // o  WWW	Rojas Gonzales Renato Carlos
WWWWW ###oo  // /oo#######  ### ## /oo / o   WWW	Soto Serafin Alejandro			alexsoto@servidor.unam.mx
WWWW ##ooo/ / /oooo###############//oo//oo  WWWW	Valencia Castro Luis Sergio
WWW ##oooo/ / ///oo###############/////oo   WWWW
WW ###ooo/// / oooo###############////oo   WWWWW
WW ###oo///  /ooo o############### / /o   WWWWWW	
W ####oo/////oo$$oo###############///$$$  WWWWWW	
W ####oo/// oo $$#$$$$$$$$$#####///$$o#$ WWWWWWW
W ####oo//  ooo$$##$##$$$$$$$$// //$ o#$ WWWWWWW	22 de noviembre de 2005
W ###ooo // ooo$$######$$$$$#$$/// $###$ WWWWWWW
W  ###oo   ///$$$############$$/# /$###$ WWWWWWW
WWW  ####oooo  $$## #####$####$###/$##$$ WWWWWWW
WWWWWW  #oooooo$$$   #$$$#####$###/$$$$$ WWWWWWW
WWWWWWW        $$$$$$ $$ #####$  ##$$$$  WWWWWWW
WWWWWWW         $$$$$$$$$$$$$$$   #$$$o   WWWWWW
WWWWWWWWWW   ##$$$$$$$$$$///oooooooo//$o$  WWWWW
WWWWWWWWWW  #####$$$$$$$///ooooooooo///$$    W*/

#ifndef imageloadH
#define imageloadH

#include "linkedlist.h"


class CImage : public CItem
{
    friend class CModel;
    friend class CObject;
    friend class CMD2;

public:
	CImage();
    ~CImage();

	bool LoadTGA(char *);
	bool LoadBMP(char *);

	void BuildGLTexture();

	void ReleaseImage();

    char* name;
	unsigned char*  imageData;
    int				bpp;			// Image Color Depth In Bits Per Pixel
    int				width;			// Image Width
    int				height;		    // Image Height

    unsigned int    GLindex;
};

#endif
