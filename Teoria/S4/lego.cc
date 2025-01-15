#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

/*
gcc lego.cc -lglut -lGLU -lGL -lm -o lego

*/

float roty = 30.0;

float roty_2 = 0;

float roty_3 = 1;

int figuraSeleccionada = 5; // Variable global para almacenar la figura seleccionada

class Ejes
{
public:
  float longitud = 30;
  // Dibuja el objeto
  void draw()
  {
    glDisable(GL_LIGHTING);
    glBegin(GL_LINES);
    {
      glColor3f(0, 1, 0);
      glVertex3f(0, 0, 0);
      glVertex3f(0, longitud, 0);

      glColor3f(1, 0, 0);
      glVertex3f(0, 0, 0);
      glVertex3f(longitud, 0, 0);

      glColor3f(0, 0, 1);
      glVertex3f(0, 0, 0);
      glVertex3f(0, 0, longitud);
    }
    glEnd();
    glEnable(GL_LIGHTING);
  }
};

Ejes ejesCoordenadas;

void plano(float t)
// Construye un plano horizontal de tamano t x t
{
  glBegin(GL_QUADS);
  glNormal3f(0.0, 1.0, 0.0);
  glVertex3f(t, 0, t);
  glVertex3f(t, 0, -t);
  glVertex3f(-t, 0, -t);
  glVertex3f(-t, 0, t);
  glEnd();
}

void caja()
{
  float width = 1;
  float height = 1;
  float depth = 1;
  GLfloat vertices[8][3] = {
      {-width / 2, -height / 2, -depth / 2}, // Vértice 0
      {width / 2, -height / 2, -depth / 2},  // Vértice 1
      {width / 2, height / 2, -depth / 2},   // Vértice 2
      {-width / 2, height / 2, -depth / 2},  // Vértice 3
      {-width / 2, -height / 2, depth / 2},  // Vértice 4
      {width / 2, -height / 2, depth / 2},   // Vértice 5
      {width / 2, height / 2, depth / 2},    // Vértice 6
      {-width / 2, height / 2, depth / 2}    // Vértice 7
  };

  GLubyte indices[6][4] = {
      {0, 1, 2, 3}, // Cara frontal
      {4, 5, 6, 7}, // Cara trasera
      {0, 1, 5, 4}, // Cara inferior
      {2, 3, 7, 6}, // Cara superior
      {0, 3, 7, 4}, // Cara izquierda
      {1, 2, 6, 5}  // Cara derecha
  };

  GLfloat normales[6][3] = {
      {0.0f, 0.0f, -1.0f}, // Normal de la cara frontal
      {0.0f, 0.0f, 1.0f},  // Normal de la cara trasera
      {0.0f, -1.0f, 0.0f}, // Normal de la cara inferior
      {0.0f, 1.0f, 0.0f},  // Normal de la cara superior
      {-1.0f, 0.0f, 0.0f}, // Normal de la cara izquierda
      {1.0f, 0.0f, 0.0f}   // Normal de la cara derecha
  };

  glBegin(GL_QUADS);
  for (int i = 0; i < 6; i++)
  {
    glNormal3fv(normales[i]);
    for (int j = 0; j < 4; j++)
    {
      glVertex3fv(vertices[indices[i][j]]);
    }
  }
  glEnd();
}

float pos[4] = {5.0, 5.0, 10.0, 0.0};
float morado[4] = {0.8, 0, 1, 1}, verde[4] = {0, 1, 0, 1};
float rojo[4] = {1, 0, 0, 1};
float azul[4] = {0, 0, 1, 1};

void Figura1()
{

  glPushMatrix();

  glTranslatef(0.5, 0.5, 0.5);

  glPushMatrix();
  caja();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0, 1, 0);

  glPushMatrix();
  caja();
  glTranslatef(1, 0, 0);
  caja();
  glPopMatrix();

  glTranslatef(0, 1, 0);
  caja();

  glPopMatrix();

  glPopMatrix();
}

void Figura2()
{

  glPushMatrix();

  // base
  glPushMatrix();
  glTranslatef(0, 4, 0);
  glScalef(2, 8, 2);
  caja();
  glPopMatrix();

  glRotatef(roty, 0, 1, 0);

  glPushMatrix();

  // glTranslatef(0,9,0);

  glPushMatrix();
  glTranslatef(0, 9, 2);
  glScalef(2, 2, 8);
  caja();
  glPopMatrix();

  // gancho + `luma
  glPushMatrix();

  glTranslatef(0, 0, roty_2);
  glTranslatef(0, 1, 3);

  glPushMatrix();
  glTranslatef(0, 6, 0);
  glScalef(2, 2, 2);
  caja();
  glPopMatrix();

  glTranslatef(0, roty_2, 0);

  glPushMatrix();
  glTranslatef(0, 4, 0);
  glScalef(1, 4, 1);
  caja();
  glPopMatrix();

  glPopMatrix();

  glPopMatrix();

  glPopMatrix();
}

