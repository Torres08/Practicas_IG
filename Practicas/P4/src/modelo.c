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
#include "lector-jpg.h"

/**	void initModel()

Inicializa el modelo y de las variables globales

**/

/*
MiDado dado;
void initModel()
{
  glEnable(GL_DEPTH_TEST); // Habilitar el depth test
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);

  dado.asignarTextura("recursos/dado.jpg");


}
*/

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
int sombreadoBrazoMecanico = 1;

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
 * @brief Obtiene el valor del sombreado del brazo mecánico.
 * @return El valor del sombreado del brazo mecánico.
 */
int getSombreadoBrazo()
{
  return getSombreado(sombreadoBrazoMecanico);
}

/**
 * @brief Configura el estado de sombreado del brazo mecánico.
 * @param estado Un entero que indica el estado del sombreado.
 *               Si es 1, el sombreado es plano. Si es 0, el sombreado es suave.
 */
void setSombreadoBrazo(int estado)
{
  setSombreado(sombreadoBrazoMecanico, estado);
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

int numeroEscena = 4;

void setEscena(int e)
{
  numeroEscena = e;
}

int getEscena()
{
  return numeroEscena;
}

void Objeto3D::asignarTextura(const char *nombre_arch)
{
  unsigned ancho, alto;
  unsigned char *data = LeerArchivoJPEG(nombre_arch, ancho, alto);
  if (!data)
  {
    std::cerr << "Error al leer la imagen JPEG: " << nombre_arch << std::endl;
    return;
  }

  glGenTextures(1, &texId);
  glBindTexture(GL_TEXTURE_2D, texId);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, ancho, alto, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

  delete[] data;
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

  // asignar vectores texturas

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

  // asignar texturas

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

class MiDado : public Objeto3D
{
public:
  float lado;

  MiDado()
  {
    lado = 1.0f;
  }

  void draw()
  {
    // habilitar el mapeo de texturas
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texId);

    glBegin(GL_QUADS);
    {
      // Cara delante
      glNormal3f(0, 0, 1);
      glTexCoord2f(0.5, 0.5);
      glVertex3f(0, 0, lado);
      glTexCoord2f(0.75, 0.5);
      glVertex3f(lado, 0, lado);
      glTexCoord2f(0.75, 0.75);
      glVertex3f(lado, lado, lado);
      glTexCoord2f(0.5, 0.75);
      glVertex3f(0, lado, lado);

      // Cara atrás
      glNormal3f(0, 0, -1);
      glTexCoord2f(0.25, 0.5);
      glVertex3f(0, 0, 0);
      glTexCoord2f(0, 0.5);
      glVertex3f(0, lado, 0);
      glTexCoord2f(0, 0.75);
      glVertex3f(lado, lado, 0);
      glTexCoord2f(0.25, 0.75);
      glVertex3f(lado, 0, 0);

      // Cara izquierda
      glNormal3f(-1, 0, 0);
      glTexCoord2f(0.25, 0.5);
      glVertex3f(0, 0, 0);
      glTexCoord2f(0.25, 0.75);
      glVertex3f(0, 0, lado);
      glTexCoord2f(0.5, 0.75);
      glVertex3f(0, lado, lado);
      glTexCoord2f(0.5, 0.5);
      glVertex3f(0, lado, 0);

      // Cara derecha
      glNormal3f(1, 0, 0);
      glTexCoord2f(0.75, 0.5);
      glVertex3f(lado, 0, 0);
      glTexCoord2f(0.75, 0.75);
      glVertex3f(lado, lado, 0);
      glTexCoord2f(1.0, 0.75);
      glVertex3f(lado, lado, lado);
      glTexCoord2f(1.0, 0.5);
      glVertex3f(lado, 0, lado);

      // Cara arriba
      glNormal3f(0, 1, 0);
      glTexCoord2f(0.5, 0.25);
      glVertex3f(0, lado, 0);
      glTexCoord2f(0.5, 0.5);
      glVertex3f(0, lado, lado);
      glTexCoord2f(0.75, 0.5);
      glVertex3f(lado, lado, lado);
      glTexCoord2f(0.75, 0.25);
      glVertex3f(lado, lado, 0);

      // Cara abajo
      glNormal3f(0, -1, 0);
      glTexCoord2f(0.75, 0.75);
      glVertex3f(0, 0, 0);
      glTexCoord2f(0.5, 0.75);
      glVertex3f(lado, 0, 0);
      glTexCoord2f(0.5, 1.0);
      glVertex3f(lado, 0, lado);
      glTexCoord2f(0.75, 1.0);
      glVertex3f(0, 0, lado);
    }
    glEnd();
    glDisable(GL_TEXTURE_2D);
  }
};

MiDado dado;
void initModel()
{
  glEnable(GL_DEPTH_TEST); // Habilitar el depth test
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);

  dado.asignarTextura("recursos/dado.jpg");
}

