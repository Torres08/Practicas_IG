/*
				D U C K
	I.G.						Curso 2021-2022

	Dpto. Lenguajes y Sistemas Informáicos
	E.T.S.I. Informáica
	Univ. de Granada

       Tema4. Interacción

        Objetivo: Este programa muestra los mecanismos de seleccion de OpenGL
	
*/
#include <math.h>
#include <GL/glut.h>                   // Libreria de utilidades de OpenGL
#include <stdio.h>
#include <stdlib.h>

/*  ============================== Modelo geometrico ============
 Lista de patos. Cada pato almacena:
 				su posición
 				su orientacón
				su color
				su velocidad
				si esta girando
				el Águlo en el que estan sus patas,
				si las está moviendo
				el Águlo de su cabeza
				si la está moviendo
				el águlo de su pico
				si lo está moviendo
*/
typedef struct {
	float x;
	float z;
	float angulo;
	float color;				// de 0 a 1. -1 es una marca de borrado
	float velocidadX;
	float velocidadZ;
	float velocidadGiro;
	float anguloPatas; 
	float velocidadPatas;
	float anguloCabeza;
	float velocidadCabeza;
	float anguloPico;
	float velocidadPico;
		} duck;
int uodate=1;
#define MAXPATOS 4 		// 21 patos son demasiados !!

typedef enum {PatoId, PatasId, CabezaId, PicoId} nombres ;

int contador=0;		// Para medir tiempo de salida entre patos
static float viewX, viewY;      // Tamño del viewport (ventanaX) en pixels
static float vofx=0.0,vofy=0.0;          // Desplazamiento ventana


duck pato[MAXPATOS];
int npatos=0;		// numero de patos

float XC,YC;			// útima posición conocida del cursor (coor. normalizadas

float D=22.0;                          // Distancia de la camara al modelo
static GLfloat view_rotx=20.0, view_roty=0.0, view_rotz=0.0;

int crearPato()
// Rellena la estructura pato para un nuevo pato. Devuelve el identificador
{
int i;
// Buscar si hay algun registro con borrado lógico
i=0;
while(i<npatos && pato[i].color!=-1)
	++i;
if(i==npatos && npatos<MAXPATOS) npatos++;	// No hay. Se añade al final
if(i==MAXPATOS) return -1;		// No caben mas !
// Tenemos un nuevo pato en el registro i

pato[i].x = 5;
pato[i].z=9;
// Decidimos la dirección de entrada en función de la posicón del cursor

pato[i].color= 0;
pato[i].velocidadX =0.05;
pato[i].velocidadZ = -0.05;
pato[i].angulo=atan2(-pato[i].velocidadX,-pato[i].velocidadZ)*180.0/3.14159;
pato[i].velocidadGiro=0;
pato[i].anguloPatas=0;
pato[i].anguloCabeza=0;
pato[i].anguloPico=0;
pato[i].velocidadPatas =8.0;
pato[i].velocidadPico =5.0;
pato[i].velocidadCabeza =2.0;


return i;
}

void ColorSeleccion( int i, int Parte)
{
unsigned char r = (i*20 & 0xFF);
unsigned char g = (Parte*20 & 0xFF);
glColor4ub(r,g,0,0);
}