void Figura3()
{

  // Figura 4
  glPushMatrix();

  glTranslatef(4, 0, 4);
  glRotatef(-180, 0, 1, 0);

  glPushMatrix();
  glRotatef(-90, 0, 0, 1);
  glRotatef(-90, 0, 1, 0);

  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, morado);

  Figura1();
  glPopMatrix();

  glPopMatrix();

  // Figura 3
  glPushMatrix();

  glTranslatef(0, 0, 4);
  glRotatef(90, 0, 1, 0);

  glPushMatrix();
  glRotatef(-90, 0, 0, 1);
  glRotatef(-90, 0, 1, 0);

  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, verde);

  Figura1();
  glPopMatrix();

  glPopMatrix();

  // Figura 2
  glPushMatrix();

  glTranslatef(4, 0, 0);
  glRotatef(-90, 0, 1, 0);

  glPushMatrix();
  glRotatef(-90, 0, 0, 1);
  glRotatef(-90, 0, 1, 0);

  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, rojo);

  Figura1();
  glPopMatrix();

  glPopMatrix();

  // figura 1
  glPushMatrix();
  glRotatef(-90, 0, 0, 1);
  glRotatef(-90, 0, 1, 0);

  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, azul);

  Figura1();
  glPopMatrix();
}

void lego()
{
  glPushMatrix();
  glTranslatef(0.5, 0.5, 0.5);
  caja();
  glPopMatrix();
}

void Figura4()
{


  glPushMatrix();
  glScalef(15,1,3);
  lego();
  glPopMatrix();

  glPushMatrix();

  glTranslatef(14,0,3);
  glRotatef(180,0,1,0);

  glPushMatrix();

  glScalef(1, 10, 3);
  lego();
  glPopMatrix();

    
  glPushMatrix();
  glTranslatef(1,0,0);
  glScalef(1,10,1);
  lego();
  glPopMatrix();


  glPushMatrix();


  glPushMatrix();
  glTranslatef(1,0,2);
  glScalef(1,10,1);
  lego();
  glPopMatrix();


  glPushMatrix();
  
  glPopMatrix();

  glPopMatrix();
}

void Figura5(){

  glTranslatef(11,10,0);
  glScalef(20,2,2);

  glPushMatrix();
  glTranslatef(0, 0.5, 0);
  caja();
  glPopMatrix();
}

void Dibuja()
{
  glClearColor(1, 1, 1, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  glTranslatef(-0.5, -5, -100);
  glLightfv(GL_LIGHT0, GL_POSITION, pos);
  glRotatef(20, 1.0, 0.0, 0.0);
  glRotatef(roty, 0.0, 1.0, 0.0);
  // glRotatef(-90, 0.0, 1.0, 0.0);
  ejesCoordenadas.draw();

  // glTranslatef(2, 0.5, 1);

  // Cambiar de figura según la tecla presionada
  switch (figuraSeleccionada)
  {
  case 1:
    Figura1();
    break;
  case 2:
    Figura2();
    break;
  case 3:
    Figura3();
    break;
  case 4:
    Figura4();
    break;
  case 5:
    Figura5();
    break;
  default:
    break;
  }

  glPopMatrix();
  glutSwapBuffers();
}

// Función para manejar las teclas
void teclado(unsigned char tecla, int x, int y)
{
  switch (tecla)
  {
  case '1':
    figuraSeleccionada = 1;
    break;
  case '2':
    figuraSeleccionada = 2;
    break;
  case '3':
    figuraSeleccionada = 3;
    break;
  case '4':
    figuraSeleccionada = 4;
    break;
  case '5':
    figuraSeleccionada = 5;
    break;
  case '6':
    figuraSeleccionada = 6;
    break;
  case '7':
    figuraSeleccionada = 7;
    break;
  case '8':
    figuraSeleccionada = 8;
    break;
  default:
    break;
  }
  glutPostRedisplay(); // Redibujar la ventana cuando se presiona una tecla
}

void Ventana(GLsizei ancho, GLsizei alto)
{
  float D = ancho;
  if (D < alto)
    D = alto;
  glViewport(0, 0, ancho, alto);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(-ancho / D, ancho / D, -alto / D, alto / D, 5, 250);
  glMatrixMode(GL_MODELVIEW);
}

void idle()
{
  roty += 0.15;

  static bool increasing = true;

  if (increasing)
  {
    roty_2 += 0.01;
    if (roty_2 >= 2.0)
    {
      increasing = false;
    }
  }
  else
  {
    roty_2 -= 0.01;
    if (roty_2 <= 0.0)
    {
      increasing = true;
    }
  }

  roty_3 += 0.01;

  if (roty_3 > 3.0)
  {
    roty_3 = 2.0;
  }

  glutPostRedisplay();
}

int main(int argc, char *argv[])
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
  glutCreateWindow("IG: cubo");
  glutDisplayFunc(Dibuja);
  glutReshapeFunc(Ventana);
  glutIdleFunc(idle);
  glutKeyboardFunc(teclado); // Asignar la función de teclado
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_DEPTH_TEST);
  glutMainLoop();
  return 0;
}