MiCubo cubo1(1.0f);

// Ejemplo de uso
MiPiramide piramide1(1.0f, 2.0f);

// ejemplos de malla
MiMalla mallaCoche("./recursos/big_dodge.ply");
MiMalla mallaVaca("./recursos/cow.ply");
MiMalla mallaBeethoven("./recursos/beethoven.ply");
MiMalla mallaTeapot("./recursos/teapot.ply");
MiMalla mallaCubo("./recursos/cubo.ply");

// para el brazo mecanico
MiMalla mallaA("./recursos/Brazo/A.ply");
MiMalla mallaB("./recursos/Brazo/B.ply");
MiMalla mallaC("./recursos/Brazo/C.ply");
MiMalla mallaD("./recursos/Brazo/D.ply");
MiMalla mallaG("./recursos/Brazo/G.ply");
MiMalla mallaH("./recursos/Brazo/H.ply");
MiMalla mallaI("./recursos/Brazo/I.ply");
MiMalla mallaE("./recursos/Brazo/C.ply");
MiMalla mallaF("./recursos/Brazo/D.ply");

// clase brazo mecanico
class BrazoMecanico : public Objeto3D
{
public:
  float anguloA, anguloB, anguloC, anguloD, anguloE, anguloF, anguloG, anguloH, anguloI;

  // ANGULO POR CADA ROTACION
  BrazoMecanico()
  {
    anguloA = anguloB = anguloC = anguloD = anguloE = anguloF = anguloG = anguloH = anguloI = 0.0f;
    anguloA = 35;  // pieza B
    anguloB = 45;  // pieza C
    anguloC = 90;  // pieza D
    anguloD = 25;  // pieza E
    anguloE = 45;  // pieza F
    anguloF = 90;  // pieza G
    anguloG = -30; // Pieza H
    anguloH = 30;  // pieza I

    anguloI = 0; // este para la traslacion del palo si vale
  }

  // get & set de los angulos
public:
  // q
  float getAnguloA() { return anguloA; } // no tiene restricciones
  void setAnguloA(float angulo) { anguloA = angulo; }

  // w
  float getAnguloB() { return anguloB; }
  void setAnguloB(float angulo)
  {
    if (angulo > 70.0f)
    {
      anguloB = 70.0f;
      printf("El valor de anguloB no puede ser mayor que 70. Se ha ajustado a 70.\n");
    }
    else if (angulo < -70.0f)
    {
      anguloB = -70.0f;
      printf("El valor de anguloB no puede ser menor que -70. Se ha ajustado a -70.\n");
    }
    else
    {
      anguloB = angulo;
    }
  }

  // libre, no tiene restricciones
  // e
  float getAnguloC() { return anguloC; }
  void setAnguloC(float angulo) { anguloC = angulo; }

  // r
  float getAnguloD() { return anguloD; }
  void setAnguloD(float angulo)
  {
    if (angulo > 70.0f)
    {
      anguloD = 70.0f;
      printf("El valor de anguloD no puede ser mayor que 70. Se ha ajustado a 70.\n");
    }
    else if (angulo < -70.0f)
    {
      anguloD = -70.0f;
      printf("El valor de anguloD no puede ser menor que -70. Se ha ajustado a -70.\n");
    }
    else
    {
      anguloD = angulo;
    }
  }

  // t
  float getAnguloE() { return anguloE; }
  void setAnguloE(float angulo) { anguloE = angulo; }

  // y
  float getAnguloF() { return anguloF; }
  void setAnguloF(float angulo)
  {
    if (angulo > 120.0f)
    {
      anguloF = 120.0f;
      printf("El valor de anguloF no puede ser mayor que 120. Se ha ajustado a 120.\n");
    }
    else if (angulo < -120.0f)
    {
      anguloF = -120.0f;
      printf("El valor de anguloD no puede ser menor que -120. Se ha ajustado a -120.\n");
    }
    else
    {
      anguloF = angulo;
    }
  }

