/*ooooo    WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW	UNAM
#ooooooo       WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW	Facultad de Ingenieria
#oo#ooo ooooo   WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
 ###oo//oo o      WWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
 ##oo o///oooooo    WWWWWWWWW              WWWWW
  # oooo///o/ oo      WWWW       /ooooooo   WWWW
W ##o##oo//////o  o          //oooo/////oo/ WWWW	CGFILoader: Clase para carga de informacion poligonal
W  ###oo  ////// oooo       oooooooooo///o/ WWWW	con formato GFI
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

#ifndef GFILoaderH
#define GFILoaderH

#include "CModel.h"
#include "maths/maths.h"
#include "HandleStream.h"

class CModel;
class CObjectField;
class CObject;
class CMaterial;

class CGFILoader
{
public:
    CGFILoader(CHandleStream*,CModel*); //with this class we can read directly from a file or from a memory buffer
    void SetStream(CHandleStream*);
    bool Header(void);
    void ObjectTable(void);
    void Objects(void);
    void Object(CObjectField*);
    void Object();    
    void Materials(void);
    char* str_save(void);

private:

    CModel *Model;
    CObject *Obj;                   //pointer to a object class to load before it is inserted in the linked list
    CMaterial *Mat;                 //pointer to a material class to load before it is inserted in the linked list
    CObjectField *Field;

    CHandleStream* Stream;    
    char magic[8];

    unsigned long basura_long;
    unsigned short basura_short;

    VECTOR3D v1,v2,v3,v;       //vectores miscelaneos
};

//---------------------------------------------------------------------------
#endif
