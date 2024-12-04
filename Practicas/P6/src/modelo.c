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
#include "Escena.h"

/**	void initModel()

Inicializa el modelo y de las variables globales

**/

int numeroEscena = 1;
int modo = GL_FILL;
int iluminacion = 1; // encendido

void initModel()
{
  glEnable(GL_DEPTH_TEST); // Habilitar el depth test
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
}

/**
 * @brief Get y set para cambiar la escena
 */
void setEscena(int e)
{
  numeroEscena = e;
}

int getEscena()
{
  return numeroEscena;
}

/**
 * @brief Funciones modo e iluminacion
 */
void setModo(int M)
{
  modo = M;
  glPolygonMode(GL_FRONT_AND_BACK, modo);
}

int getModo()
{
  return modo;
}

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

/**
 * @brief Color Seleccion para el raton
 * @param id id del objeto seleccionado
 * @note Asigna un color unico a cada objeto basado en su identificador
 */
void ColorSeleccion(int id)
{
  printf("Color seleccion: %d\n", id);
  unsigned char r = (id & 0xFF);
  glColor3ub(r, 0, 0);
}

/**
 * @brief Pick para seleccionar objetos
 * @param x coordenada x
 * @param y coordenada y
 * @param id identificador del objeto seleccionado
 * @note Lee el color del pixel y decodifica el identificador del objeto seleccionado
 */
int pick(int x, int y, int *id)
{
  GLint viewport[4];
  unsigned char data[4];
  int found = 0;

  glGetIntegerv(GL_VIEWPORT, viewport);
  glPushAttrib(GL_ALL_ATTRIB_BITS); // Guardar el estado actual de OpenGL
  glDisable(GL_DITHER);
  glDisable(GL_LIGHTING);
  glDisable(GL_TEXTURE_2D);
  glDisable(GL_BLEND);
  glDisable(GL_FOG);
  glDisable(GL_MULTISAMPLE);
  glClearColor(0, 0, 0, 1); // Fija el color de fondo a negro
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Dibujar la escena en modo de selección
  dibujoEscena(true);

  glFlush();
  glReadPixels(x, viewport[3] - y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, data);
  if (data[0] > 0)
    found = 1;
  *id = data[0];

  glPopAttrib(); // Restaurar el estado anterior de OpenGL

  return found;
}

void dibujoEscena(bool seleccion)
{
  glPushMatrix();

  Escena escena;

  // Iluminación
  if (getModo() == GL_FILL && getIluminacion())
  {
    glEnable(GL_LIGHTING);
  }
  else
  {
    glDisable(GL_LIGHTING);
  }

  switch (numeroEscena)
  {
  case 1:
    glPushMatrix();
    escena.Escena1(seleccion);
    glPopMatrix();

    break;
  case 2:
    glPushMatrix();
    escena.Escena2(seleccion);
    glPopMatrix();
    break;
  }

  glPopMatrix();
}

void Dibuja(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  dibujoEscena(false);
  glutSwapBuffers();
}

/**	void idle()

Procedimiento de fondo. Es llamado por glut cuando no hay eventos pendientes.

**/
void idle(int v)
{
  glutPostRedisplay();        // Redibuja
  glutTimerFunc(30, idle, 0); // Vuelve a activarse dentro de 30 ms
}
