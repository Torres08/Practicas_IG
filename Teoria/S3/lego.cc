#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

/*
gcc lego.cc -lglut -lGLU -lGL -lm -o lego

*/

float roty = 30.0;
int figuraSeleccionada = 1; // Variable global para almacenar la figura seleccionada

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
  float width = 4;
  float height = 1;
  float depth = 2;
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

  glTranslatef(2, 0.5, 1); // para ponerlo con el eje de coordenadas

  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, verde);
  caja();

  glPushMatrix();
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, rojo);
  glRotatef(90.0, 0.0, 1.0, 0.0);
  glTranslatef(-1, 1, -1);
  caja();

  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, morado);
  glTranslatef(0, -1, 4);
  caja();
  glPopMatrix();

  glPushMatrix();
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, azul);
  glTranslatef(2, 1, 0);
  caja();
  glPopMatrix();
}

void Figura2()
{
  glTranslatef(2, 0.5, 1); // para ponerlo con el eje de coordenadas

  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, verde);
  caja();

  glPushMatrix();
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, azul);
  glRotatef(90.0, 1.0, 0.0, 0.0);
  glTranslatef(0, -0.5, -1.5);
  caja();

  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, rojo);
  glTranslatef(0, 2, 1);
  caja();
  glPopMatrix();

  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, morado);
  glTranslatef(0, 2, 1);
  caja();
}

void Figura3()
{
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, verde);
  for (int i = 0; i < 20; i++)
  {
    glTranslatef(0.0, 1.0, 0.0);
    glRotatef(20.0, 0.0, 1.0, 0.0);
    caja();
  }
}

void Figura4()
{

  glPushMatrix();
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, verde);

  // Traslación inversa para llevar el punto (2, 0, -1) al origen
  glTranslatef(-2.0f, 0.0f, 1.0f);

  // Rotación alrededor del eje Y en el origen: 45 grados
  glRotatef(roty, 0.0f, 1.0f, 0.0f);

  // Traslación de regreso a la posición original (2, 0, -1)
  glTranslatef(2.0f, 0.0f, -1.0f);

  // Aquí dibujarías el objeto que quieres rotar
  caja(); // Ejemplo: dibujar un cubo

  glPopMatrix();
}

void rotarRespectoAlEje(float anguloGrados, float x, float y, float z)
{
  // Normalizamos el vector (1,1,1) para obtener el eje unitario de rotación
  float longitud = sqrt(x * x + y * y + z * z); // Magnitud del vector
  float ux = x / longitud;
  float uy = y / longitud;
  float uz = z / longitud;

  // Aplicamos la rotación alrededor del eje (ux, uy, uz)
  glRotatef(anguloGrados, ux, uy, uz);
}

// revisar esto
void Figura5()
{
  glPushMatrix(); // Guardar la matriz actual

  // Dibuja el vector (1, 1, 1)
  glColor3f(1.0f, 0.0f, 0.0f); // Color rojo para el vector
  glBegin(GL_LINES);
  glVertex3f(0.0f, 0.0f, 0.0f);    // Punto de inicio en el origen
  glVertex3f(10.0f, 10.0f, 10.0f); // Punto final (1, 1, 1)
  glEnd();

  // caja rota sobre el vector (1, 1, 1)
  glTranslatef(2.0f, 0.0f, -1.0f);            // Trasladar el objeto al origen
  rotarRespectoAlEje(roty, 1.0f, 1.0f, 1.0f); // Rotar alrededor de (1,1,1)  glTranslatef(-2.0f, 0.0f, 1.0f);   // Trasladar el objeto a su posición original
  glTranslatef(-2.0f, 0.0f, 1.0f);            // Trasladar de vuelta a la posición original

  // Dibujar el objeto (una caja en este caso)
  caja();

  glPopMatrix(); // Restaurar la matriz original
}

void Figura6()
{

  glPushMatrix();

  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, rojo);
  glutSolidTorus(0.5, 3, 24, 32);

  glTranslatef(0, 4, 0);
  glRotatef(90, 0, 1, 0);
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, verde);
  glPushMatrix();
  glRotatef(45, 1, 0, 0);
  glutSolidTorus(0.5, 3, 24, 4);
  glPopMatrix();
  glTranslatef(0, 4, 0);
  glRotatef(90, 0, 1, 0);
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, morado);
  glutSolidTorus(0.5, 3, 24, 8);

  glPopMatrix();
}

void Figura7()
{

  /*
  glPushMatrix();
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, rojo);
  glRotatef(90, 0, 1, 0);
  glutSolidTorus(0.5, 3, 24, 32);
  glPopMatrix();

  glPushMatrix();
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, verde);
  glRotatef(90, 1, 0, 0);
  glutSolidTorus(0.5, 3, 24, 32);
  glPopMatrix();

  glPushMatrix();
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, azul);
  glRotatef(90, 0, 0, 1);
  glutSolidTorus(0.5, 3, 24, 32);
  glPopMatrix();
  */
  GLfloat colores[3][4] = {
      {1.0, 0.0, 0.0, 1.0}, // Rojo
      {0.0, 1.0, 0.0, 1.0}, // Verde
      {0.0, 0.0, 1.0, 1.0}  // Azul
  };

  GLfloat rotaciones[3][3] = {
      {0, 1, 0}, // Rotación en Y
      {1, 0, 0}, // Rotación en X
      {0, 0, 1}  // Rotación en Z
  };

  // Bucle que realiza las 3 rotaciones con sus respectivos colores
  for (int i = 0; i < 3; i++)
  {
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, colores[i]);
    glRotatef(90, rotaciones[i][0], rotaciones[i][1], rotaciones[i][2]);
    glutSolidTorus(0.5, 3, 24, 32);
    glPopMatrix();
  }
}

void Figura8()
{
   // Dibujar el toroide grande (azul) que rodea todo
    glPushMatrix();
    glRotatef(90, 0, 1, 0); // Rotar para que el toroide esté en posición horizontal
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, azul);
    glutSolidTorus(0.3, 3.0, 24, 32);  // Radio pequeño: 0.5, Radio grande: 8.0
    glPopMatrix();

    // Dibujar varios toroides pequeños naranjas en un patrón radial
    int numToroides = 8; // Número de toroides pequeños
    for (int i = 0; i < numToroides; i++)
    {
        glPushMatrix();
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, rojo);

        // Rotar para distribuir los toroides alrededor del eje Z
        glRotatef(i * (360.0 / numToroides), 1.0, 0.0, 0); 

        // Dibujar el toroide naranja
        glutSolidTorus(0.3, 3.0, 24, 32); // Radio pequeño: 0.3, Radio grande: 3.0
        glPopMatrix();
    }
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
  case 6:
    Figura6();
    break;
  case 7:
    Figura7();
    break;
  case 8:
    Figura8();
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