void dibujarPato(int i)
{
// Dibuja el pato i
float color[4]={0.6,0.0,0.6,1.0},
	naranja[4]={1.0,0.5,0.0,1.0};
int k;

//color[0] = 0.5+0.5*pato[i].color;
//color[1] = 1.0-0.5*pato[i].color;

glMaterialfv( GL_FRONT, GL_AMBIENT_AND_DIFFUSE,color);
glPushMatrix();
glTranslatef(pato[i].x, 0,pato[i].z);
                glPushName(i);			// Identificador del pato
                glPushName(PatoId);
                ColorSeleccion( i, PatoId);

                
                
glRotatef(pato[i].angulo,0,1,0);
	glPushMatrix();			//Dibujar cuerpo
		glScalef(0.7,0.6,1.0);
		glRotatef(45.0,0,1,0);
		glutSolidCube(1.0);
	glPopMatrix();
	glMaterialfv( GL_FRONT, GL_AMBIENT_AND_DIFFUSE,naranja);
			glLoadName(PatasId);
                        ColorSeleccion( i, PatasId);
                        
                        
	glPushMatrix();			//Dibujar las patas
		glTranslatef(0.2,-0.3,0);
		glRotatef(pato[i].anguloPatas,1,0,0);
		glTranslatef(0,-0.5,0);
		glScalef(1.0,0.2,1.0);
		glutSolidCube(0.3);
	glPopMatrix();
	glPushMatrix();			//Dibujar la otra pata
		glTranslatef(-0.2,-0.3,0);
		glRotatef(-pato[i].anguloPatas,1,0,0);
		glTranslatef(0,-0.5,0);
		glScalef(1.0,0.2,1.0);
		glutSolidCube(0.3);
	glPopMatrix();
	glMaterialfv( GL_FRONT, GL_AMBIENT_AND_DIFFUSE,color);
			glLoadName(CabezaId);
                        ColorSeleccion( i, CabezaId);
	glPushMatrix();			//Dibujar la cabeza
		glTranslatef(0,0.0,-0.1);
		glRotatef(pato[i].anguloCabeza,1,0,0);
		glTranslatef(0,0.3,-0.5);
		glPushMatrix();
			glScalef(0.8,0.6,1.0);
			glRotatef(45.0,0,1,0);
			glutSolidCube(0.5);
		glPopMatrix();
			glLoadName(PicoId);
                        ColorSeleccion( i, PicoId);
		glPushMatrix();		// Pico
		     glMaterialfv( GL_FRONT, GL_AMBIENT_AND_DIFFUSE,naranja);
		     glPushMatrix();
		     	glTranslatef(0,0.05,-0.2);
		     	glRotatef(pato[i].anguloPico,1,0,0);
			glTranslatef(0,0,-0.2);
		     	glScalef(0.6,0.3,1.0);
		     	glutSolidCube(0.4);
		     glPopMatrix();
		     glPushMatrix();
		     	glTranslatef(0,-0.05,-0.2);
		     	glRotatef(-pato[i].anguloPico,1,0,0);
			glTranslatef(0,0,-0.2);
		     	glScalef(0.6,0.3,1.0);
		     	glutSolidCube(0.4);
		     glPopMatrix();
		glPopMatrix();
	glPopMatrix();
			glPopName();
			glPopName();
                     
glPopMatrix();
}

void dibujarFondo()
{
// Esta en coordenadas 0,0,0 a 10,0,10

 /* Franja central*/
   glColor3ub(100,100,100);
   glBegin( GL_QUAD_STRIP );        // Cinta de cuadrilateros
      glNormal3f( 0.0, 1.0, 0.0 );   /* Suelo Izquierda */
      	glVertex3f( -20, 0, 0 );
      	glVertex3f( -20, 0, 10 );
      	glVertex3f(0, 0, 0 );
      	glVertex3f( 0, 0, 10 );
      glNormal3f( 1.0, 0.0, 0.0 );       /* Lateral*/
      	glVertex3f( 0, -10, 0 );
      	glVertex3f( 0, -10, 10 );
      glNormal3f( 0.0, 1.0, 0.0 );       /*Fondo*/
      	glVertex3f( 10, -10, 0 );
     	glVertex3f( 10, -10, 10 );
      glNormal3f( -1.0, 0.0, 0.0 );       /*Lateral*/
      glVertex3f( 10, 0, 0 );
      glVertex3f( 10, 0, 10 );
      glNormal3f( 0.0, 1.0, 0.0 );       /*Suelo Derecha*/
      glVertex3f( 30, 0, 0 );
      glVertex3f( 30, 0, 10 );
    glEnd();
   glBegin( GL_QUADS );
      glNormal3f( 0.0, 1.0, 0.0 );	/* Alante */
      glVertex3f( -20, 0, 10 );
      glVertex3f( -20,0 ,30 );
      glVertex3f( 30, 0, 30 );
      glVertex3f( 30,0,10 );

      glVertex3f( -20, 0, -20 );	// Atras
      glVertex3f( -20,0 ,0 );
      glVertex3f( 30, 0, 0 );
      glVertex3f( 30,0,-20 );

   glNormal3f( 0.0, 0.0, 1.0 );	/* costado*/
      glVertex3f( 0, 0, 0 );
      glVertex3f( 0,-10 ,0 );
      glVertex3f( 10, -10, 0 );
      glVertex3f( 10,0,0 );
   glNormal3f( 0.0, 0.0, -1.0 );	/* costado*/
      glVertex3f( 0, 0, 10 );
      glVertex3f( 10,0 ,10 );
      glVertex3f( 10, -10, 10 );
      glVertex3f( 0,-10,10 );
   glEnd();
}
void dibujarAgua()
{
// Esta en coordenadas 0,0,0 a 10,0,10
   glColor3ub(100,100,100);
   glBegin( GL_QUADS );
      glNormal3f( 0.0, 1.0, 0.0 );	/* Alante */
      glVertex3f( 0, 0, 0 );
      glVertex3f( 0,0 ,10 );
      glVertex3f( 10, 0, 10 );
      glVertex3f( 10,0, 0 );
   glEnd();
     glBegin( GL_QUADS );
      glNormal3f( 0.0, -1.0, 0.0 );	/* Alante */
      glVertex3f( 0, 0, 0 );
      glVertex3f(10,0 ,0 );
      glVertex3f( 10, 0, 10 );
      glVertex3f( 0,0,10 );
   glEnd();
}

