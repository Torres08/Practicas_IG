/*
				PICK
	I.G.						Curso 2021-2022

	Dpto. Lenguajes y Sistemas Informáicos
	E.T.S.I. Informáica
	Univ. de Granada

       Tema4. Interacción

        Objetivo: Este programa muestra seleccion por color usando OpenGL
	
*/
#include <math.h>
#include <GL/glut.h>                   // Libreria de utilidades de OpenGL
#include <stdio.h>
#include <stdlib.h>

/*  ============================== Modelo geometrico ============
 Lista de esferas.
 Cada esfera tiene un centro, color y un rádio
*/
typedef struct {
	float x,y,z;
	float color[4];
	float r;
		} Esfera;

#define MAXESFERAS 100 		// 21 patos son demasiados !!

Esfera bola[MAXESFERAS];



float random_float(float min, float max) {
    return (float)rand() / (float)RAND_MAX * (max - min) + min;
}

void ponerEsfera(Esfera *esfera) {
    esfera->x = random_float(-100.0f, 100.0f);  // Rango de -100 a 100
    esfera->y = random_float(-100.0f, 100.0f);
    esfera->z = random_float(-100.0f, 100.0f);

    esfera->color[0] = random_float(0.0f, 1.0f);  // Colores entre 0 y 1
    esfera->color[1] = random_float(0.0f, 1.0f);
    esfera->color[2] = random_float(0.0f, 1.0f);
	esfera->color[3] = 1;

    esfera->r = random_float(1.0f, 10.0f);  // Radio entre 1 y 10
}

void init(){
	int i;
	for(i=0;i<MAXESFERAS;++i){
		ponerEsfera(&bola[i]);
	}
}


void ColorSeleccion( int i)
{
unsigned char r = ((i+1) & 0xFF);
glColor4ub(r,0,0,0);
}


void dibujoEscena()
{
   int i;
   glClear( GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT );
   glPushMatrix();
   glTranslatef( 0, 0,-30);  // Aleja la camara
   for(i=0;i<MAXESFERAS;++i){
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, bola[i].color );
	ColorSeleccion(i);
   	glTranslatef( bola[i].x, bola[i].y,-bola[i].z);
	glutSolidSphere(bola[i].r,20,20);
	glPopMatrix();
   }
   glPopMatrix();
}

void dibujar()
{
glEnable(GL_LIGHTING);
glEnable(GL_DITHER);
glShadeModel(GL_SMOOTH);
glClearColor(1,1,1,1);   // Fija el color de fondo a negro
 dibujoEscena();
glutSwapBuffers();          // Intercambia buffers: visualiza lo dibujado
}

void Ventana(GLsizei ancho,GLsizei alto)
{
float calto;
  glViewport(0,0,ancho,alto);
  glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   if(ancho>0)
  	calto =  alto/ancho;
   else
  	calto = 1;
   glOrtho(-100,100,-100*calto,100*calto,0,140);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}



 static void letra (unsigned char k, int x, int y)
{
  switch (k) {
  case 27:  /* Escape */  // Terminar
    exit(0) ;
    break;
  default:
    return;
  }
  glutPostRedisplay();  // Algunas de las opciones cambian paramentros
}                       // de la camara. Es necesario actualziar la imagen




int pick(int x, int y,int * i)
{
 
    GLint viewport[4];
    unsigned char data[4];
	int f=0;

    glGetIntegerv (GL_VIEWPORT, viewport);
    glDisable(GL_DITHER); 
    glDisable(GL_LIGHTING);
	glClearColor(0,0,0,1);   // Fija el color de fondo a negro
    dibujoEscena();
    glEnable(GL_LIGHTING);
    glEnable(GL_DITHER); 
   glFlush();
   glReadPixels(x, viewport[3] - y,1,1, GL_RGBA, GL_UNSIGNED_BYTE, data);
   if(data[0]>0) f=1;
   *i=data[0]-1;
return f;
}


void clickRaton( int boton, int estado, int x, int y )
{
int i=-1,k=0;

   if(boton== GLUT_LEFT_BUTTON && estado == GLUT_DOWN) {
                // Se ha actuado sobre el izquierdo que esta ahora pulsado
		
	k=pick(x,y,&i);
	printf(" %d: %d \n",k,i);
        if(k) { ponerEsfera(&bola[i]);
		dibujar();
		}
	}
}

int main( int argc, char *argv[] )
{
   glutInit( &argc, argv ); // Inicializa glu y Mesa

   glutInitWindowSize( 500,500 );          // Tamaño
   glutInitDisplayMode( GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE); // Tipo

   glutCreateWindow("UGR: IG. Tema4. Seleccion");   // Crea la ventana

// Inicializa las funciones de dibujo y cambio de tamaño de la ventana X
   glutDisplayFunc( dibujar );   // Indica funcion de redibujo
   glutReshapeFunc( Ventana );  // Indica funcion de cambio de tamaño de ventana X

// Inicializacion

// FUNCIONES DE INTERACCÓN
    glutMouseFunc( clickRaton ); // Indica la funcion a llamar cuando se hace click
    glutKeyboardFunc(letra);    // Llamada para teclado


// Activacion de funciones
    glEnable(GL_CULL_FACE);     // Activa eliminacion de caras traseras
    glEnable( GL_LIGHTING );    // Activa uso de luces
    glEnable( GL_LIGHT0 );      // Activa luz 0
    glEnable(GL_DEPTH_TEST);    // Activa test de profundidad

	init();

// Empieza
   glutMainLoop();              // Llama al gestor de eventos de glut
   return 0;
}


