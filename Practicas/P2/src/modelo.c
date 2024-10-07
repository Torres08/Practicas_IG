/*	Prácticas de Informática Gráfica

  Grupos C y D				Curso 2023-24

  Codigo base para la realización de las practicas de IG

  Estudiante:

=======================================================
  G. Arroyo, J.C. Torres
  Dpto. Lenguajes y Sistemas Informticos
  (Univ. de Granada)

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details
 http://www.gnu.org/copyleft/gpl.html

=======================================================/
modulo modelo.c
    Representación del modelo
    Funciones de dibujo
    Función Idle

*/
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h> // Libreria de utilidades de OpenGL
#include "practicasIG.h"
#include <vector>
#include "modelo.h"
#include "MiMalla.h"

/**	void initModel()

Inicializa el modelo y de las variables globales

**/
void initModel()
{

  glEnable(GL_DEPTH_TEST); // Habilitar el depth test
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);

  //glShadeModel(GL_SMOOTH);
}

/*
  Cambiar modo
*/

int modo = GL_FILL;
int iluminacion = 1;

void setModo(int M)
{
  modo = M;
  glPolygonMode(GL_FRONT_AND_BACK, modo);
}

// no funciona para miMalla
int getIluminacion()
{
  return iluminacion;
}

void setIluminacion(int estado)
{
  iluminacion = estado;
  if (estado)
  {
    glEnable(GL_LIGHTING); // Activa la iluminación
  }
  else
  {
    glDisable(GL_LIGHTING); // Desactiva la iluminación
  }
}

// sombreado coche: N

int sombreado = 1;

int getSombreado()
{
  return sombreado;
}

void setSombreado(int estado)
{
  sombreado = estado;
  if (estado)
  {
    glShadeModel(GL_FLAT);
  }
  else
  {
    glShadeModel(GL_SMOOTH);
  }
}

// sombreado cubo: M

int sombreado2 = 0;

int getSombreado2()
{
  return sombreado2;
}

void setSombreado2(int estado)
{
  sombreado2 = estado;
  if (estado)
  {
    glShadeModel(GL_FLAT);
  }
  else
  {
    glShadeModel(GL_SMOOTH);
  }
}


class Ejes : Objeto3D
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

    // glEnable(GL_LIGHTING);
    //  condicion aqui

    if (modo == GL_FILL && getIluminacion())
    {
      glEnable(GL_LIGHTING);
    }
  }
};

Ejes ejesCoordenadas;

// MiCubo
// glColor3f(1.0f, 0.0f, 1.0f);  // Magenta

class MiCubo : Objeto3D
{
public:
  float lado;

  MiCubo(float l)
  {
    lado = l;
  }

  void draw()
  {

    // GLfloat color[4] = {1.0f, 0.0f, 1.0f, 1.0f}; // Magenta
    // glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);

    glBegin(GL_QUADS);
    {
      // Cara delante
      glNormal3f(0, 0, 1);
      glVertex3f(0, 0, lado);
      glVertex3f(lado, 0, lado);
      glVertex3f(lado, lado, lado);
      glVertex3f(0, lado, lado);

      // Cara atrás
      glNormal3f(0, 0, -1);
      glVertex3f(0, 0, 0);
      glVertex3f(0, lado, 0);
      glVertex3f(lado, lado, 0);
      glVertex3f(lado, 0, 0);

      // Cara izquierda
      glNormal3f(-1, 0, 0);
      glVertex3f(0, 0, 0);
      glVertex3f(0, 0, lado);
      glVertex3f(0, lado, lado);
      glVertex3f(0, lado, 0);

      // Cara derecha
      glNormal3f(-1, 0, 0);
      glVertex3f(lado, 0, 0);
      glVertex3f(lado, lado, 0);
      glVertex3f(lado, lado, lado);
      glVertex3f(lado, 0, lado);

      // Cara arriba
      glNormal3f(0, 1, 0);
      glVertex3f(0, lado, 0);
      glVertex3f(0, lado, lado);
      glVertex3f(lado, lado, lado);
      glVertex3f(lado, lado, 0);

      // Cara abajo
      glNormal3f(0, -1, 0);
      glVertex3f(0, 0, 0);
      glVertex3f(lado, 0, 0);
      glVertex3f(lado, 0, lado);
      glVertex3f(0, 0, lado);
    }
    glEnd();
  }
};

MiCubo cubo1(1.0f);

// MiPiramide
class MiPiramide : Objeto3D
{
public:
  float lado;
  float alto;

  MiPiramide(float l, float h)
  {
    lado = l;
    alto = h;
  }

  void calcularNormal(float Ax, float Ay, float Az, float Bx, float By, float Bz, float Cx, float Cy, float Cz)
  {
    // Calcular los dos vectores
    // v1 -v0
    // v2 - v0
    float ux = Bx - Ax;
    float uy = By - Ay;
    float uz = Bz - Az;

    float vx = Cx - Ax;
    float vy = Cy - Ay;
    float vz = Cz - Az;

    // Calcular el producto vectorial para la normal
    float nx = uy * vz - uz * vy;
    float ny = uz * vx - ux * vz;
    float nz = ux * vy - uy * vx;

    // Normalizar la normal (opcional) hacer raiz cuadrada, si es distinto de 0 dividirlo
    float length = sqrt(nx * nx + ny * ny + nz * nz);
    if (length != 0)
    {
      nx /= length;
      ny /= length;
      nz /= length;
    }

    // Usar la normal calculada
    glNormal3f(nx, ny, nz);
  }