void dibujoEscena()
{
  float azul[4]={0,0.8,1,0.6};
  float gris[4]={0.8,0.8,0.4,1};
   static GLfloat pos[4] = {5.0, 10.0, 10.0, 0.0 }; // Posicion de la luz
   int i;

   glShadeModel(GL_FLAT);
   glPushMatrix();         // Apila la transformación geométrica actual
//   	glClearColor(0,0,0,1);   // Fija el color de fondo a negro
   	glClear( GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT );
                                        // Inicializa el buffer de color
 	glTranslatef( 0, 0,-D);  // Aleja la camara


 	 glRotatef( view_rotx, 1.0, 0.0, 0.0 ); // Rotaciones de la camara
	glRotatef( view_roty, 0.0, 1.0, 0.0 );
	glRotatef( view_rotz, 0.0, 0.0, 1.0 );
	glLightfv( GL_LIGHT0, GL_POSITION, pos );
	glTranslatef(-5, 3,-5);
//	Dibuja el estanque
	  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, gris );
	  dibujarFondo();
// 	Dibuja los patos
	for(i=0;i<npatos;++i)
		dibujarPato(i);
// Dibuja el agua
	  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, azul );
	  dibujarAgua();
   glPopMatrix();
}

void dibujar()
{
glEnable(GL_LIGHTING);
glEnable(GL_DITHER);
glClearColor(0,0,0,1);   // Fija el color de fondo a negro
 dibujoEscena();
glutSwapBuffers();          // Intercambia buffers: visualiza lo dibujado
}

void viewtrans()
{
float calto;
    if(viewX>0)
  	calto =  viewY/viewX;
   else
  	calto = 1;
   glFrustum(-1+vofx,1+vofx,calto*(-1+vofy),calto*(1+vofy),3,1000);
        // Transformacion de visualizacion
  glMatrixMode(GL_MODELVIEW); // A partir de este momento las transformaciones son de modelado
  glLoadIdentity();     // Inicializa la transformacion
}


void setviewtrans()
{
float calto;
    glMatrixMode(GL_PROJECTION); // Especificamos la transformación de visualización
   glLoadIdentity();    // Inicializa la transformacion
   viewtrans();
  }

void Ventana(GLsizei ancho,GLsizei alto)
{
  viewX = ancho; // Almacena las dimensiones en variables del programa
  viewY = alto;
  glViewport(0,0,ancho,alto);
setviewtrans();
}

static void especial(int k, int x, int y)
// Este procedimiento es llamado por el sistema cuando se pulsa una tecla
// especial. El codigo k esta definido en glut mediante constantes
{
  switch (k) {
  case GLUT_KEY_UP:
    view_rotx += 5.0;   // Cursor arriba + rotacion x
    break;
  case GLUT_KEY_DOWN:
    view_rotx -= 5.0;
    break;
  case GLUT_KEY_LEFT:
    view_roty += 5.0;
    break;
  case GLUT_KEY_RIGHT:
    view_roty -= 5.0;
    break;
  default:
    return;
  }
  glutPostRedisplay();  // Actualiza la imagen (ver proc. letra)
}

 static void letra (unsigned char k, int x, int y)
