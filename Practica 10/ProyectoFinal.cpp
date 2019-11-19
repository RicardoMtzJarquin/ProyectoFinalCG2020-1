//Semestre 2020 - 1
//************************************************************//
//***   Proyecto Final      Escenario virtual           ******//
//*** 	Alumnos:                                        ******//
//***			Martínez Jarquín Ricardo Eduardo        ******//
//***			Salgado Salazar Carlos Eduardo          ******//
//***           Grupo 02                                ******//
//************************************************************//

#include "texture.h"
#include "figuras.h"
#include "Camera.h"
#include "cmodel/CModel.h"


CCamera objCamera; 
GLfloat g_lookupdown = 0.0f;    // Look Position In The Z-Axis (NEW) 


GLfloat Diffuse[]= { 0.5f, 0.5f, 0.5f, 1.0f };				// Diffuse Light Values
GLfloat Specular[] = { 1.0, 1.0, 1.0, 1.0 };				// Specular Light Values
GLfloat Position[]= { 0.0f, 27.0f, -5.0f, 0.0f };			// Light Position
GLfloat Position2[]= { 0.0f, 0.0f, -5.0f, 1.0f };			// Light Position

GLfloat m_dif1[] = { 0.0f, 0.2f, 1.0f, 1.0f };				// Diffuse Light Values
GLfloat m_spec1[] = { 0.0, 0.0, 0.0, 1.0 };				    // Specular Light Values
GLfloat m_amb1[] = { 0.0, 0.0, 0.0, 1.0 };				    // Ambiental Light Values
GLfloat m_s1[] = {18};

CTexture cielo;		       //cielo del escenario
CTexture pasto;		       //pasto del piso
CTexture muro;		       //muros de la casa
CTexture techo;		       //techo de la casa 
CTexture columna;	       //columna de la casa
CTexture piso;		       //piso de la casa
CTexture puerta;	       //puerta de la casa
CTexture ventana;	       //ventana de la casa
CTexture vidrio;	       //parte transparente puerta y ventana
CTexture maderaclara;      //mesa
CTexture maderaobscura;    //patas de la mesa
CTexture closett;          //cara del closet
CTexture closetm;          //muro del closet
CTexture comodafrente;     //comoda frente 
CTexture comodapata;       //para de la comoda
CTexture portada;          //imagen de la TV
CTexture marco;            //marco de la TV
CTexture logo;             //logo de la TV
CTexture camabase;         //mdera base de la cama
CTexture camapataiz;       //pata izquierda de la cama
CTexture camapatader;      //pata derecha de la cama
CTexture camafrente;       //proteccion de enfrente de la cama
CTexture camacabe;         //cabecera de la cama
CTexture cabecerapataiz;   //pata de la cabecera de la cama IZ
CTexture cabecerapatader;  // pata de la cabecera de ña cama DER
CTexture colchonlado;      // lado del cochon
CTexture colchonlado2;     //lado del colchon corto
CTexture colchonbase;      //frente del colchon
CTexture metal;            //metal para la lampara
CTexture metal1;           //metal para el ventilador
CTexture tela;             //pantalla de la lampara
CTexture nave;             //Nave espacial
CTexture astronauta;       //Astronauta de la nave
CTexture tela1;            //tela del sillon
CTexture sillaT;           //silla
CTexture tree;             //arbusto
CTexture tree2;            //arbusto
CTexture tree3;            //arbol
CTexture tree4;            //arbol
CTexture tree1;            //arbol
CTexture camino;           //camino a fuera de la casa

//figuras para los  modelos 
CFiguras fig1;
CFiguras fig2;

//Animación de la pantalla
float des = 0.0;

//Animación del ventilador 
float giro = 0.0;

// Animacion de la Nave-------------------------------------------
float naveX = -20;      //POS X DE LA NAVE
float naveY = 132.0;    //POS Y DE LA NAVE
float naveZ = -30.0;    //POS Z DE LA NAVE
float naverot = -90.0;  //ANGULO DE ROTACION DE LA NAVE
float portalR = 0.0;    //RADIO DEL PORTAL
float astLAR = 0.0;     //ALTURA DEL ASTRONAUTA
float astroX = 110.0;    //LARGO DEL ASTRONAUTA
float astroY = 17.0;    //ALTURA DEL PORTAL


bool naveACT = false;  //ESTADOS DE LA NAVE
bool nave1 = true;
bool nave2 = false;
bool nave3 = false;
bool nave4 = false;
bool nave5 = false;
bool nave6 = false;
bool nave7 = false;
bool nave8 = false;
bool nave9 = false;
bool nave10 = false;
bool nave11 = false;

// VARIBLES DE LA CAMARA PARA LAS VISTAS
float posX = -16.46;
float posY = 4.59;
float posZ = 15.0;
float view_x = -16.67;
float view_y = 4.59;
float view_z = -12.0;
float up_X = 0;
float up_Y = 1;
float up_Z = 0;