  // u
  //-5,40
  float getAnguloG() { return anguloG; }
  void setAnguloG(float angulo)
  {
    if (angulo < -50.0f)
    {
      anguloG = -50.0f;
      printf("El valor de anguloG no puede ser mayor que 40. Se ha ajustado a 40.\n");
    }
    else if (angulo > 10.0f)
    {
      anguloG = 10.0f;
      printf("El valor de anguloG no puede ser menor que -5. Se ha ajustado a -5.\n");
    }
    else
    {
      anguloG = angulo;
    }
  }

  float getAnguloH() { return anguloH; }
  void setAnguloH(float angulo)
  {
    if (angulo > 50.0f)
    {
      anguloH = 50.0f;
      printf("El valor de anguloG no puede ser mayor que 40. Se ha ajustado a 40.\n");
    }
    else if (angulo < -10.0f)
    {
      anguloH = -10.0f;
      printf("El valor de anguloG no puede ser menor que -5. Se ha ajustado a -5.\n");
    }
    else
    {
      anguloH = angulo;
    }
  }

  // a
  //  30 0
  float getAnguloI() { return anguloI; }
  void setAnguloI(float angulo)
  {
    if (angulo > 0.30f)
    {
      anguloI = 0.30f;
      printf("El valor de anguloI no puede ser mayor que 30. Se ha ajustado a 30.\n");
    }
    else if (angulo < 0.0f)
    {
      anguloI = 0.0f;
      printf("El valor de anguloI no puede ser menor que 0. Se ha ajustado a 0.\n");
    }
    else
    {
      anguloI = angulo;
    }
  }

  void A()
  {
    //
    glPushMatrix();
    // 1. Set up, poner la figura en el medio
    glTranslatef(0.35, 0.2, 0);

    mallaA.draw();
    glPopMatrix();
  }

  // rotacion sobre el eje Y
  void B()
  {
    glPushMatrix();
    // glRotatef(get_roty(), 0, 0, 1); // angulo A
    glRotatef(anguloA, 0, 0, 1);

    glTranslatef(0, 0.55, -0.5);
    mallaB.draw();

    // colocar C en B sin rotacion de C ni de -90
    glPushMatrix();
    glRotatef(11, 0, 0, 1);
    glTranslatef(-0.22, -0.53, 0.75);
    C();

    glPopMatrix();

    /*
    glPushMatrix();
    glRotatef(11, 0, 0, 1);
    glTranslatef(-0.22, -0.53, 1.5);
    E();
    glPopMatrix();
    */

    glPopMatrix();
  }

  void C()
  {
    glPushMatrix();

    // glRotatef(get_roty(), 1, 0, 0); // angulo B
    glRotatef(anguloB, 1, 0, 0);
    glTranslatef(0.22, 0.54, -0.75);
    glRotatef(-11, 0, 0, 1);
    mallaC.draw();

    glPushMatrix();
    glTranslatef(0, -0.54, 0.85);
    D();
    glPopMatrix();

    // repetimos el proceso para E F, misma pieza misma rotacion

    glPopMatrix();
  }

  void E()
  {

    glPushMatrix();

    // glRotatef(get_roty(), 1, 0, 0); // Angulo D
    glRotatef(anguloD, 1, 0, 0); // Angulo D
    glTranslatef(0.22, 0.54, -0.75);
    glRotatef(-11, 0, 0, 1);
    mallaE.draw();

    glPushMatrix();
    glTranslatef(0, -0.54, 0.85);
    F();
    glPopMatrix();

    // repetimos el proceso para E F, misma pieza misma rotacion

    glPopMatrix();
  }

  void D()
  {
    glPushMatrix();
    // glRotatef(get_roty(), 0, 0, 1);// Angulo C
    glRotatef(anguloC, 0, 0, 1); // Angulo C
    glRotatef(3, 0, 0, 1);
    glTranslatef(0, 0.54, -0.85);
    mallaD.draw();

    glPushMatrix();
    glRotatef(11, 0, 0, 1);
    glTranslatef(-0.22, -0.53, 1.5);
    E();
    glPopMatrix();

    glPopMatrix();
  }

