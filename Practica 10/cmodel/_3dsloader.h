/*ooooo    WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW	UNAM
#ooooooo       WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW	Facultad de Ingenieria
#oo#ooo ooooo   WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
 ###oo//oo o      WWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
 ##oo o///oooooo    WWWWWWWWW              WWWWW
  # oooo///o/ oo      WWWW       /ooooooo   WWWW
W ##o##oo//////o  o          //oooo/////oo/ WWWW	C3dsloader: Clase para carga de informacion poligonal
W  ###oo  ////// oooo       oooooooooo///o/ WWWW	con formato 3ds
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
#ifndef _3dsloaderH
#define _3dsloaderH

//----- Primary chunk
#define MAIN3DS       0x4D4D

//----- Main Chunks
#define EDIT3DS       0x3D3D  // this is the start of the editor config
#define KEYF3DS       0xB000  // this is the start of the keyframer config

//----- sub defines of EDIT3DS
#define EDIT_CONFIG1  			0x0100
#define	BACKGR_BITMAP  			0x1100
#define USE_BACKGR_BITMAP		0x1101
#define BACKGR_COLOR   			0x1200
#define USE_BACKGR_COLOR		0x1201
#define GRADIENT_COLORS			0x1300
#define USE_GRADIENT_COLORS		0x1301
#define SHADOW_MAP_BIAS			0x1400
#define SHADOW_MAP_SIZE			0x1420
#define SHADOW_MAP_SAMPLE_RANGE	0x1450
#define RAYTRACE_BIAS			0x1460
#define RAYTRACE_BIAS_ON		0x1470
#define AMBIENT_COLOR			0x2100
#define	FOG 					0x2200
#define USE_FOG					0x2201
#define FOG_BACKGR				0x2210
#define DISTANCE_QUEUE			0x2300
#define USE_DISTANCE_QUEUE		0x2301
#define LAYERED_FOG_OPTIONS		0x2302
#define USE_LAYERED_FOG			0x2303
#define WINDOW_SETTINGS			0x7001
#define MESH_VERSION  			0x3D3E
#define OBJ						0x4000
#define MATERIAL				0xAFFF

//----- sub defines of OBJ
#define OBJ_HIDDEN				0x4010
#define OBJ_DOESNT_CAST			0x4012
#define MATTE_OBJ				0x4013
#define EXTER_PROCESS_ON		0x4015
#define OBJ_DOESNT_RECV_SHADOWS	0x4017
#define LIGHT					0x4600
#define CAMERA					0x4700
#define TRIANGULAR				0x4100

//----- sub defines of TRIANGULAR
#define VERTEX_LIST   			0x4110
#define FACES_DESCRIPTION		0x4120
#define MAPPING_COORD_LIST		0x4140
#define LOCAL_COORD_SYSTEM		0x4160
#define OBJ_COLOR_IN_EDITOR		0x4165
#define EXTER_PROCCES_NAME		0x4181
#define EXTER_PROCCES_PARAMETER	0x4182

//----- sub defines of MATERIAL
#define MATERIAL_NAME			0xA000
#define MAT_AMBIENT_COLOR		0xA010
#define	MAT_DIFFUSE_COLOR		0xA020
#define MAT_SPECULAR_COLOR		0xA030
#define SHININESS_PERCENT		0xA040
#define SHININESS_STRENGTH_PERCENT	0xA041
#define	TRANSPARENCY			0xA050
#define TWOSIDED				0xA081

#define RGB1	0x0011
#define RGB2	0x0012
#define	PERCENT	0x0030

//sub defines of TEXTUREDATA
#define TEXTURES 		0xA200
#define TEXTURE_NAME	0xA300

#define HIERARCHY	0xB010
#define MESH_INFO	0xB002
#define	PIVOT		0xB013

#define INI_POS 6   //because it's the sum in bytes of the size of the chunk id (2) and its length (4)

#include "CModel.h"

class C3dsloader
{
public:
    C3dsloader(CHandleStream*,CModel*);
    ~C3dsloader();
    bool mainchunk(void);
private:
    CModel *Model;
    CObject *Obj;                   //pointer to a object class to load before it is inserted in the linked list
    CMaterial *Mat;                 //pointer to a material class to load before it is inserted in the linked list

    CHandleStream* Stream;

    char* nombre_obj;
    bool default_used;
    bool default_included;    

    void primarychunk(unsigned long);
    void editchunk(unsigned long);
    void adddefault(void);
    void materialchunk(unsigned long);
    void color_read(unsigned long, COLOR*);
    void percentchunk(unsigned long, float*);
    void texturedata(unsigned long);
    void objectchunk(unsigned long,unsigned long);
    void triangularchunk(unsigned long);
    void read_vertex(void);
    void read_faces(unsigned long);
    void facematerial(unsigned long,unsigned long);
    void read_mapping(void);
    void read_coord_sys(void);
    void keychunk(unsigned long);
    void meshinfochunk(unsigned long);

    void Pivote(void);
    void mov_bufferp(unsigned long);
    char* str_save(void);
};

//---------------------------------------------------------------------------
#endif