void InitGL ( GLvoid )                                  // Inicializamos parametros
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);				// Negro de fondo	

	glEnable(GL_TEXTURE_2D);                            //HABILITA LA CARGA DE TEXTURAS

	glShadeModel (GL_SMOOTH);
	glLightfv(GL_LIGHT1, GL_POSITION, Position);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, Diffuse);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glEnable ( GL_COLOR_MATERIAL );

	glClearDepth(1.0f);									// Configuramos Depth Buffer
	glEnable(GL_DEPTH_TEST);							// Habilitamos Depth Testing
	glDepthFunc(GL_LEQUAL);								// Tipo de Depth Testing a realizar
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);

	/* setup blending */
	glEnable(GL_BLEND);			// Turn Blending On
    
	// CARGA DE LAS TEXTURAS DE LOS POLIGONOS

    cielo.LoadBMP("texturas/cielo.bmp");   //LECTURA DEL ARCHIVO 
	cielo.BuildGLTexture();                //CRECION DE LA TEXTURA
	cielo.ReleaseImage();                  //BORRADO DE LA TEXTURA AL FINALIZAR

	pasto.LoadTGA("texturas/pasto.tga");
	pasto.BuildGLTexture();
	pasto.ReleaseImage();

	muro.LoadTGA("texturas/muro.tga");
	muro.BuildGLTexture();
	muro.ReleaseImage();

	techo.LoadTGA("texturas/techo.tga");
	techo.BuildGLTexture();
	techo.ReleaseImage();

	columna.LoadTGA("texturas/columna.tga");
	columna.BuildGLTexture();
	columna.ReleaseImage();

	piso.LoadTGA("texturas/piso.tga");
	piso.BuildGLTexture();
	piso.ReleaseImage();

	puerta.LoadTGA("texturas/puerta.tga");
	puerta.BuildGLTexture();
	puerta.ReleaseImage();
	
	ventana.LoadTGA("texturas/ventana.tga");
	ventana.BuildGLTexture();
	ventana.ReleaseImage();
	
	vidrio.LoadTGA("texturas/vidrio.tga");
	vidrio.BuildGLTexture();
	vidrio.ReleaseImage();

	maderaclara.LoadTGA("texturas/maderaclara.tga");
	maderaclara.BuildGLTexture();
	maderaclara.ReleaseImage();

	maderaobscura.LoadTGA("texturas/maderaobs.tga");
	maderaobscura.BuildGLTexture();
	maderaobscura.ReleaseImage();

	closett.LoadTGA("texturas/closet.tga");
	closett.BuildGLTexture();
	closett.ReleaseImage();

	closetm.LoadTGA("texturas/closetmuro.tga");
	closetm.BuildGLTexture();
	closetm.ReleaseImage();

	comodafrente.LoadTGA("texturas/comodafrente.tga");
	comodafrente.BuildGLTexture();
	comodafrente.ReleaseImage();

	comodapata.LoadTGA("texturas/comodapata.tga");
	comodapata.BuildGLTexture();
	comodapata.ReleaseImage();

	portada.LoadTGA("texturas/portada.tga");
	portada.BuildGLTexture();
	portada.ReleaseImage();

	marco.LoadBMP("texturas/marco.bmp");
	marco.BuildGLTexture();
	marco.ReleaseImage();

	logo.LoadTGA("texturas/logo.tga");
	logo.BuildGLTexture();
	logo.ReleaseImage();

	camabase.LoadTGA("texturas/camabase.tga");
	camabase.BuildGLTexture();
	camabase.ReleaseImage();

	camapataiz.LoadTGA("texturas/camapataiz.tga");
	camapataiz.BuildGLTexture();
	camapataiz.ReleaseImage();

	camapatader.LoadTGA("texturas/camapatader.tga");
	camapatader.BuildGLTexture();
	camapatader.ReleaseImage();

	camafrente.LoadTGA("texturas/camafrente.tga");
	camafrente.BuildGLTexture();
	camafrente.ReleaseImage();

	camacabe.LoadTGA("texturas/camacabe.tga");
	camacabe.BuildGLTexture();
	camacabe.ReleaseImage();

	cabecerapataiz.LoadTGA("texturas/cabecerapataiz.tga");
	cabecerapataiz.BuildGLTexture();
	cabecerapataiz.ReleaseImage();

	cabecerapatader.LoadTGA("texturas/cabecerapatader.tga");
	cabecerapatader.BuildGLTexture();
	cabecerapatader.ReleaseImage();

	colchonlado.LoadTGA("texturas/colchonlado.tga");
	colchonlado.BuildGLTexture();
	colchonlado.ReleaseImage();

	colchonlado2.LoadTGA("texturas/colchonlado2.tga");
	colchonlado2.BuildGLTexture();
	colchonlado2.ReleaseImage();

	colchonbase.LoadTGA("texturas/colchonbase.tga");
	colchonbase.BuildGLTexture();
	colchonbase.ReleaseImage();

	metal.LoadTGA("texturas/metal.tga");
	metal.BuildGLTexture();
	metal.ReleaseImage();

	metal1.LoadTGA("texturas/metal1.tga");
	metal1.BuildGLTexture();
	metal1.ReleaseImage();

	tela.LoadTGA("texturas/tela.tga");
	tela.BuildGLTexture();
	tela.ReleaseImage();

	astronauta.LoadTGA("texturas/astronauta.tga");
	astronauta.BuildGLTexture();
	astronauta.ReleaseImage();

	nave.LoadTGA("texturas/nave.tga");
	nave.BuildGLTexture();
	nave.ReleaseImage();

	sillaT.LoadTGA("texturas/silla.tga");
	sillaT.BuildGLTexture();
	sillaT.ReleaseImage();

	tela1.LoadTGA("texturas/tela1.tga");
	tela1.BuildGLTexture();
	tela1.ReleaseImage();

	camino.LoadTGA("texturas/camino.tga");
	camino.BuildGLTexture();
	camino.ReleaseImage();
		
	tree.LoadTGA("texturas/arbol.tga");
	tree.BuildGLTexture();
	tree.ReleaseImage();
	
	tree1.LoadTGA("texturas/arbol2.tga");
	tree1.BuildGLTexture();
	tree1.ReleaseImage();
	
	tree2.LoadTGA("texturas/arbol3.tga");
	tree2.BuildGLTexture();
	tree2.ReleaseImage();
	
	tree3.LoadTGA("texturas/arbol4.tga");
	tree3.BuildGLTexture();
	tree3.ReleaseImage();

	objCamera.Position_Camera(posX, posY, posZ, view_x, view_y, view_z, up_X, up_Y, up_Z);

}

//  Funciones para los muebles


