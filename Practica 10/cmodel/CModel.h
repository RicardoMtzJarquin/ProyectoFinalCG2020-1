/*ooooo    WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW	UNAM
#ooooooo       WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW	Facultad de Ingenieria
#oo#ooo ooooo   WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
 ###oo//oo o      WWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
 ##oo o///oooooo    WWWWWWWWW              WWWWW
  # oooo///o/ oo      WWWW       /ooooooo   WWWW
W ##o##oo//////o  o          //oooo/////oo/ WWWW	CModel: API de programacion para carga, manipulacion 
W  ###oo  ////// oooo       oooooooooo///o/ WWWW	y dibujo de modelos poligonales con formato GFI y 3ds
WW ##ooo#oo///////oo     oooo/ oooo//oo//oo  WWW
WW  ##o##oooo/ooo/ooBBBBBB//o///oooo/oo///o  WWW	Desarrollada por:
WW   #o#oo o##/oooooBBBBB//ooooo//oooooo//o  WWW
WW   ###ooo## ooo BBBBB //oooo/ooooooooo//o   WW	Rojas Gonzales Renato Carlos
WW   ## o### ooBBBBBB /// o oooooooooooo//o   WW	Soto Serafin Alejandro			alexsoto@servidor.unam.mx
WWW   ##o#ooooBBBBBB////#######oo#oooooo /o   WW	Valencia Castro Luis Sergio
WWW    ###ooBBBBBB/////########oooooo/oo / o  WW
WWWW   o## BBBBB// ///###########o#oo o////o  WW	
WWWW    ##BBBBBB////#####  ### ## oo/ o////o  WW
WWWWW    ##BBBB////######   ##  #ooo/oo// /o  WW	
WWWWWW  ###B/// / #######   ##  #oooooo////o  WW
WWWWWW  ##B// // /#######   ##  ##oooo////o  WWW	
WWWWWW ###o/  / ooo######   ##  ##/ooo // o  WWW	22 de noviembre de 2005
WWWWW ###oo  // /oo#######  ### ## /oo / o   WWW
WWWW ##ooo/ / /oooo###############//oo//oo  WWWW
WWW ##oooo/ / ///oo###############/////oo   WWWW
WW ###ooo/// / oooo###############////oo   WWWWW
WW ###oo///  /ooo o############### / /o   WWWWWW
W ####oo/////oo$$oo###############///$$$  WWWWWW
W ####oo/// oo $$#$$$$$$$$$#####///$$o#$ WWWWWWW
W ####oo//  ooo$$##$##$$$$$$$$// //$ o#$ WWWWWWW
W ###ooo // ooo$$######$$$$$#$$/// $###$ WWWWWWW
W  ###oo   ///$$$############$$/# /$###$ WWWWWWW
WWW  ####oooo  $$## #####$####$###/$##$$ WWWWWWW
WWWWWW  #oooooo$$$   #$$$#####$###/$$$$$ WWWWWWW
WWWWWWW        $$$$$$ $$ #####$  ##$$$$  WWWWWWW
WWWWWWW         $$$$$$$$$$$$$$$   #$$$o   WWWWWW
WWWWWWWWWW   ##$$$$$$$$$$///oooooooo//$o$  WWWWW
WWWWWWWWWW  #####$$$$$$$///ooooooooo///$$    W*/

#ifndef CModelH
#define CModelH

#include "CObject.h"
#include "imageload.h"
#include "HandleStream.h"
#include "linkedlist.h"
//#include "GFILoader.h"
class CGFILoader;

#define _SHADED 4
#define _WIRED  2
#define _POINTS 0

#define MODEL_LOADED    6
#define OBJECT_LOADED   7
#define TABLE_LOADED    8
#define WRONG_FILE      9
#define WRONG_NAME      10
#define NOT_CONNECTED   11
#define SESSION_ERROR   12

class CModel
{
public:
    CModel();							//Class constructor
    ~CModel();                          //Class destructor

    bool GFILoad(char*);                //Load a GFI file
    bool GFIStartSession(char*);        //Creates a session with a GFI file
    bool GFILoadObject(char*);          //Load a lone object from a gfi file
    bool GFILoadObject(CObjectField*);  //
    bool GFIEndSession();               //Closes gfi file
    void GFIsave(char*);                //Saves model to a disk with GFI format

    bool _3dsLoad(char*);               //Load a 3ds file
    
    bool LoadTextureImages();           //Load the images that GL requires to build the textures
	void ReleaseTextureImages();		//
    
    void VertexNormals();               //vertex normals for better visualization
    void FlipNormals();                 //change vertex normals direcction

	VECTOR3D CalculateCenter();         //center calculus
	BOX CalculateBoundingBox();			//bbox calculos, need's a call to CalculateCenter() first
	
    void Translate(VECTOR3D&);          //permanently translate model
    void Scale(float);                  //permanently scale model
    void RotateZ(float);                //permanently rotate model trough z axis
    void RotateY(float);
    void RotateX(float);
	void MatrixMultiply(MATRIX4X4&);

    unsigned long GetObjectNumber();
    unsigned long GetMaterialNumber();

    bool IsSessionOpened();
    void KillSession();

    void GLIniTextures();				//This fuction creates OpenGL textures
    void GLEraseTextures();
    void GLrender(VECTOR3D*,int,float); //Call this fuction to render the Model with OpenGL

    CLinkedList<CObjectField> ObjectTable;	
    CLinkedList<CMaterial> MaterialList;	//Material list that give color to this model
    CLinkedList<CImage> ImageList;
    CLinkedList<CObject> ObjectList;		//this model is mde of several objects

    bool PointColision(VECTOR3D&,float);	//test for colision with a point

    short type;                         //this varible will tell us which mesh type is loaded (gfi, 3ds)
    unsigned long table_length;		    //longitud total de la tabla

    BOX bound;                          //model's bounding box
	VECTOR3D center;					//model's center

private:

    friend class C3dsloader;            //esto es para que estas clase accesen a CModel
    friend class CGFILoader;            //    

    unsigned long object_count;         //number of objects for the model (from 1 to ...) for GFI
    unsigned long material_count;       //para GFI
    unsigned long file_length;		    //longitud total del archivo

    CFileStream* gfistream;
    CGFILoader* gfisession;
    void GetPath(char*);
    char* path;                         //model's path
	char* filename;	                    //file name	
};

//distancia de un punto a un triangulo
float PointToTriDistance(VECTOR3D&,VECTOR3D&,VECTOR3D&,VECTOR3D&);
float PointToTriDistanceMod(VECTOR3D&,VECTOR3D&,VECTOR3D&,VECTOR3D&);

#endif