  void F()
  {
    glPushMatrix();
    // glRotatef(get_roty(), 0, 0, 1); // Angulo E
    glRotatef(anguloE, 0, 0, 1); // Angulo E
    glRotatef(3, 0, 0, 1);
    glTranslatef(0, 0.54, -0.85);
    mallaF.draw();

    glPushMatrix();

    glTranslatef(0.15, -0.5, 1.5);
    glRotatef(9, 0, 0, 1);
    glRotatef(-90, 0, 1, 0);
    G();
    glPopMatrix();

    glPopMatrix();
  }

  void G()
  {
    glPushMatrix();

    glScaled(1.3, 1.3, 1.3);

    glRotatef(anguloF, 0, 0, 1); // Angulo F

    glPushMatrix();
    glTranslatef(0, 0, 0.118);
    glRotatef(90, 0, 1, 0);
    I();
    glPopMatrix();

    glTranslatef(-0.05, 0, 0);
    glRotatef(-23, 0, 0, 1);
    glRotatef(15, 1, 0, 0);
    glRotatef(-38, 0, 1, 0);
    glTranslated(0, 1.27, -1.65);
    mallaG.draw();

    glPopMatrix();
  }

  void I()
  {
    glPushMatrix();

    // glRotatef(get_roty(), 0, 0, 1);
    glTranslatef(0, 0, anguloI); // me gustaria moverlo sobr el eje Z, angulo I

    glPushMatrix();
    glTranslatef(-0.05, -0.01, 0.7);
    J();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.05, 0.01, 0.7);
    K();
    glPopMatrix();

    glScaled(0.8, 0.8, 0.8);
    glRotatef(-180, 1, 0, 0);
    glRotatef(90, 0, 0, 1);
    glTranslatef(-0.128, -0.055, -0.72);
    glRotatef(-23, 1, 0, 0);
    glRotatef(46, 0, 1, 0);
    glTranslatef(-0.5, 1, -1.15);
    mallaH.draw(); // traslada sobre un eje, no rota

    glPopMatrix();
  }

  void J()
  {

    glPushMatrix();

    glRotatef(anguloG, 0, 1, 0); // angulo G

    glRotatef(-135, 0, 1, 0);

    glTranslatef(-0.05, 0, -0.05);
    glRotatef(40, 0, 0, 1);
    glRotatef(-80, 1, 0, 0);
    glTranslatef(-0.65, 0.9, -1.15);
    mallaI.draw();
    glPopMatrix();
  }

  void K()
  {
    glPushMatrix();

    // glRotatef(get_roty(),0,1,0); // angulo H
    glRotatef(anguloH, 0, 1, 0); // angulo H

    glRotatef(180, 0, 0, 1);

    glRotatef(-130, 0, 1, 0);

    glTranslatef(-0.05, 0, -0.05);
    glRotatef(40, 0, 0, 1);
    glRotatef(-80, 1, 0, 0);
    glTranslatef(-0.65, 0.9, -1.15);
    mallaI.draw();
    glPopMatrix();
  }

  void animacion()
  {
    static float angulo = 0.0f;
    angulo += 1.0f;

    setAnguloA(sin(angulo * M_PI / 180.0f) * 35.0f);
    setAnguloB(sin(angulo * M_PI / 180.0f) * 70.0f);
    setAnguloC(sin(angulo * M_PI / 180.0f) * 90.0f);
    setAnguloD(sin(angulo * M_PI / 180.0f) * 70.0f);
    setAnguloE(sin(angulo * M_PI / 180.0f) * 45.0f);
    setAnguloF(sin(angulo * M_PI / 180.0f) * 120.0f);
    setAnguloG(sin(angulo * M_PI / 180.0f) * 50.0f);
    setAnguloH(sin(angulo * M_PI / 180.0f) * 50.0f);
    setAnguloI(sin(angulo * M_PI / 180.0f) * 0.30f);
  }

  // E F

  void draw()
  {

    // base
    float blanco[4] = {1, 1, 1, 1};
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, blanco);

    // set_roty(0);

    glRotated(-90, 1, 0, 0);
    glScaled(2, 2, 2);

    glPushMatrix();

    A();
    glTranslatef(0.36, -0.35, 0.5); // mirandolo sin rotated -90

    B();

    // animacion(); // aqui va bien

    // A();
    // B();
    // C();
    // D();
    // E();
    // F();
    // G();
    //  I();
    // J();

    // Pieza B

    /*
    glRotatef(anguloA, 0, 0, 1);

    glTranslatef(0, 0.55, -0.5);
    mallaB.draw();
    */

    // Pieza C
    /*
    glRotatef(anguloB, 1, 0, 0);
     glTranslatef(0.22, 0.54, -0.75);
     glRotatef(-11, 0, 0, 1);
     mallaC.draw();
     */

    // Pieza D
    /*
    glRotatef(anguloC, 0, 0, 1); // Angulo C
    glRotatef(3, 0, 0, 1);
    glTranslatef(0, 0.54, -0.85);
    mallaD.draw();
    */

    // Pieza E
    /*
    glRotatef(anguloD, 1, 0, 0); // Angulo D
    glTranslatef(0.22, 0.54, -0.75);
    glRotatef(-11, 0, 0, 1);
    mallaE.draw();
    */

    // Pieza F
    /*
    glRotatef(anguloE, 0, 0, 1); // Angulo E
     glRotatef(3, 0, 0, 1);
     glTranslatef(0, 0.54, -0.85);
     mallaF.draw();
     */

    // Pieza G
    /*
    glRotatef(anguloF, 0, 0, 1); // Angulo F
    glTranslatef(-0.05, 0, 0);
    glRotatef(-23, 0, 0, 1);
    glRotatef(15, 1, 0, 0);
    glRotatef(-38, 0, 1, 0);
    glTranslated(0, 1.27, -1.65);
    mallaG.draw();
    */

    // Pieza H
    /*
    glTranslatef(0,0,anguloI); //me gustaria moverlo sobr el eje Z, angulo I
    glScaled(0.8, 0.8, 0.8);
    glRotatef(-180, 1, 0, 0);
    glRotatef(90, 0, 0, 1);
    glTranslatef(-0.128, -0.055, -0.72);
    glRotatef(-23, 1, 0, 0);
    glRotatef(46, 0, 1, 0);
    glTranslatef(-0.5, 1, -1.15);
    mallaH.draw(); // traslada sobre un eje, no rota
    */

    // Pieza I
    // J();

    // Pieza J
    // K();

    glPopMatrix();
  }

  void draw_animacion()
  {
    // base
    float blanco[4] = {1, 1, 1, 1};
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, blanco);

    // set_roty(0);

    glRotated(-90, 1, 0, 0);
    glScaled(2, 2, 2);

    glPushMatrix();

    A();
    glTranslatef(0.36, -0.35, 0.5); // mirandolo sin rotated -90

    B();

    animacion();

    glPopMatrix();
  }
};