void mesa()
{
	glPushMatrix();
		glDisable(GL_LIGHTING);
		glTranslatef(-40.5, 6.0, -35.5);
		fig1.prismaM(1.0, 28.0, 13.0, maderaclara.GLindex, maderaclara.GLindex); //tabla superior
		glPushMatrix();
			glTranslatef(-10.0, -5.2, 5.0);
			fig1.prismaM(9.35, 1.5, 1.0, maderaobscura.GLindex, maderaobscura.GLindex); //Pata Derecha 1
			glPushMatrix();
				glTranslatef(0.0, -4.18, -5.0);
				fig1.prismaM(1.0, 1.5, 9.0, maderaobscura.GLindex, maderaobscura.GLindex); //Union Derecha
			glPopMatrix();
		glPopMatrix();

	glPushMatrix();
		glTranslatef(-10.0, -5.2, -5.0);
		fig1.prismaM(9.35, 1.5, 1.0, maderaobscura.GLindex, maderaobscura.GLindex);//Pata Derecha 2
	glPopMatrix();

	glPushMatrix();
		glTranslatef(10.0, -5.2, 5.0);
		fig1.prismaM(9.35, 1.5, 1.0, maderaobscura.GLindex, maderaobscura.GLindex);//Pata Izquierda 1
		glPushMatrix();
			glTranslatef(0.0, -4.18, -5.0);
			fig1.prismaM(1.0, 1.5, 9.0, maderaobscura.GLindex, maderaobscura.GLindex); //Union Izquierda
		glPopMatrix();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(10.0, -5.2, -5.0);
		fig1.prismaM(9.35, 1.5, 1.0, maderaobscura.GLindex, maderaobscura.GLindex);//Pata Izquierda 2
	glPopMatrix();
	glEnable(GL_LIGHTING);
	glPopMatrix();
}
void mesa_centro()
{
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glScalef(0.5, 0.5, 0.5);
	glTranslatef(-60.5, 2.1, -5.5);
	glPushMatrix();
	glTranslatef(0.0, -0.3, 0.0);
	fig1.prismaM(1.5, 11.0, 18.5, metal1.GLindex, metal1.GLindex); //tabla superior
	glPopMatrix();
	

	glRotatef(90.0, 0.0, 1.0, 0.0);
	glPushMatrix();
	glTranslatef(-10.0, -5.2, 5.0);
	fig1.prismaM(9.35, 1.5, 1.0, maderaclara.GLindex, maderaclara.GLindex); //Pata Derecha 1
	glPushMatrix();
	glTranslatef(0.0, -4.18, -5.0);
	fig1.prismaM(1.0, 1.5, 9.0, maderaclara.GLindex, maderaclara.GLindex); //Union Derecha
	glPushMatrix();
	glTranslatef(0.0, 9.35, 0.0);
	fig1.prismaM(1.0, 1.5, 11.0, maderaclara.GLindex, maderaclara.GLindex); //Union Derecha
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-10.0, -5.2, -5.0);
	fig1.prismaM(9.35, 1.5, 1.0, maderaclara.GLindex, maderaclara.GLindex);//Pata Derecha 2
	glPopMatrix();

	glPushMatrix();
	glTranslatef(10.0, -5.2, 5.0);
	fig1.prismaM(9.35, 1.5, 1.0, maderaclara.GLindex, maderaclara.GLindex);//Pata Izquierda 1
	glPushMatrix();
	glTranslatef(0.0, -4.18, -5.0);
	fig1.prismaM(1.0, 1.5, 9.0, maderaclara.GLindex, maderaclara.GLindex); //Union Izquierda
	glPushMatrix();
	glTranslatef(0.0, 9.35, 0.0);
	fig1.prismaM(1.0, 1.5, 11.0, maderaclara.GLindex, maderaclara.GLindex); //Union Izquierda

	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(10.0, -5.2, -5.0);
	fig1.prismaM(9.35, 1.5, 1.0, maderaclara.GLindex, maderaclara.GLindex);//Pata Izquierda 2
	glPopMatrix();
	glEnable(GL_LIGHTING);
	glPopMatrix();
}
void closet()
{
	glPushMatrix();
		glDisable(GL_LIGHTING);
		glTranslatef(41, 12.6 , -40.5);
		fig1.prismaM(33, 28, 4, closett.GLindex, closetm.GLindex);
		glEnable(GL_LIGHTING);
	glPopMatrix();
}
void silla()
{
	glPushMatrix();
	glDisable(GL_LIGHTING);
		glTranslatef(-20.0, 3.6, -35.0);
		glRotatef(-45, 0.0, 1.0, 0.0);
		fig1.prismaM(0.1, 5.0, 4.0, sillaT.GLindex, sillaT.GLindex);//asiento
		glPushMatrix();
			glTranslatef(-2.0, -1.0, -2.5);
			fig1.prismaM(13.0, 1.0, 1.0, sillaT.GLindex, sillaT.GLindex); //pata tracera iz
		glPopMatrix();

		glPushMatrix();
			glTranslatef(2.0, -1.0, -2.5);
			fig1.prismaM(13.0, 1.0, 1.0, sillaT.GLindex, sillaT.GLindex);//pata tracera der
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-2.0, -3.775, 1.5);
			fig1.prismaM(7.45, 1.0, 1.0, sillaT.GLindex, sillaT.GLindex); //pata delantera iz	
		glPopMatrix();
		
		glPushMatrix();
			glTranslatef(2.0, -3.775, 1.5);
			fig1.prismaM(7.45, 1.0, 1.0, sillaT.GLindex, sillaT.GLindex); //pata delantera der
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-2.0, -0.55, -0.5);
			fig1.prismaM(1.0, 0.8, 3.0, sillaT.GLindex, sillaT.GLindex); //asiento proteccion iz
			glPushMatrix();
				glTranslatef(0, -4, 0);
				fig1.prismaM(0.5, 0.4, 3.0, sillaT.GLindex, sillaT.GLindex); //asiento proteccion iz bajo
			glPopMatrix();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(2.0, -0.55, -0.5);
			fig1.prismaM(1.0, 0.8, 3.0, sillaT.GLindex, sillaT.GLindex); //asiento proteccion der
			glPushMatrix();
				glTranslatef(0, -4, 0);
				fig1.prismaM(0.5, 0.4, 3.0, sillaT.GLindex, sillaT.GLindex); //asiento proteccion der bajo
			glPopMatrix();
		glPopMatrix();
		
		glPushMatrix();
			glTranslatef(0.0, -0.55, 1.5);
			fig1.prismaM(1.0, 3.0, 0.8, sillaT.GLindex, sillaT.GLindex); //asiento proteccion frente
			glPushMatrix();
				glTranslatef(0, -2.0, 0.2);
				fig1.prismaM(0.5, 3.0, 0.4, sillaT.GLindex, sillaT.GLindex); //asiento proteccion frente bajo
			glPopMatrix();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0.0, -0.55, -1.6);
			fig1.prismaM(1.0, 3.0, 0.8, sillaT.GLindex, sillaT.GLindex); //asiento proteccion tracera
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0.0, 5.0, -2.5);
			fig1.prismaM(1.0, 3.0, 1.0, sillaT.GLindex, sillaT.GLindex); //respaldo 1
			glPushMatrix();
				glTranslatef(0.0, -1.5, 0.0);
				fig1.prismaM(1.0, 3.0, 1.0, sillaT.GLindex, sillaT.GLindex); //respaldo 2
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0.0, -3.0, 0.0);
				fig1.prismaM(1.0, 3.0, 1.0, sillaT.GLindex, sillaT.GLindex); //respaldo 3
			glPopMatrix();
		glPopMatrix();
	glEnable(GL_LIGHTING);
	glPopMatrix();
}
void comoda()
{
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glTranslatef(52.5, 1.1, 3.5);
	glRotatef(90,0.0, 1.0, 0.0);
	fig1.prismaM(8, 8, 5, comodafrente.GLindex, comodapata.GLindex);     //base comoda
		glPushMatrix();
			glTranslatef(3.5, -4.5, -2);
			fig1.prismaM(1, 1, 1, comodapata.GLindex, comodapata.GLindex); //Pata Delantera IZ
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-3.5, -4.5, 2);
			fig1.prismaM(1, 1, 1, comodapata.GLindex, comodapata.GLindex);//Pata Tracera DER
		glPopMatrix();
		glPushMatrix();
		glTranslatef(3.5, -4.5, 2);
		fig1.prismaM(1, 1, 1, comodapata.GLindex, comodapata.GLindex); //Pata Tracera IZ
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-3.5, -4.5, -2);
			fig1.prismaM(1, 1, 1, comodapata.GLindex, comodapata.GLindex);//Pata Delantera DER
		glPopMatrix();
	glEnable(GL_LIGHTING);
	glPopMatrix();
}
void pantalla()
{
	glPushMatrix();
	glDisable(GL_LIGHTING);
		glTranslatef(1,10, 5);
		glRotatef(90, 0.0, 1.0, 0.0);
		glColor3f(1, 1, 1);
		glBindTexture(GL_TEXTURE_2D, portada.GLindex);
		glBegin(GL_POLYGON);
			glNormal3f(0, 0, 1);
			glTexCoord2f(0 - des, 0); glVertex2f( 0,  0); //v1
			glTexCoord2f(1 - des, 0); glVertex2f(30,  0); //v2
			glTexCoord2f(1 - des, 1); glVertex2f(30, 15); //v3
			glTexCoord2f(0 - des, 1); glVertex2f( 0, 15); //v4
		glEnd();

		glPushMatrix();
			glTranslatef(7.375, -0.25, -0.5);
			glRotatef(180, 0.0, 1.0, 0.0);
			fig1.prismaM(0.5, 15.75, 1, marco.GLindex, marco.GLindex); // INFERIOR 1
			glPushMatrix();
				glTranslatef(-9.125, 0.0, 0.0);
				glRotatef(180, 0.0, 1.0, 0.0);
				fig1.prismaM(0.5, 2.5, 1.0, logo.GLindex, marco.GLindex); // INFERIOR 2
			glPopMatrix();
			glPushMatrix();
				glTranslatef(-16.75, 0.0, 0.0);
				glRotatef(180, 0.0, 1.0, 0.0);
				fig1.prismaM(0.5, 12.75, 1, marco.GLindex, marco.GLindex); // INFERIOR 3
			glPopMatrix();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(15, 15.25, -0.5);
			glRotatef(180, 0.0, 1.0, 0.0);
			fig1.prismaM(0.5, 31, 1, marco.GLindex, marco.GLindex);  // SUPERIOR
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-0.25, 7.5, -0.5);
			glRotatef(90, 0.0, 0.0, 1.0);
			fig1.prismaM(0.5, 15, 1, marco.GLindex, marco.GLindex); // IZQUIERDO
		glPopMatrix();
		glPushMatrix();
			glTranslatef(30.25, 7.5, -0.5);
			glRotatef(90, 0.0, 0.0, 1.0);
			fig1.prismaM(0.5, 15, 1, marco.GLindex, marco.GLindex);  //DERECHO
		glPopMatrix();
	glEnable(GL_LIGHTING);
	glPopMatrix();
}
void cama()
{
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glTranslatef(39, -0.41, -12);
	fig1.prismaM(2, 30, 20, camabase.GLindex, camabase.GLindex); // base de la cama

	glPushMatrix();
	glTranslatef(0.0, 2.75, 0);
	glRotatef(180, 0.0, 1.0, 0.0);
	fig1.prismaCOL(2.5, 30, 19, colchonlado.GLindex, colchonbase.GLindex, colchonlado2.GLindex); //colchon
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0.0, 1.25, -10.0);
	fig1.prismaM(0.5, 30, 1, camabase.GLindex, camabase.GLindex); //Proteccion IZ
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 1.25, 10.0);
	fig1.prismaM(0.5, 30, 1, camabase.GLindex, camabase.GLindex); //Proteccion DER
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-15.5, 1.05, 0.0);
	glRotatef(-90, 0.0, 1.0, 0.0);
	glRotatef(90, 1.0, 0.0, 0.0);
	fig1.prismaM(1.0, 19.0, 0.9, camabase.GLindex, camafrente.GLindex); //Proteccion Frente
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-15.5, -1.0, -10.0);
	glRotatef(-90, 0.0, 1.0, 0.0);
	fig1.prismaM(5, 1, 1, camapataiz.GLindex, camabase.GLindex); //Pata delantera IZ
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-15.5, -1.0, 10.0);
	glRotatef(-90, 0.0, 1.0, 0.0);
	fig1.prismaM(5, 1, 1, camapatader.GLindex, camabase.GLindex); //Pata delantera DER
	glPopMatrix();

	glPushMatrix();
		glTranslatef(15.5, -1.0, -10.0);
		glRotatef(-90, 0.0, 1.0, 0.0);
		fig1.prismaM(5, 1, 1, camabase.GLindex, camabase.GLindex); //Pata tracera IZ
		glPushMatrix();
			glTranslatef(0, 7.5, 0.0);
			fig1.prismaM(10, 1, 1, cabecerapataiz.GLindex, camabase.GLindex); //Pata cabecera IZ
		glPopMatrix();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(15.5, -1.0, 10.0);
		glRotatef(-90, 0.0, 1.0, 0.0);
		fig1.prismaM(5, 1, 1, camabase.GLindex, camabase.GLindex); //Pata tracera DER
		glPushMatrix();
			glTranslatef(0, 7.5, 0.0);
			fig1.prismaM(10, 1, 1, cabecerapatader.GLindex, camabase.GLindex); //Pata cabecera DER
		glPopMatrix();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(15.5, 5.6, 0.0);
		glRotatef(-90, 0.0, 1.0, 0.0);
		fig1.prismaM(8.1, 19.0, 1, camacabe.GLindex, camabase.GLindex); //Cabecera
		glPushMatrix();
			glTranslatef(0.0, 4.975, 0.0);
			glRotatef(90, 1.0, 0.0, 0.0);
			fig1.prismaM(1.0, 19.0, 1.85, camabase.GLindex, camafrente.GLindex); //Proteccion Frente cabecera
		glPopMatrix();	
	glPopMatrix();


	glEnable(GL_LIGHTING);
	glPopMatrix();
}
void lampara()
{
	glPushMatrix();
	glDisable(GL_LIGHTING);
		glTranslatef(52.5, 5.2, 34.5);
		fig1.prismaM(0.2, 2.0, 2.0, metal.GLindex, metal.GLindex); //base lampara
		glPushMatrix();
			glTranslatef(0.0, 0.1, 0.0);
			fig1.cilindro(0.15, 0.5, 50.0, metal.GLindex);         //base redonda lampara 1
			glPushMatrix();
				glTranslatef(0.0, 0.44, 0.0);
				fig1.cilindro(0.1, 1.3, 50.0, metal.GLindex);   //base redonda lampara 2
				glPushMatrix();
					glTranslatef(0.0, 3.3, 0.0);
					fig1.prismaCOL(4.0, 2.0, 2.0, tela.GLindex, tela.GLindex, tela.GLindex);  //panatalla de la lampara
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
	glEnable(GL_LIGHTING);
	glPopMatrix();
}
void ventilador()
{
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glTranslatef(-25, 34.0, -15.5);
	fig1.prismaM(0.1, 0.1, 0.1, metal.GLindex, metal.GLindex); //base lampara

	
	glPushMatrix();
	fig1.cilindro(2.0, 1.0, 50.0, metal1.GLindex);
	glPopMatrix();
	/***************************/
	glPushMatrix();
	glTranslatef(0.0, -3.0, 0.0);
	fig1.cilindro(0.5, 3.0, 50.0, metal1.GLindex);
	/*1*/	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -4.0, 0.0);
	fig1.cilindro(1.2, 1.0, 50.0, metal1.GLindex);
	/*2*/	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -5.0, 0.0);
	fig1.cilindro(2.0, 1.5, 50.0, metal1.GLindex);
	/*3*/	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -5.4, 0.0);
	fig1.cilindro(2.0, 0.2, 20.0, metal1.GLindex);
	/*4*/	glPopMatrix();

	glPushMatrix();
	glRotatef(0.0 + giro, 0.0, 1.0, 0.0);
	glTranslatef(-4.8, -5.1, 0.0);
	fig1.prismaM(0.2, 8.0, 1.0, camabase.GLindex, camabase.GLindex);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90.0 + giro, 0.0, 1.0, 0.0);
	glTranslatef(-4.8, -5.1, 0.0);
	fig1.prismaM(0.2, 8.0, 1.0, camabase.GLindex, camabase.GLindex);
	glPopMatrix();

	glPushMatrix();
	glRotatef(180.0 + giro, 0.0, 1.0, 0.0);
	glTranslatef(-4.8, -5.1, 0.0);
	fig1.prismaM(0.2, 8.0, 1.0, camabase.GLindex, camabase.GLindex);
	glPopMatrix();

	glPushMatrix();
	glRotatef(270.0 + giro, 0.0, 1.0, 0.0);
	glTranslatef(-4.8, -5.1, 0.0);
	fig1.prismaM(0.2, 8.0, 1.0, camabase.GLindex, camabase.GLindex);
	glPopMatrix();
	glEnable(GL_LIGHTING);
	glPopMatrix();
}
void sillon()
{
	glPushMatrix();

	glDisable(GL_LIGHTING);
	glTranslatef(-20.0, -3.39, -5.0);
	fig1.prismaM(1.0, 1.0, 1.0, maderaclara.GLindex, maderaclara.GLindex);//0

	glPushMatrix();
	glTranslatef(8.0, 0.0, 0.0);
	fig1.prismaM(1.0, 1.0, 1.0, maderaclara.GLindex, maderaclara.GLindex);//1
	glPopMatrix();

	glPushMatrix();
	glTranslatef(8.0, 0.0, 8.0);
	fig1.prismaM(1.0, 1.0, 1.0, maderaclara.GLindex, maderaclara.GLindex);//2
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.0, 8.0);
	fig1.prismaM(1.0, 1.0, 1.0, maderaclara.GLindex, maderaclara.GLindex);//3
	glPopMatrix();

	glPushMatrix();
	glTranslatef(4.0, 3.5, 0.0);
	fig1.prismaM(6.0, 10.0, 1.0, tela1.GLindex, tela1.GLindex);//patas izquierda
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(4.0, 3.5, 8.0);
	fig1.prismaM(6.0, 10.0, 1.0, tela1.GLindex, tela1.GLindex);//patas derecha
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(3.5, 1.0, 4.0);
	fig1.prismaM(1.0, 9.0, 7.0, tela1.GLindex, tela1.GLindex);//patas baja
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(3.5, 1.5, 4.0);
	fig1.prismaM(0.01, 9.0, 7.0, maderaobscura.GLindex, maderaobscura.GLindex);//patas baja
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3.5, 2.52, 4.0);
	fig1.prismaM(2.0, 9.0, 7.0, tela1.GLindex, tela1.GLindex);//patas baja
	glPopMatrix();

	glPushMatrix();
	glTranslatef(8.5, 4.5, 4.0);
	fig1.prismaM(8.0, 1.0, 7.0, tela1.GLindex, tela1.GLindex);//patas baja
	glPopMatrix();

	
	glEnable(GL_LIGHTING);
	glPopMatrix();
}
void arbol(GLuint text)
{
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glEnable(GL_ALPHA_TEST);
	//glDisable(GL_DEPTH_TEST);   // Turn Depth Testing Off
	glAlphaFunc(GL_GREATER, 0.1);
	//glEnable(GL_BLEND);     // Turn Blending On
	//glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, text);
	glBegin(GL_QUADS); //plano
	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0, 20.0, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0, 20.0, 0.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glRotatef(45, 0, 1, 0);
	glBegin(GL_QUADS); //plano
	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0, 20.0, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0, 20.0, 0.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glRotatef(-45, 0, 1, 0);
	glBegin(GL_QUADS); //plano
	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0, 20.0, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0, 20.0, 0.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glBegin(GL_QUADS); //plano
	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0, 20.0, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0, 20.0, 0.0);
	glEnd();
	glDisable(GL_ALPHA_TEST);
	//glDisable(GL_BLEND);        // Turn Blending Off
	//glEnable(GL_DEPTH_TEST);    // Turn Depth Testing On
	glEnable(GL_LIGHTING);

	glPopMatrix();
}

