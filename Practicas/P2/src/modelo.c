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
}

int modo = GL_FILL;
int iluminacion = 1;

/**
 * @brief Poner el modo de dibujo
 */
void setModo(int M)
{
  modo = M;
  glPolygonMode(GL_FRONT_AND_BACK, modo);
}

/**
 * @brief Obtiene el valor de la iluminación.
 * @return El valor de la iluminación.
 */
int getIluminacion()
{
  return iluminacion;
}

/**
 * @brief Configura el estado de la iluminación.
 * @param estado Un entero que indica el estado de la iluminación.
 *               Si es 1, la iluminación se activa. Si es 0, la iluminación se desactiva.
 */
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

// Variables globales para sombreado del coche y cubo
// 1 smooth 0 flat 
int sombreadoCoche = 1;
int sombreadoCubo = 0;

/**
 * @brief Obtiene el valor del sombreado de un objeto.
 *
 * @param sombreadoObjeto Referencia al valor del sombreado del objeto.
 * @return El valor del sombreado del objeto. Coche o Cubo
 */
int getSombreado(int &sombreadoObjeto)
{
  return sombreadoObjeto;
}

/**
 * @brief Configura el estado de sombreado de un objeto.
 *
 * @param sombreadoObjeto Referencia al valor del sombreado del objeto.
 * @param estado Un entero que indica el estado del sombreado.
 *               Si es 1, el sombreado es plano. Si es 0, el sombreado es suave.
 */
void setSombreado(int &sombreadoObjeto, int estado)
{
  sombreadoObjeto = estado;
  if (estado)
  {
    glShadeModel(GL_FLAT); // plano
  }
  else
  {
    glShadeModel(GL_SMOOTH); // suave
  }
}

/**
 * @brief Obtiene el valor del sombreado del coche.
 * @return El valor del sombreado del coche.
 */
int getSombreadoCoche()
{
  return getSombreado(sombreadoCoche);
}

/**
 * @brief Configura el estado de sombreado del coche.
 * @param estado Un entero que indica el estado del sombreado.
 *               Si es 1, el sombreado es plano. Si es 0, el sombreado es suave.
 */
void setSombreadoCoche(int estado)
{
  setSombreado(sombreadoCoche, estado);
}

/**
 * @brief Obtiene el valor del sombreado del cubo.
 * @return El valor del sombreado del cubo.
 */
int getSombreadoCubo()
{
  return getSombreado(sombreadoCubo);
}

/**
 * @brief Configura el estado de sombreado del cubo.
 * @param estado Un entero que indica el estado del sombreado.
 *               Si es 1, el sombreado es plano. Si es 0, el sombreado es suave.
 */
void setSombreadoCubo(int estado)
{
  setSombreado(sombreadoCubo, estado);
}

/**
 * @brief Clase Eje
 */
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

/**
 * @brief Clase Cubo
 */
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

/**
 * @brief Clase Piramide
 */
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

MiMalla mallaCoche("./recursos/big_dodge.ply");
MiMalla mallaCubo("./recursos/cubo.ply");

void Dibuja(void)
{
  static GLfloat pos[4] = {5.0, 5.0, 10.0, 0.0}; // Posicion de la fuente de luz

  float color[4] = {0.8, 0.0, 1, 1};

  glPushMatrix(); // Apila la transformacion geometrica actual

  glClearColor(0.0, 0.0, 0.0, 1.0); // Fija el color de fondo a negro
  // glClearColor(1.0, 1.0, 1.0, 1.0); // Fija el color de fondo a blanco

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Inicializa el buffer de color y el Z-Buffer

  // Manejamos la luz
  if (modo == GL_FILL && getIluminacion())
  {
    glEnable(GL_LIGHTING);
  }
  else
  {
    glDisable(GL_LIGHTING);
  }

  transformacionVisualizacion(); // Carga transformacion de visualizacion
  ejesCoordenadas.draw();        // Dibuja los ejes

  glLightfv(GL_LIGHT0, GL_POSITION, pos); // Declaracion de luz. Colocada aqui esta fija en la escena

  /*
    // Practica 1: Dibujamos Triangulo y

    GLfloat color3[4] = {1.0f, 0.0f, 1.0f, 1.0f}; // Magenta
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color3);
    cubo1.draw(); // dibujo el cubo
    //cubo1.draw(); // dibujo el cubo

    glTranslatef(1.2, 0, 0);

    GLfloat color2[4] = {0.0f, 1.0f, 1.0f, 1.0f}; // Cyan
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color2);
    piramide1.draw();

  */

  // Dibujamos el coche 
  glPushMatrix();
  glScalef(0.5, 0.5, 0.5);
  GLfloat color2[4] = {1.0f, 0.0f, 0.0f, 1.0f}; // Red
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color2);
  if (sombreadoCoche)
  {
    mallaCoche.drawSmooth(); // Dibuja con sombreado suave
  }
  else
  {
    mallaCoche.drawFlat(); // Dibuja con sombreado plano
  }
  glPopMatrix();

  // Dibujamos el cubo
  glPushMatrix();
  glTranslatef(5, 0, 0);
  GLfloat color3[4] = {0.5f, 0.0f, 0.5f, 1.0f}; // Violet
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color3);
  if (sombreadoCubo)
  {
    mallaCubo.drawSmooth(); // Dibuja con sombreado suave
  }
  else
  {
    mallaCubo.drawFlat(); // Dibuja con sombreado plano
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