BrazoMecanico brazoMecanico;

void global_setAnguloA(float angulo)
{
  brazoMecanico.setAnguloA(angulo);
}

float global_getAnguloA()
{
  return brazoMecanico.getAnguloA();
}

void global_setAnguloB(float angulo)
{
  brazoMecanico.setAnguloB(angulo);
}

float global_getAnguloB()
{
  return brazoMecanico.getAnguloB();
}

void global_setAnguloC(float angulo)
{
  brazoMecanico.setAnguloC(angulo);
}

float global_getAnguloC()
{
  return brazoMecanico.getAnguloC();
}

void global_setAnguloD(float angulo)
{
  brazoMecanico.setAnguloD(angulo);
}

float global_getAnguloD()
{
  return brazoMecanico.getAnguloD();
}

void global_setAnguloE(float angulo)
{
  brazoMecanico.setAnguloE(angulo);
}

float global_getAnguloE()
{
  return brazoMecanico.getAnguloE();
}

void global_setAnguloF(float angulo)
{
  brazoMecanico.setAnguloF(angulo);
}

float global_getAnguloF()
{
  return brazoMecanico.getAnguloF();
}

void global_setAnguloG(float angulo)
{
  brazoMecanico.setAnguloG(angulo);
}

float global_getAnguloG()
{
  return brazoMecanico.getAnguloG();
}

void global_setAnguloH(float angulo)
{
  brazoMecanico.setAnguloH(angulo);
}

float global_getAnguloH()
{
  return brazoMecanico.getAnguloH();
}

void global_setAnguloI(float angulo)
{
  brazoMecanico.setAnguloI(angulo);
}

float global_getAnguloI()
{
  return brazoMecanico.getAnguloI();
}

void global_animacion()
{
  brazoMecanico.animacion();
}

int animacion = 0;

void setAnimacion(int a)
{
  animacion = a;
}

int getAnimacion()
{
  return animacion;
}

// set roty & get roty

/**
 * @brief Clase Escena
 */