void display ( void )   // Creamos la funcion donde se dibuja
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glLoadIdentity();
	
	glPushMatrix();

		glRotatef(g_lookupdown,1.0f,0,0);

		gluLookAt(	objCamera.mPos.x,  objCamera.mPos.y,  objCamera.mPos.z,	
					objCamera.mView.x, objCamera.mView.y, objCamera.mView.z,	
					objCamera.mUp.x,   objCamera.mUp.y,   objCamera.mUp.z);
	
	

		glPushMatrix();		
			glPushMatrix(); //Creamos cielo
				glDisable(GL_LIGHTING);
				glTranslatef(0,60,0);
				fig1.skybox(350.0, 130.0, 250.0,cielo.GLindex,pasto.GLindex);
				glEnable(GL_LIGHTING);

				/*CUARTO1*/
				glTranslatef(-30.0, -44.9, 0.0);
			  glPushMatrix();
				glDisable(GL_LIGHTING);
				glPushMatrix();
					glTranslatef(0.0, 0.0, -45.0);
					glRotatef(90.0, 0.0, 1.0, 0.0);
					fig2.prismaC(40.0, 5.0, 60.0, muro.GLindex);//atras
				glPopMatrix();

				glPushMatrix();
					glTranslatef(-27.5, -3.95, 20.0);
					glRotatef(90.0, 0.0, 1.0, 0.0);
					fig2.prismaC(32.1, 5.0, 5.0, muro.GLindex);//frenteIZQ-INFER
				glPopMatrix();

				 glPushMatrix();
					glTranslatef(0.0, 18.26, 20.0);
					fig2.prismaC(3.6, 60.0, 5.0, muro.GLindex);//frente-SUP
				glPopMatrix();

				glPushMatrix();
					glTranslatef(-11.25, -15.0, 20.0);
					fig2.prismaC(10.0, 27.5, 5.0, muro.GLindex);//frente-INF
				glPopMatrix();

				glPushMatrix();
					glTranslatef(27.5, -4.0, 20.0);
					glRotatef(90.0, 0.0, 1.0, 0.0);
					fig2.prismaC(32.0, 5.0, 5.0, muro.GLindex);//frenteDER-INFER
				glPopMatrix();

				glPushMatrix();
					glTranslatef(5.0, -4.0, 20.0);
					fig2.prismaC(32.0, 5.0, 5.0, muro.GLindex);//frenteMEDIO	
				glPopMatrix();

				glPushMatrix();
					glTranslatef(27.5, 0.0, -12.5);
					fig2.prismaC(40.0, 5.0, 60.0, muro.GLindex);//derecha
				glPopMatrix();

				glPushMatrix();
					glTranslatef(-27.5, 0.0, -12.5);
					fig2.prismaC(40.0, 5.0, 60.0, muro.GLindex);//izquierda
				glPopMatrix();

				///TECHO FACHADA
				glPushMatrix();
					glTranslatef(0.0, 14.29, 20.0);
					glColor3f(1.0, 1.0, 1.0);
					fig2.prisma(4.4, 60.0, 5.0, techo.GLindex);//ATRAS
				glPopMatrix();

				glPushMatrix();
					glTranslatef(0.0, 14.29, 45.0);
					fig2.prisma(4.4, 60.0, 5.0, techo.GLindex);//FRENTE
				glPopMatrix();

				glPushMatrix();
					glTranslatef(32.5, 14.29, 32.5);
					fig2.prisma(4.4, 5.0, 30.0, techo.GLindex);//DERECHA
				glPopMatrix();

				glPushMatrix();
					glTranslatef(-27.5, 14.29, 32.5);
					fig2.prisma(4.4, 5.0, 20.0, techo.GLindex);//IZQUIERDA
				glPopMatrix();


				glPushMatrix();
					glTranslatef(2.5, 14.29, 32.5);
					fig2.prismaC(4.0, 55.0, 20.0, muro.GLindex);//ENMEDIO
				glPopMatrix();


				 glEnable(GL_LIGHTING);

				/*INICIO_CUARTO_DOS*/
				 glDisable(GL_LIGHTING);
				glPushMatrix();
					glTranslatef(60.0, 0.0, -45.0);
					glRotatef(90.0, 0.0, 1.0, 0.0);
					fig2.prismaC(40.0, 5.0, 60.0, muro.GLindex);//ATRAS
				glPopMatrix();

				glPushMatrix();
					glTranslatef(87.5, -4.0, 10.0);
					glRotatef(90.0, 0.0, 1.0, 0.0);
					fig2.prismaC(32.0, 5.0, 5.0, muro.GLindex);//FRENTEDERECHA
				glPopMatrix();

				glPushMatrix();
					glTranslatef(32.51, -4.0, 10.0);
					glRotatef(90.0, 0.0, 1.0, 0.0);
					fig2.prismaC(32.0, 5.0, 5.0, muro.GLindex);//FRENTEIZQUIERDA
				glPopMatrix();

				glPushMatrix();
					glTranslatef(60.0, -15.0, 10.0);
					fig2.prismaC(10.0, 50.0, 5.0, muro.GLindex);//FRENTEINFERIOR
				glPopMatrix();

				glPushMatrix();
					glTranslatef(60.0, 16.0, 10.0);
					fig2.prismaC(8.0, 60.0, 5.0, muro.GLindex);//FRENTESUPERIOR
				glPopMatrix();

				glPushMatrix();
					glTranslatef(87.5, 0.0, -17.5);
					fig2.prismaC(40.0, 5.0, 50.0, muro.GLindex);//DERECHA
				glPopMatrix();

				glPushMatrix();
					glTranslatef(60.0, 1.0, 10.0);
					fig2.prisma(22.0, 10.0, 5.0, columna.GLindex);//FRENTEMEDIO
				glPopMatrix();

				glPushMatrix();
					glTranslatef(27.5, 2.5, 40.0);
					fig2.prisma(45.0, 5.0, 5.0, columna.GLindex);//SOLO
				glPopMatrix();

				glPushMatrix();
					glTranslatef(0.0, 20.25, -12.50);
					fig2.prismaT(0.5, 60.01, 70.0, techo.GLindex, muro.GLindex);//TECHOIZQ
				glPopMatrix();

				glPushMatrix();
					glTranslatef(60.0, 20.25, -17.5);//
					fig2.prismaT(0.5, 60.01, 60.0, techo.GLindex, muro.GLindex);//TECHODER
				glPopMatrix();

				glPushMatrix();
					glTranslatef(0.0, -19.5, -12.5);
					glRotatef(180, 0.0, 0.0, 1.0);
					 fig2.prismaT(1.0, 50.0, 60.0, piso.GLindex, piso.GLindex);//PISODER
					 glPushMatrix();
						  glTranslatef(-57.5, 0.0, -5.0);                                       //PISOS DE LAS HABITACIONES
						  fig2.prismaT(1.0, 55.0, 50.0, piso.GLindex, piso.GLindex);//PISOIZQ
					 glPopMatrix();
					 glPushMatrix();
						  glTranslatef(-16.25, 0.0, 42.5);
						  fig2.prismaT(1.0, 17.5, 25, piso.GLindex, piso.GLindex);//ENTRADA
					 glPopMatrix();
					 glPushMatrix();
						  glTranslatef(-27.5, 0.0, 42.5);
						  fig2.prismaT(1.0, 5, 15, piso.GLindex, piso.GLindex);//ENTRADA ESPACIO
					glPopMatrix();
				glPopMatrix();
			  
				/*JARDINERA2*/
				glPushMatrix();
					glTranslatef(60.0, -19.5, 13.0);
					fig2.prisma(1.0, 60.0, 1.0, techo.GLindex);//JARDINERA_DERECHA_ATRAS
				glPopMatrix();

				glPushMatrix();
					glTranslatef(60.0, -19.5, 42.0);//42=Z
					fig2.prisma(1.0, 60.0, 1.0, techo.GLindex);//JARDINERA_DERECHA_FRENTE
				glPopMatrix();

				glPushMatrix();
					glTranslatef(30.5, -19.5, 27.5);//27.2=largo
					fig2.prisma(1.0, 1.0, 28.0, techo.GLindex);//JARDINERA_DERECHA_IZQ
				glPopMatrix();

				glPushMatrix();
					glTranslatef(89.5, -19.5, 27.5);//
					fig2.prisma(1.0, 1.0, 28.0, techo.GLindex);//JARDINERA_DERECHA_DER			  
				glPopMatrix();
			 
				/*JARDINERA 1*/
				glPushMatrix();
					glTranslatef(-11.25, -19.5, 23.0);
					fig2.prisma(1.0, 37.5, 1.0, techo.GLindex);//JARDINERA_IZQUIERDA_ATRAS
				glPopMatrix();
			  
				glPushMatrix();
					glTranslatef(-11.25, -19.5, 42.0);
					fig2.prisma(1.0, 37.5, 1.0, techo.GLindex);//JARDINERA_IZQUIERDA_FRENTE
				glPopMatrix();

				glPushMatrix();
					glTranslatef(7.0, -19.5, 32.5);
					fig2.prisma(1.0, 1.0, 18.0, techo.GLindex);//JARDINERA_DERECHA_DER
				glPopMatrix();

				glPushMatrix();
					glTranslatef(-29.5, -19.5, 32.5);
					fig2.prisma(1.0, 1.0, 18.0, techo.GLindex);//JARDINERA_DERECHA_IZQ
				glPopMatrix();

				glPushMatrix();
					glTranslatef(16.25, -3.5, 20);
					glEnable(GL_ALPHA_TEST);
					glAlphaFunc(GL_GREATER, 0.1);
					fig2.prismaV(31, 17.5, 5.0, puerta.GLindex, vidrio.GLindex);//PUERTA
					glDisable(GL_ALPHA_TEST);
					glPushMatrix();
						glTranslatef(-27.5, 4.55, 0.0);
						glEnable(GL_ALPHA_TEST);
						glAlphaFunc(GL_GREATER, 0.1);
						fig2.prismaV(22.08, 27.5, 5.0, ventana.GLindex, vidrio.GLindex);//VENTANA IZQUIERDA
						glDisable(GL_ALPHA_TEST);
					glPopMatrix();
				glPopMatrix();

				glPushMatrix();
					glTranslatef(45.0, 1.0, 10.0);
					glEnable(GL_ALPHA_TEST);
					glAlphaFunc(GL_GREATER, 0.1);
					fig2.prismaV(22.0, 19.99, 5.0, ventana.GLindex, vidrio.GLindex);//VENTANA DERECHA 1
					glDisable(GL_ALPHA_TEST);
					glPushMatrix();
						glTranslatef(30.0, 0.0, 0.0);
						glEnable(GL_ALPHA_TEST);
						glAlphaFunc(GL_GREATER, 0.1);
						fig2.prismaV(22.0, 19.99, 5.0, ventana.GLindex, vidrio.GLindex);//VENTANA DERECHA 2
						 glDisable(GL_ALPHA_TEST);
					glPopMatrix();
				glPopMatrix();
			 
				glEnable(GL_LIGHTING);
			glPopMatrix();
		glPopMatrix();
			/*FIN CUARTO*/

			
			//MUEBLES DE LA RECAMARA
			glPushMatrix();
				closet();
				comoda();
				pantalla();
				cama();
				glTranslatef(0, 0.0, -31);
				comoda();
				lampara();
				glTranslatef(0, 0.0, -62);
				lampara();
			glPopMatrix();

			//MUEBLES DE LA SALA
			glPushMatrix();
				mesa();
				ventilador();
				silla();
				mesa_centro();
				sillon();
				glRotatef(90.0, 0.0, 1.0, 0.0);
				glTranslatef(35.0, 0.0, -30.0);
				sillon();
			glPopMatrix();
			///////////////////////////////////////////////////////////////////////////////////
			///////////////////////////////////////////////////////////////////////////////////
			///////////////////////////////////////////////////////////////////////////////////
			///////////////////////////////////////////////////////////////////////////////////
			///////////////////////////////////////////////////////////////////////////////////
			/////////////////////////////////////////  arboles   //////////////////////////////
			///////////////////////////////////////////////////////////////////////////////////
			///////////////////////////////////////////////////////////////////////////////////
			///////////////////////////////////////////////////////////////////////////////////
			///////////////////////////////////////////////////////////////////////////////////
			///////////////////////////////////////////////////////////////////////////////////
			
			glPushMatrix();
				glTranslatef(-120.0, -5.0, -70.0);
				glScalef(2.5, 5.0, 2.5);
				arbol(tree.GLindex);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-130.0, -5.0, -20.0);
				glScalef(2.5, 5.0, 2.5);
				arbol(tree.GLindex);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-90.0, -5.0, 10.0);
				glScalef(2.5, 5.0, 2.5);
				arbol(tree.GLindex);
			glPopMatrix();
			
			glPushMatrix();
				glTranslatef(-130.0, -5.0, 20.0);
				glScalef(2.5, 5.0, 2.5);
				arbol(tree.GLindex);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-100.0, -5.0, -40.0);
				glScalef(2.5, 5.0, 2.5);
				arbol(tree.GLindex);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-50.0, -5.5, 40.0);
				glScalef(0.5, 0.5, 0.5);
				arbol(tree2.GLindex);
			glPopMatrix();
			
			glPushMatrix();
				glTranslatef(-40.0, -5.5, 40.0);
				glScalef(0.5, 0.5, 0.5);
				arbol(tree2.GLindex);
			glPopMatrix();
			
			glPushMatrix();
				glTranslatef(-30.0, -5.5, 40.0);
				glScalef(0.5, 0.5, 0.5);
				arbol(tree2.GLindex);
			glPopMatrix();
			
			glPushMatrix();
				glTranslatef(50.0, -5.5, 40.0);
				glScalef(0.5, 0.5, 0.5);
				arbol(tree2.GLindex);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-50.0, -5.5, 30.0);
				glScalef(0.5, 0.5, 0.5);
				arbol(tree2.GLindex);
			glPopMatrix();
			
			glPushMatrix();
				glTranslatef(-40.0, -5.5, 30.0);
				glScalef(0.5, 0.5, 0.5);
				arbol(tree2.GLindex);
			glPopMatrix();
			
			glPushMatrix();
				glTranslatef(-30.0, -5.5, 30.0);
				glScalef(0.5, 0.5, 0.5);
				arbol(tree2.GLindex);
			glPopMatrix();
			
			glPushMatrix();
				glTranslatef(50.0, -5.5, 30.0);
				glScalef(0.5, 0.5, 0.5);
				arbol(tree2.GLindex);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(20.0, -5.5, 40.0);
				glScalef(0.5, 0.5, 0.5);
				arbol(tree2.GLindex);
			glPopMatrix();
			
			glPushMatrix();
				glTranslatef(30.0, -5.5, 40.0);
				glScalef(0.5, 0.5, 0.5);
				arbol(tree2.GLindex);
			glPopMatrix();
			
			glPushMatrix();
				glTranslatef(10.0, -5.5, 40.0);
				glScalef(0.5, 0.5, 0.5);
				arbol(tree2.GLindex);
			glPopMatrix();
			
			glPushMatrix();
				glTranslatef(40.0, -5.5, 40.0);
				glScalef(0.5, 0.5, 0.5);
				arbol(tree2.GLindex);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(20.0, -5.5, 20.0);
				glScalef(0.5, 0.5, 0.5);
				arbol(tree2.GLindex);
			glPopMatrix();
			
			glPushMatrix();
				glTranslatef(30.0, -5.5, 20.0);
				glScalef(0.5, 0.5, 0.5);
				arbol(tree2.GLindex);
			glPopMatrix();
			
			glPushMatrix();
				glTranslatef(10.0, -5.5, 30.0);
				glScalef(0.5, 0.5, 0.5);
				arbol(tree2.GLindex);
			glPopMatrix();
			
			glPushMatrix();
				glTranslatef(40.0, -5.5, 20.0);
				glScalef(0.5, 0.5, 0.5);
				arbol(tree2.GLindex);
			glPopMatrix();
			
			glPushMatrix();
				glTranslatef(10.0, -5.5, 20.0);
				glScalef(0.5, 0.5, 0.5);
				arbol(tree2.GLindex);
			glPopMatrix();
			
			glPushMatrix();
				glTranslatef(50.0, -5.5, 20.0);
				glScalef(0.5, 0.5, 0.5);
				arbol(tree2.GLindex);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(30.0, -6.2, 30.0);
				glScalef(1.5, 1.5, 1.5);
				arbol(tree1.GLindex);
			glPopMatrix();
			/////////////////////////////////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////////////////////
			//////////////////////////// ANIMACION COMPLEJA /////////////////////////////////

			glPushMatrix();
				glDisable(GL_LIGHTING);
				glTranslatef(naveX, naveY, naveZ);
				glRotatef(naverot, 0.0, 0.0, 1.0);
				glEnable(GL_ALPHA_TEST);
				glAlphaFunc(GL_GREATER, 0.1);
				fig2.prismaCOL(50.0, 20.0, 0.1, nave.GLindex, vidrio.GLindex, vidrio.GLindex); //NAVE
				glDisable(GL_ALPHA_TEST);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(astroX, astroY, -30.0);
				glEnable(GL_ALPHA_TEST);
				glAlphaFunc(GL_GREATER, 0.1);
				fig2.prismaCOL(20.0, astLAR, 0.1, astronauta.GLindex, vidrio.GLindex, vidrio.GLindex); //ASTRONAUTA
				glDisable(GL_ALPHA_TEST);
				glEnable(GL_LIGHTING);
			glPopMatrix();

			glPushMatrix();
			glDisable(GL_LIGHTING);
				glTranslatef(114.0, 16.0, -30.0);
				glRotatef(90, 0.0, 0.0, 1.0);
				fig1.cono(20, portalR, 50.0, techo.GLindex);  //PORTAL
			glEnable(GL_LIGHTING);
			glPopMatrix();

			glPushMatrix();
			glDisable(GL_LIGHTING);
				glTranslatef(0, -4.75, 57.5);
				fig1.prismaCamino(0.5, 350, 30, camino.GLindex);     //Camino largo
				glPushMatrix();
					glTranslatef(-38.0, 0, 41.25);
					glRotatef(180, 0.0, 0.0, 1.0);
					fig1.prismaCamino(0.5, 30, 52.5, camino.GLindex);  //Camino corto
				glPopMatrix();
			glEnable(GL_LIGHTING);
			glPopMatrix();			
	glPopMatrix();		
	glutSwapBuffers ( );

}

