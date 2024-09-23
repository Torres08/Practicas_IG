/*

	Dpto. Lenguajes y Sistemas Inform�ticos
	E.T.S.I. Inform�tica
	Univ. de Granada

        Demostraci�n Geometria 1.
        Este es un programa simple que utiliza Mesa. Dibuja un cubo
        en la ventana de salida.

        Objetivo: Estudiar la definici�n de propiedades de elementos geom�tricos.
	
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

float D=100.0;
static GLfloat view_rotx=20.0, view_roty=30.0, view_rotz=0.0;

static int		menu;     // Identificador del menu
typedef enum{ ZOOM,GIRAR,SALIR} opciones_menu;
typedef enum {MOVIENDO,GIRANDO} acciones_raton;
int MODORaton=MOVIENDO;
int RatonPulsado = GL_FALSE;

int Xref=0, Yref=0;



static void ejes(float L)
{
glBegin(GL_LINES);{
  glColor3f(1,1,1);
  glVertex3f( 0, 0, 0 );
  glVertex3f( 0, L, 0 );
  glVertex3f( 0, 0, 0 );
  glVertex3f( L, 0, 0 );
  glVertex3f( 0, 0, 0 );
  glVertex3f( 0, 0, L );

	}
glEnd();
}


static void cubo( GLfloat x, GLfloat y, GLfloat z )
/* Construye una caja con un vertice en origen y otro en (x,y,z)
*/
{
	float color[4]={0.2,0.7,1,1};

   glShadeModel( GL_FLAT );

   glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color );



   /* Caras transversales */
   glBegin( GL_QUAD_STRIP );{
      glNormal3f( 0.0, 0.0, -1.0 );   /* Vertical hacia atras */

      glVertex3f( x, 0, 0 );
      glVertex3f( 0, 0, 0 );


      glVertex3f( x, y, 0 );
      glVertex3f( 0, y, 0 );

glNormal3f( 0.0, 1.0, 0.0 );       /* Superior, horizontal */

      glVertex3f( x, y, z );
      glVertex3f( 0, y, z );
glNormal3f( 0.0, 0.0, 1.0 );       /*Vertical delantera*/
      glVertex3f( x, 0, z );
      glVertex3f( 0, 0, z );

glNormal3f( 0.0, -1.0, 0.0 );       /*Inferior */
      glVertex3f( x, 0, 0 );
      glVertex3f( 0, 0, 0 );  }
    glEnd();

   /* Costados */
   glBegin( GL_QUADS );{
      glNormal3f( 1.0, 0.0, 0.0 );
      glVertex3f( x, 0, 0 );
      glVertex3f( x, y, 0 );
      glVertex3f( x, y, z );
      glVertex3f( x, 0, z ); }
   glEnd();


   glBegin( GL_QUADS );{
      glNormal3f( -1.0, 0.0, 0.0 );
      glVertex3f( 0, 0, 0 );
      glVertex3f( 0, 0, z );
      glVertex3f( 0, y, z );
      glVertex3f( 0, y, 0 ); }
   glEnd();


}


static void Dibuja( void )
{
   static GLfloat pos[4] = {5.0, 5.0, 10.0, 0.0 };

glPushMatrix();		// Apila la transformaci�n geom�trica actual
  // Fija el color de fondo a negro
  glClearColor(0,0,0,1);
  // Inicializa el buffer de color
  glClear( GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT );

  // Fija el color de dibujo
  // Introduce la geometria

  glTranslatef(0,0,-D);
// Colocar aqui la luz si esta fija respecto del observador
  glLightfv( GL_LIGHT0, GL_POSITION, pos );

  glRotatef( view_rotx, 1.0, 0.0, 0.0 );
  glRotatef( view_roty, 0.0, 1.0, 0.0 );
  glRotatef( view_rotz, 0.0, 0.0, 1.0 );

// Colocar aqui la luz si esta fija en la escena
//    glLightfv( GL_LIGHT0, GL_POSITION, pos );

  ejes(30);
  cubo(10,10,10);

glPopMatrix(); // Desapila la transformaci�n geom�trica

glutSwapBuffers();
}
/* ------------------------------------------------------------------------- */

void Ventana(GLsizei ancho,GLsizei alto)
{
	float calto; 	// altura de la ventana corregida
  // Establecemos el Viewport usando la nueva anchura y altura de la ventana X
  	glViewport(0,0,ancho,alto);

 // Especificamos la transformaci�n de visualizaci�n 	
  	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	

  	if(ancho>0)
  		calto = 1*(GLfloat)alto/(GLfloat)ancho;
  	else
  		calto = 1;
  		
//  		glOrtho(-50,50,-calto, calto,0,1);
			glFrustum(-1,1,-calto,calto,5,250);

// A partir de este momento las transformaciones son de modelado  		
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();



}

/* -------------------- FUNCIONES DE INTERACCI�N ----------------------------------- */
 static void letra (unsigned char k, int x, int y)
{
  switch (k) {
  case 'h':
  case 'H':
  	printf("\n Dpto. Lenguajes y Sistemas Inform�ticos");
  	printf("\n E.T.S.I. Inform�tica		Univ. de Granada ");
  	printf("\n Demostraci�n Geo1");
  	printf("\n");
  	printf("\n Escape: Salir");
  	printf("\n\n\n");
  	break;
  case 'z':
    view_rotz += 5.0;
    break;
  case '+':
    D -= 5.0;
    break;
  case '-':
    D += 5.0;
    break;
  case 'Z':
    view_rotz -= 5.0;
    break;
  case 27:  /* Escape */
    exit(0);
    break;
  default:
    return;
  }
  glutPostRedisplay();
}


static void idle()
{
view_roty +=0.15;
  glutPostRedisplay();
}

 static void especial(int k, int x, int y)
{
  switch (k) {
  case GLUT_KEY_UP:
    view_rotx += 5.0;
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
  glutPostRedisplay();
}

 void seleccionMenu( int opcion )
{
   switch ( opcion )
   {
   case SALIR:
   	  exit(0);
   }
}



 void CreaMenu()
{

   menu = glutCreateMenu( seleccionMenu );

   glutAddMenuEntry( "Salir", SALIR );

	MODORaton = MOVIENDO;

   glutAttachMenu( GLUT_RIGHT_BUTTON );
   glEnable(GL_DEPTH_TEST);
   glEnable(GL_CULL_FACE);
   glEnable( GL_LIGHTING );
   glEnable( GL_LIGHT0 );

}



/* ------------------------------------------------------------------------- */




int main( int argc, char *argv[] )
{
// Inicializa glu y Mesa
   glutInit( &argc, argv );

// Crea una ventana X para la salida gr�fica
   glutInitWindowPosition( 600, 300 );
   glutInitWindowSize( 300, 300 );
   glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH );
   glutCreateWindow("IG: cubo.");


// Inicializa las funciones de dibujo y cambio de tama�o de la ventana X
   glutDisplayFunc( Dibuja );
   glutReshapeFunc( Ventana );

// FUNCIONES DE INTERACCI�N
 	CreaMenu();
  	glutKeyboardFunc(letra);
  	glutSpecialFunc(especial);
	glutIdleFunc(idle);


   glutMainLoop();
   return 0;
}