class Escena
{
public:
  // constructor, dibujar ejes

  Escena()
  {
    static GLfloat pos[4] = {5.0, 5.0, 10.0, 0.0}; // Posicion de la fuente de luz

    float color[4] = {0.8, 0.0, 1, 1};

    // glPushMatrix(); // Apila la transformacion geometrica actual

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

    glLightfv(GL_LIGHT0, GL_POSITION, pos);

    // glPopMatrix();
  }

  void drawEscena1()
  {
    GLfloat color3[4] = {1.0f, 0.0f, 1.0f, 1.0f}; // Magenta
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color3);
    cubo1.draw(); // dibujo el cubo

    glTranslatef(1.2, 0, 0);

    GLfloat color2[4] = {0.0f, 1.0f, 1.0f, 1.0f}; // Cyan
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color2);
    piramide1.draw();
  }

  void drawEscena2()
  {
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
  }

  void drawEscena3()
  {
    // dibujar brazo
    glPushMatrix();
    // glScalef(0.5, 0.5, 0.5);
    GLfloat color3[4] = {1.0f, 1.0f, 1.0f, 1.0f}; // White

    if (animacion)
    {
      brazoMecanico.draw_animacion();
    }
    else
    {
      brazoMecanico.draw();
    }

    glPopMatrix();
  }

  void drawEscena4()
  {

    glPushMatrix();

    glTranslatef(-0.5, -0.5, -0.5);
    dado.draw();

    glPopMatrix();


    glPushMatrix();

    glTranslatef(-10, 0, 0);

    // Beethoven Vidrio
    mallaBeethoven.setDiffuseReflectivity(0.0f, 0.5f, 0.0f);  // Color verde difuso
    mallaBeethoven.setSpecularReflectivity(0.9f, 0.9f, 0.9f); // Alta reflectividad especular
    mallaBeethoven.setAmbientReflectivity(0.1f, 0.1f, 0.1f);  // Baja reflectividad ambiente
    mallaBeethoven.setShininess(200.0f);                      // Brillo muy alto
    mallaBeethoven.draw();
    glPopMatrix();

    glPushMatrix();

    // Vaca Goma
    glTranslatef(0, 0, 10);
    mallaVaca.setDiffuseReflectivity(0.8f, 0.0f, 0.0f);  // Color rojo difuso
    mallaVaca.setSpecularReflectivity(0.2f, 0.2f, 0.2f); // Baja reflectividad especular
    mallaVaca.setAmbientReflectivity(0.0f, 0.2f, 0.0f);  // Baja reflectividad ambiente
    mallaVaca.setShininess(20.0f);                       // Brillo bajo
    mallaVaca.draw();
    glPopMatrix();

    // hervidor Mate
    glPushMatrix();
    glTranslatef(0, 0, -10);
    mallaTeapot.setDiffuseReflectivity(0.4f, 0.4f, 0.4f);  // Color gris difuso
    mallaTeapot.setSpecularReflectivity(0.1f, 0.1f, 0.1f); // Baja reflectividad especular
    mallaTeapot.setAmbientReflectivity(0.2f, 0.2f, 0.2f);  // Baja reflectividad ambiente
    mallaTeapot.setShininess(10.0f);                       // Brillo bajo
    mallaTeapot.draw();

    glPopMatrix();

    // Coche Oro
    glPushMatrix();

    glTranslatef(10, 0, 0);
    mallaCoche.setDiffuseReflectivity(0.83f, 0.69f, 0.22f);  // Color dorado difuso
    mallaCoche.setSpecularReflectivity(0.99f, 0.94f, 0.81f); // Alta reflectividad especular
    mallaCoche.setAmbientReflectivity(0.25f, 0.20f, 0.07f);  // Reflectividad ambiente moderada
    mallaCoche.setShininess(100.0f);                         // Brillo alto
    mallaCoche.draw();

    glPopMatrix();
  }
};

/**	void Dibuja( void )

Procedimiento de dibujo del modelo. Es llamado por glut cada vez que se debe redibujar.

**/

void Dibuja(void)
{

  glPushMatrix();

  Escena escena;

  switch (numeroEscena)
  {
  case 1:
    escena.drawEscena1();
    break;

  case 2:
    escena.drawEscena2();
    break;

  case 3:
    escena.drawEscena3();
    break;

  case 4:
    escena.drawEscena4();
    break;
  }

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