void animacion()
{
	glutPostRedisplay();
	des += 0.0010;
	giro += 1;

	// Animacion de la nave
	if (naveACT)
	{
		if (nave1)
		{
			naveY -= 0.1;
			naveX += 0.2;
			if (naveX > 91)
			{
				nave1 = false;
				nave2 = true;
			}
		}
		if (nave2)
		{
			naverot+= 0.5;
			if (naverot > 0)
			{
				nave2 = false;
				nave3 = true;
			}
		}
		if (nave3)
		{
			naveY -= 0.1;
			if (naveY < 18)
			{
				nave3 = false;
				nave4 = true;
			}
		}
		if (nave4)
		{
			portalR += 0.02;
			if (portalR > 16)
			{
				nave4 = false;
				nave5 = true;
			}
		}if (nave5)
		{
			astLAR += 0.1;
			astroX += 0.1;
			if (astLAR > 15)
			{
				portalR = 0.0;
				nave5 = false;
				nave6 = true;
			}
		}if (nave6)

		{
			astroY += 0.1;
			if (astroY > 40)
			{
				nave6 = false;
				nave7 = true;
			}
		}if (nave7)

		{
			astroY -= 0.1;
			if (astroY < 17)
			{
				nave7 = false;
				nave8 = true;
			}
		}if (nave8)
		{
			portalR += 0.02;
			if (portalR > 16)
			{
				nave8 = false;
				nave9 = true;
			}
		}if (nave9)
		{
			astroX -= 0.1;
			if (astroX < 110)
			{
				astLAR = 0.0;
				portalR = 0.0;
				nave9 = false;
				nave10 = true;
			}
		}if (nave10)
		{
			naveY += 0.1;
			if (naveY > 150)
			{
				naveX = -20;
				naveY = 132.0;
				naveZ = -30.0;
				naverot = -90.0;
				nave10 = false;
				nave1 = true;
			}
		}
	}
}


