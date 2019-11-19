//#include <windows.h>  //Solo para Windows
//#include <GL/gl.h>     // The GL Header File
//#include <stdio.h>

//#include <math.h>
#include "Main.h"


class CFiguras
{
	public:

	float text_der;
	float text_izq;

	void esfera(GLfloat radio, int meridianos, int paralelos, GLuint text); //Func�on creacion esfera
	void cilindro(float radio, float altura, int resolucion, GLuint text);	//Func�on creacion cilindro
	void cono(float altura, float radio, int resolucion, GLuint text);		//Func�on creacion cono
	void prisma_anun (GLuint text, GLuint text2);							//Func�on creacion movimiento
	void prisma (float altura, float largo, float profundidad, GLuint text);//Func�on creacion prisma
	void prismaT(float altura, float largo, float profundidad, GLuint text, GLuint text1);//Func�on creacion prisma del techo
	void prismaC(float altura, float largo, float profundidad, GLuint text);//Func�on creacion prisma de los muro de la casa
	void prismaV(float altura, float largo, float profundidad, GLuint text, GLuint text1);//Func�on creacion prisma del techo
	void prismaM(float altura, float largo, float profundidad, GLuint text, GLuint text1);//Func�on creacion prisma del techo
	void prismaCOL(float altura, float largo, float profundidad, GLuint text, GLuint text1, GLuint text2);//Func�on creacion prisma del colchon
	void prismaCamino(float altura, float largo, float profundidad, GLuint text);//Func�on creacion prisma del techo

	void prisma2 (GLuint text, GLuint text2);
	void skybox(float altura, float largo, float profundidad, GLuint text, GLuint text1);	//Funcion creacion cielo
	

	//void torus(GLfloat radioM, GLfloat radiom, int meridianos, int paralelos, GLuint text );
	void torus(GLfloat radioM, GLfloat radiom, int meridianos, int paralelos);

};
