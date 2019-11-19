/*ooooo    WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW	UNAM
#ooooooo       WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW	Facultad de Ingenieria
#oo#ooo ooooo   WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
 ###oo//oo o      WWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
 ##oo o///oooooo    WWWWWWWWW              WWWWW
  # oooo///o/ oo      WWWW       /ooooooo   WWWW
W ##o##oo//////o  o          //oooo/////oo/ WWWW	CHandleStream: Clase para manejo de flujo de datos
W  ###oo  ////// oooo       oooooooooo///o/ WWWW	
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

#ifndef HandleStreamH
#define HandleStreamH

#include <stdio.h>

class CHandleStream
{
public:
    CHandleStream();
    ~CHandleStream();

    virtual int Read (void*, int)  =0;
    virtual void Write(void*, int) =0;
    virtual void SetPosition(long)  =0;
    virtual long GetPosition()      =0;
private:
};

class CFileStream: public CHandleStream
{
public:
    CFileStream();
    ~CFileStream();

    bool Open(char*,char*); //abre un archivo con nombre char* y modo de escritura char*
    int Read (void*, int);
    void Write(void*, int); //escribe al archivo el bloque de datos de tamano int apuntado por void*
    void SetPosition(long);
    long GetPosition();

    void Seek(long,int);
private:
    FILE* fp;
};


class CMemoryStream: public CHandleStream
{
public:
    CMemoryStream();
    ~CMemoryStream();

    bool LoadFromFile(char*);
    int Read (void*, int);
    void Write(void*, int);
    void SetPosition(long);
    long GetPosition();
    long FileLength();
private:
    FILE* fp;
    char* fb;
    long position;
    long length;
};
//---------------------------------------------------------------------------
#endif