void reshape ( int width , int height )   // Creamos funcion Reshape
{
  if (height==0)										// Prevenir division entre cero
	{
		height=1;
	}

	glViewport(0,0,width,height);	

	glMatrixMode(GL_PROJECTION);						// Seleccionamos Projection Matrix
	glLoadIdentity();

	// Tipo de Vista
	
	glFrustum (-0.1, 0.1,-0.1, 0.1, 0.1, 400.0);

	glMatrixMode(GL_MODELVIEW);							// Seleccionamos Modelview Matrix
	glLoadIdentity();
}

void keyboard ( unsigned char key, int x, int y )  // Create Keyboard Function
{
	switch (key) {
	case 'w':   //Movimientos de camara
	case 'W':
		objCamera.Move_Camera(CAMERASPEED + 0.1);
		break;

	case 's':
	case 'S':
		objCamera.Move_Camera(-(CAMERASPEED + 0.1));
		break;

	case 'a':
	case 'A':
		objCamera.Strafe_Camera(-(CAMERASPEED + 0.1));
		break;

	case 'd':
	case 'D':
		objCamera.Strafe_Camera(CAMERASPEED + 0.1);
		break;

			/*vista sala*/
		case 'r':
		case 'R':
			objCamera.mPos.x = -52.88;
			objCamera.mPos.y = 25.60;
			objCamera.mPos.z = 18.53;
			objCamera.mView.x = -50.94;
			objCamera.mView.y = 25.60;
			objCamera.mView.z = 16.23;
			objCamera.mUp.x = 0.0;
			objCamera.mUp.y = 1.0;
			objCamera.mUp.z = 0.0;
			g_lookupdown = 37.0;

			break;
			/*vista cuarto*/
		case 't':
		case 'T':
			objCamera.mPos.x = 54.59;
			objCamera.mPos.y = 25.60;
			objCamera.mPos.z = 4.77;
			objCamera.mView.x = 52.39;
			objCamera.mView.y = 25.60;
			objCamera.mView.z = 2.73;
			objCamera.mUp.x = 0.0;
			objCamera.mUp.y = 1.0;
			objCamera.mUp.z = 0.0;
			g_lookupdown = 15.0;

			break;
			/*vista aerea */
		case 'e':
		case 'E':	

			objCamera.mPos.x = -2.92;
			objCamera.mPos.y = 20.79;
			objCamera.mPos.z = 98.53;
			objCamera.mView.x = -2.92;
			objCamera.mView.y = 20.79;
			objCamera.mView.z = 95.53;
			objCamera.mUp.x = 0.0;
			objCamera.mUp.y = 1.0;
			objCamera.mUp.z = 0.0;
			g_lookupdown = 15.0;
			break;
		
		case ' ':
			//objCamera.Position_Camera(-17.5, 2.5, 21.04, -17.5, 2.5, -14.05, 0.0, 1.0, 0.0);
			printf("\n\tmPosX=%f ,mPosY=%f,mPosZ=%f \n\n\tmViewX=%f,mViewY=%f,mViewZ=%f \n\n\tmUpX=%f,mUpY=%f,mUpZ=%f\n", objCamera.mPos.x, objCamera.mPos.y, objCamera.mPos.z,
				objCamera.mView.x, objCamera.mView.y, objCamera.mView.z, objCamera.mUp.x, objCamera.mUp.y, objCamera.mUp.z);
			printf("\n\tmPosX=%f ", g_lookupdown);
			break;

		case 'n':
		case 'N':
			naveACT^= true;
			break;

		case 27:        // Cuando Esc es presionado...
			exit ( 0 );   // Salimos del programa
			break;        
		default:        // Cualquier otra
			break;
  }

  glutPostRedisplay();
}