  void draw()
  {
    // GLfloat color[4] = {0.0f, 1.0f, 1.0f, 1.0f}; // Cyan
    // glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);

    float Cx = lado / 2.0f;
    float Cy = alto;
    float Cz = lado / 2.0f;

    glBegin(GL_TRIANGLES);
    {

      // Cara delante
      calcularNormal(0, 0, lado, lado, 0, lado, Cx, Cy, Cz);
      glVertex3f(0, 0, lado);
      glVertex3f(lado, 0, lado);
      glVertex3f(lado / 2, alto, lado / 2); // arriba

      // Cara atras
      calcularNormal(lado, 0, 0, 0, 0, 0, Cx, Cy, Cz);
      glVertex3f(lado, 0, 0);
      glVertex3f(0, 0, 0);
      glVertex3f(lado / 2, alto, lado / 2);

      // Cara derecha
      calcularNormal(lado, 0, lado, lado, 0, 0, Cx, Cy, Cz);
      glVertex3f(lado, 0, lado);
      glVertex3f(lado, 0, 0);
      glVertex3f(lado / 2, alto, lado / 2);

      // Cara izquierda
      calcularNormal(0, 0, 0, 0, 0, lado, Cx, Cy, Cz);
      glVertex3f(0, 0, 0);
      glVertex3f(0, 0, lado);
      glVertex3f(lado / 2, alto, lado / 2);
    }
    glEnd();

    // Base de la pirámide
    glBegin(GL_QUADS);
    {
      glNormal3f(0, -1, 0);
      glVertex3f(0, 0, 0);
      glVertex3f(lado, 0, 0);
      glVertex3f(lado, 0, lado);
      glVertex3f(0, 0, lado);
    }
    glEnd();
  }
};

// Ejemplo de uso
MiPiramide piramide1(1.0f, 2.0f);

/**	void Dibuja( void )

Procedimiento de dibujo del modelo. Es llamado por glut cada vez que se debe redibujar.

**/

MiMalla malla("./recursos/big_dodge.ply");
MiMalla malla2("./recursos/cubo.ply");

void Dibuja(void)
{
  static GLfloat pos[4] = {5.0, 5.0, 10.0, 0.0}; // Posicion de la fuente de luz

  float color[4] = {0.8, 0.0, 1, 1};

  glPushMatrix(); // Apila la transformacion geometrica actual

  glClearColor(0.0, 0.0, 0.0, 1.0); // Fija el color de fondo a negro
  // glClearColor(1.0, 1.0, 1.0, 1.0); // Fija el color de fondo a blanco

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Inicializa el buffer de color y el Z-Buffer

  // sombreado
  //setSombreado(sombreado);
  //setSombreado2(sombreado2);

  //
  if (modo == GL_FILL && getIluminacion())
  {
    glEnable(GL_LIGHTING);
  }
  else
  {
    glDisable(GL_LIGHTING);
  }

  // ejesCoordenadas.draw(); // Dibuja los ejes

  //glLightfv(GL_LIGHT0, GL_POSITION, pos); // Declaracion de luz. Colocada aqui esta fija en la escena

  transformacionVisualizacion(); // Carga transformacion de visualizacion
  ejesCoordenadas.draw();        // Dibuja los ejes

  glLightfv(GL_LIGHT0, GL_POSITION, pos); // Declaracion de luz. Colocada aqui esta fija en la escena

  /*
  GLfloat color3[4] = {1.0f, 0.0f, 1.0f, 1.0f}; // Magenta
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color3);
  cubo1.draw(); // dibujo el cubo
   //cubo1.draw(); // dibujo el cubo

  glTranslatef(1.2, 0, 0);



  GLfloat color2[4] = {0.0f, 1.0f, 1.0f, 1.0f}; // Cyan
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color2);
  piramide1.draw();
  */


  // coche
  glPushMatrix();
  glScalef(0.5, 0.5, 0.5);
  GLfloat color2[4] = {1.0f, 0.0f, 0.0f, 1.0f}; // Red
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color2);
  if (sombreado) {
        malla.drawSmooth(); // Dibuja con sombreado suave
    } else {
        malla.drawFlat(); // Dibuja con sombreado plano
  }
  glPopMatrix();

  // cubo
  glPushMatrix();
  glTranslatef(5, 0, 0);
  GLfloat color3[4] = {0.5f, 0.0f, 0.5f, 1.0f}; // Violet
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color3);
  if (sombreado2) {
        malla2.drawSmooth(); // Dibuja con sombreado suave
    } else {
        malla2.drawFlat(); // Dibuja con sombreado plano
  }
  glPopMatrix();


  glPopMatrix();
  glutSwapBuffers(); // Intercambia el buffer de dibujo y visualizacion
}

/**	void idle()

Procedimiento de fondo. Es llamado por glut cuando no hay eventos pendientes.

**/
void idle(int v)
{

  glutPostRedisplay();        // Redibuja
  glutTimerFunc(30, idle, 0); // Vuelve a activarse dentro de 30 ms
}