// Este procedimiento es llamado por el sistema cuando se pulsa una tecla normal
// El codigo k es el ascii de la letra
{
  switch (k) {
  case 'a':
  case 'A':
    vofx -= 0.15;
    break;
  case 'd':
  case 'D':
    vofx += 0.15;
    break;
  case 'w':
  case 'W':
    vofy += 0.15;
    break;
  case 'x':
  case 'X':
    vofy -= 0.15;
    break;
    case 's':
  case 'S':
    vofx = 0.0;
    vofy=0.0;
    break;
  case '+':             // + Camara mas cerca
    D -= 5.0;
    break;
  case '-':             // - Camara mas lejos
    D += 5.0;
    break;
case 'z':
    view_rotz += 5.0;   // z +rotacion respecto a Z
    break;
  case 'Z':
    view_rotz -= 5.0;   // Z -rotacion respecto a Z
    break;
  case 27:  /* Escape */  // Terminar
    exit(0) ;
    break;
  default:
    return;
  }
  setviewtrans();
  glutPostRedisplay();  // Algunas de las opciones cambian paramentros
}                       // de la camara. Es necesario actualziar la imagen

void animar(int v)
{
int i,k;
contador ++;
if(contador>100){
	contador=0;
	k=crearPato();

	}
for(i=0;i<npatos;++i) {
	if(pato[i].color!=-1) {	// Este pato existe
		if(pato[i].velocidadX!=0 ||  pato[i].velocidadZ!=0 )	{	// Esta andando
			pato[i].x+=pato[i].velocidadX;
			pato[i].z+=pato[i].velocidadZ;
			if(pato[i].x>9.5 || pato[i].x<0.5 ) {
				pato[i].velocidadX=-pato[i].velocidadX;
				pato[i].angulo=pato[i].angulo+90;
				}
			if(pato[i].z>9.5 || pato[i].z<0.5) {
				 pato[i].velocidadZ=-pato[i].velocidadZ;
				 pato[i].angulo=pato[i].angulo+90;
				 }
			}
		if(pato[i].velocidadGiro!=0)	{	// Esta girando
				pato[i].angulo+= pato[i].velocidadGiro;
				pato[i].velocidadX=pato[i].velocidadZ=0.0;
			}
		if(pato[i].velocidadPatas!=0)	{	// Esta moviendo las patas
				pato[i].anguloPatas+= pato[i].velocidadPatas;
				if(pato[i].anguloPatas > 45.0) pato[i].velocidadPatas=-pato[i].velocidadPatas;
				if(pato[i].anguloPatas < -45.0) pato[i].velocidadPatas=-pato[i].velocidadPatas;
			}
		if(pato[i].velocidadCabeza!=0)	{	// Esta girando la cabeza
				pato[i].anguloCabeza+= pato[i].velocidadCabeza;
				if(pato[i].anguloCabeza > 20.0) pato[i].velocidadCabeza=-pato[i].velocidadCabeza;
				if(pato[i].anguloCabeza < -45.0) pato[i].velocidadCabeza=-pato[i].velocidadCabeza;
			}
		if(pato[i].velocidadPico!=0)	{	// Esta moviendo el pico
				pato[i].anguloPico+= pato[i].velocidadPico;
				if(pato[i].anguloPico > 45.0) pato[i].velocidadPico=-pato[i].velocidadPico;
				if(pato[i].anguloPico < 0.0) pato[i].velocidadPico=-pato[i].velocidadPico;
			}
		}
	}
		if(uodate) glutPostRedisplay();
    glutTimerFunc( 50, animar, 0);      // Funcion de fondo
}