void arrow_keys ( int a_keys, int x, int y )  // Funcion para manejo de teclas especiales (arrow keys)
{
  switch ( a_keys ) {
	case GLUT_KEY_PAGE_UP:
		objCamera.UpDown_Camera(CAMERASPEED);
		break;

	case GLUT_KEY_PAGE_DOWN:
		objCamera.UpDown_Camera(-CAMERASPEED);
		break;

    case GLUT_KEY_UP:     // Presionamos tecla ARRIBA...
		g_lookupdown -= 1.0f;
		break;

    case GLUT_KEY_DOWN:               // Presionamos tecla ABAJO...
		g_lookupdown += 1.0f;
		break;

	case GLUT_KEY_LEFT:
		objCamera.Rotate_View(-CAMERASPEED);
		break;

	case GLUT_KEY_RIGHT:
		objCamera.Rotate_View( CAMERASPEED);
		break;

    default:
		break;
  }
  glutPostRedisplay();
}


int main ( int argc, char** argv )   // Main Function
{
  PlaySound(TEXT("Soundtrack/TLoU.wav"), NULL, SND_ASYNC | SND_LOOP);
  glutInit            (&argc, argv); // Inicializamos OpenGL
  glutInitDisplayMode (GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); // Display Mode (Clores RGB y alpha | Buffer Doble )
  glutInitWindowSize  (900, 900);	// Tamaño de la Ventana
  glutInitWindowPosition (0, 0);	//Posicion de la Ventana
  glutCreateWindow    ("Proyecto Final"); // Nombre de la Ventana
  //glutFullScreen     ( );         // Full Screen
  InitGL ();						// Parametros iniciales de la aplicacion
  glutDisplayFunc     ( display );  //Indicamos a Glut función de dibujo
  glutReshapeFunc     ( reshape );	//Indicamos a Glut función en caso de cambio de tamano
  glutKeyboardFunc    ( keyboard );	//Indicamos a Glut función de manejo de teclado
  glutSpecialFunc     ( arrow_keys );	//Otras
  glutIdleFunc		  ( animacion );
  glutMainLoop        ( );          // 

  return 0;
}
