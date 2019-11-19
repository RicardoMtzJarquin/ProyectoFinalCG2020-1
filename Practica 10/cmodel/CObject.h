/*ooooo    WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW	UNAM
#ooooooo       WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW	Facultad de Ingenieria
#oo#ooo ooooo   WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
 ###oo//oo o      WWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
 ##oo o///oooooo    WWWWWWWWW              WWWWW
  # oooo///o/ oo      WWWW       /ooooooo   WWWW
W ##o##oo//////o  o          //oooo/////oo/ WWWW	CObject: Familia de clases para manejo de informacion poligonal
W  ###oo  ////// oooo       oooooooooo///o/ WWWW	en memoria principal accesibles desde la clase CModel.
WW ##ooo#oo///////oo     oooo/ oooo//oo//oo  WWW
WW  ##o##oooo/ooo/ooBBBBBB//o///oooo/oo///o  WWW
WW   #o#oo o##/oooooBBBBB//ooooo//oooooo//o  WWW
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

#ifndef CObjectH
#define CObjectH

#include "linkedlist.h"
#include "imageload.h"
#include "maths/maths.h"

class CObjectField;

typedef struct
{
    float r,g,b,a;  //color components: red,green,blue,alfa
}COLOR;

class CMaterial : public CItem
{
public:
	CMaterial();    //class constructor
    ~CMaterial();   //class destructor

    char* GetName();            //Function to get material's name
    char* GetTextName();        //Function to get texture name for this material
    COLOR GetDiffuse();         //Function to get the diffuse color component
    void SetDiffuse(COLOR);     //Function to store a diffuse color component

private:
    unsigned long id;   //this is the material's id, a GFI file offset
    char*       name;   //material's name
    COLOR		amb;    //ambient component
    COLOR		diff;   //diffuse component
    COLOR		spec;   //specular component
    float       shine_p;    //shininess percent
    float       shine_s;    //shininess strength
    char*       textname;   //if not null, this is the name of a texture to this material
    CImage*		img;        //Reference to a element in the image list that will make a texture for this material
	bool		twosided;

    friend class C3dsloader;
    friend class CGFILoader;
    friend class CModel;
    friend class CObject;
};

typedef struct
{
    unsigned short v1,v2,v3,flags;  //3 indices to a vector element
}FACE;

typedef struct
{
    float s,t;  //two bidimentional coordinates
}MAPPING;

typedef struct
{
    VECTOR3D cmayor;  //2 box's vertices
    VECTOR3D cmenor;  //
}BOX;

class CFaceMaterial : public CItem
{
public:
	CFaceMaterial();        //class constructor
    ~CFaceMaterial();       //clas destructor

private:

    char* name;             //name of the material belonging this info
    unsigned long offset;   //Reference to a element in the material list belonging this info in the file
    unsigned short nfaces;  //number of faces that this material belongs
    unsigned short* faceid; //list of face indices
	CMaterial* material;    //Reference to a element in the material list belonging this info in memeory

    friend class CModel;
    friend class CObject;
    friend class C3dsloader;
    friend class CGFILoader;
};

class CObject : public CItem
{
public:

    CObject();                  //class constructor
    ~CObject();                 //class destructor

	void GLIniTextures();
	void GLrender(VECTOR3D*,int,float);
	void GLEraseTextures();

	bool LoadTextureImages(CLinkedList<CImage>*);
    bool FreeTextureImages(CLinkedList<CImage>*);

    char*	GetName();            //Function to get the object's name
    BOX		GetBox();               //Function to get BOX structure
    short	GetHierarchy();
    VECTOR3D GetCenter();
	unsigned short GetVertexNumber();   //Function to retrieve the number of object's vertexes
    unsigned short GetFaceNumber();     //Function to retrieve the number of object's faces

	float Volume();
	void Center();           //Functions to calculate and get the object's center
	bool VertexNormals();       //Fucntion to calculate Vertex Normals

    void Translate(VECTOR3D&);			//Functions to trasform object geometry
    void Scale(float);
    void RotateZ(float);
    void RotateY(float);
    void RotateX(float);
	void MatrixMultiply(MATRIX4X4&);	//multiplies object by a custom matrix,
						//all this functions leaves their result in "transformed" array


	unsigned short	nverts;		//number of vertices for the object
	VECTOR3D*		vertices;	//pointer to a list of vertices
	VECTOR3D*		vn;		    //pointer to a list of vertex normals

    unsigned short  nfaces;	    //number of faces for the object
    FACE*			faces;	    //pointer to a list of faces
    VECTOR3D*		fn;		    //pointer to a list of faces normals

    unsigned short	ncoords;    //number of texturization coordinates for the object
	MAPPING*        coords;     //pointer to a list of texture corrdinates

    unsigned short	nma;	    //number of materials for this object
	CLinkedList<CFaceMaterial> facemat_list;	//a linked list of info about this model's materials
private:

    friend class C3dsloader;
    friend class CModel;
    friend class CGFILoader;
    friend class CObjectField;

    

	unsigned long	file_offset; //offset en el archivo gfi save
    bool			blend_flag;  //is this object have a transparency effect?
	CObjectField*   Table;       //solo referencia hacia el campo de la tabla

	VECTOR3D			obj_center;	 //object's center vector
    VECTOR3D			pivot;
    //COORD_SYS		coordsys;
	float			volume;
};



class CObjectField : public CItem
{
public:
	CObjectField();     //class constructor
    ~CObjectField();    //class destructor

    char* GetName();        //Function to get the object's name
    bool IsLoaded();        //Function to know if an object is loaded
    short GetHierarchy();   //Fucntion to get the object's hierarchy
    void SetHierarchy(short);   //Function to change object's hierarchy
    BOX GetBox();               //Function to get object bounding box
    CObject* object;            //pointer to the real object's data

private:

    char *name_obj;     //pointer to the object's name
    short hierarchy;    //object's hierarchy
    BOX bound;          //object bounding box
    unsigned long offset_obj;   //object file offset
    unsigned long block_size;   //object's size in file

    friend class CObject;
    friend class CGFILoader;
    friend class C3dsloader;
    friend class CModel;
};
#endif