int pick(int x, int y,int * i, int * parte)
{
 
    GLint viewport[4];
    unsigned char data[4];
	int f=0;

    glGetIntegerv (GL_VIEWPORT, viewport);
    glDisable(GL_DITHER); 
    glDisable(GL_LIGHTING);
	glClearColor(0,0,1,1);   // Fija el color de fondo a negro
    dibujoEscena();
    glEnable(GL_LIGHTING);
    glEnable(GL_DITHER); 
//	uodate=0;
   glFlush();
//   glFinish();
   

   glReadPixels(x, viewport[3] - y,1,1, GL_RGBA, GL_UNSIGNED_BYTE, data);
   
   *i=data[0]/20;
   *parte=data[1]/20;
   if(data[2]>0)
	f=-1;

//    dibujoEscena();
//    glutSwapBuffers();
return f;
}


void clickRaton( int boton, int estado, int x, int y )
// Este procedimiento será llamado por el sistema cuando se haga click
// con el ratón. Los parametros indican el estado del ratón en ese momento.
{
int parte=-1, i=-1,k=0;
float s,c;

   if(boton== GLUT_LEFT_BUTTON && estado == GLUT_DOWN) {
                // Se ha actuado sobre el izquierdo que esta ahora pulsado
		
	k=pick(x,y,&i,&parte);
	printf(" %d: %d %d \n",k,i,parte);
        if(k>-1) {
		switch (parte) {
		case PatoId:
			if(pato[i].velocidadX!=0 ||  pato[i].velocidadZ!=0 )	{	// Esta andando => se para y gira
				pato[i].velocidadX = 0;
				pato[i].velocidadZ =0;
				pato[i].velocidadPatas=0;
				pato[i].velocidadGiro=5;
				}
			else if(pato[i].velocidadGiro!=0)	// Girando => parado
					pato[i].velocidadGiro=0;
				else {								// Parado => andando
					if(pato[i].x>9.5 || pato[i].x<0.5 || pato[i].z>9.5 || pato[i].z<0.5) 	pato[i].velocidadGiro=5;
					s=sin(pato[i].angulo * 3.14159/180);
					c=cos(pato[i].angulo * 3.14159/180);
					pato[i].velocidadX = -0.08*s;
					pato[i].velocidadZ =-0.08*c;
				}
			break;
		case CabezaId:
			if(pato[i].velocidadCabeza!=0  )		// Esta andando => se para
				pato[i].velocidadCabeza = 0.0;
			else
				pato[i].velocidadCabeza=2;
			break;
		case PicoId:
			if(pato[i].velocidadPico!=0  )		// Esta andando => se para
				pato[i].velocidadPico = 0.0;
			else
				pato[i].velocidadPico=5;
			break;
		case PatasId:
			if(pato[i].velocidadPatas!=0  )		// Esta andando => se para
				pato[i].velocidadPatas = 0.0;
			else
				pato[i].velocidadPatas=8;
			break;
			}
		}
	}
}

int main( int argc, char *argv[] )
{
   glutInit( &argc, argv ); // Inicializa glu y Mesa

   glutInitWindowSize( 500,500 );          // Tamaño
   glutInitDisplayMode( GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE); // Tipo

   glutCreateWindow("UGR: IG. Tema4. Seleccion (Duck).");   // Crea la ventana

// Inicializa las funciones de dibujo y cambio de tamaño de la ventana X
   glutDisplayFunc( dibujar );   // Indica funcion de redibujo
   glutReshapeFunc( Ventana );  // Indica funcion de cambio de tamaño de ventana X

// Inicializacion

// FUNCIONES DE INTERACCÓN
    glutMouseFunc( clickRaton ); // Indica la funcion a llamar cuando se hace click
    glutKeyboardFunc(letra);    // Llamada para teclado
    glutSpecialFunc(especial);   // Llamada para teclas especiales

    glutTimerFunc( 200, animar, 0);      // Funcion de fondo

// Activacion de funciones
    glEnable(GL_CULL_FACE);     // Activa eliminacion de caras traseras
    glEnable( GL_LIGHTING );    // Activa uso de luces
    glEnable( GL_LIGHT0 );      // Activa luz 0
    glEnable(GL_DEPTH_TEST);    // Activa test de profundidad
 //   glEnable(GL_BLEND);
//    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    crearPato();

// Empieza
   glutMainLoop();              // Llama al gestor de eventos de glut
   return 0;
}


