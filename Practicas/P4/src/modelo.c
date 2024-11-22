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
#include "MiDado.h"
#include "Ejes.h"
#include "MiCubo.h"
#include "MiPiramide.h"
#include "MiBrazoMecanico.h"
#include "lector-jpg.h"

using namespace std;

Ejes ejesCoordenadas;

MiCubo cubo1(1.0f);
MiPiramide piramide1(1.0f, 2.0f);
MiMalla mallaCoche("./recursos/big_dodge.ply");
MiMalla mallaVaca("./recursos/cow.ply");
MiMalla mallaBeethoven("./recursos/beethoven.ply");
MiMalla mallaTeapot("./recursos/teapot.ply");
MiMalla mallaCubo("./recursos/cubo.ply");
MiMalla mallaLobo("./recursos/lobo.ply");
MiMalla mallaTaza("./recursos/mug.ply");

MiBrazoMecanico brazoMecanico;
MiDado dado;

void aplicarMaterial(const MiMalla &malla)
{
  float diffuse[3], specular[3], ambient[3];
  std::tie(diffuse[0], diffuse[1], diffuse[2]) = malla.getDiffuseReflectivity();
  std::tie(specular[0], specular[1], specular[2]) = malla.getSpecularReflectivity();
  std::tie(ambient[0], ambient[1], ambient[2]) = malla.getAmbientReflectivity();
  float shininess = malla.getShininess();

  glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
  glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
  glMaterialf(GL_FRONT, GL_SHININESS, shininess);
}

void initModel()
{
  glEnable(GL_DEPTH_TEST); // Habilitar el depth test
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);

  dado.asignarTextura("recursos/dado.jpg");
  //mallaLobo.asignarTextura("recursos/marmol.jpg");

  if (getTipoTextura)
  {
    mallaTaza.asignarTextura("recursos/madera.jpg");
    mallaLobo.asignarTextura("recursos/marmol.jpg");
  }
  else
  {
    mallaTaza.asignarTextura("recursos/marmol.jpg");
    mallaLobo.asignarTextura("recursos/madera.jpg");
  }


  // Configurar material para mallaVaca (Oro)
  mallaVaca.setDiffuseReflectivity(0.83f, 0.69f, 0.22f);  
  mallaVaca.setSpecularReflectivity(0.99f, 0.94f, 0.81f); 
  mallaVaca.setAmbientReflectivity(0.25f, 0.20f, 0.07f);  
  mallaVaca.setShininess(50.0f);                          

  // Configurar material para mallaBeethoven (Vidrio)
  mallaBeethoven.setDiffuseReflectivity(0.0f, 0.5f, 0.0f);  
  mallaBeethoven.setSpecularReflectivity(0.9f, 0.9f, 0.9f); 
  mallaBeethoven.setAmbientReflectivity(0.1f, 0.1f, 0.1f);  
  mallaBeethoven.setShininess(100.0f);                      

  // Configurar material para mallaTeapot (Plástico)
  mallaTeapot.setDiffuseReflectivity(0.0f, 0.0f, 1.0f);  
  mallaTeapot.setSpecularReflectivity(0.3f, 0.3f, 0.3f); 
  mallaTeapot.setAmbientReflectivity(0.1f, 0.1f, 0.1f);  
  mallaTeapot.setShininess(1.0f);                        
                                                         
  mallaCoche.setDiffuseReflectivity(1.0f, 0.0f, 0.0f);   
  mallaCoche.setSpecularReflectivity(0, 0, 0);           
  mallaCoche.setAmbientReflectivity(0, 0, 0);            
  mallaCoche.setShininess(0);

  // Configurar material para mallaLobo (Madera)
  mallaLobo.setDiffuseReflectivity(1.0f, 1.0f, 1.0f);  
  mallaLobo.setSpecularReflectivity(1.0f, 1.0f, 1.0f); 
  mallaLobo.setAmbientReflectivity(1.0f, 1.0f, 1.0f);  
  mallaLobo.setShininess(100.0f);                      
}

/**
 * @brief Asignar Textura a partir de una ruta de archivo.
 * 
 */
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

  // glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
  glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, ancho, alto, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

  glEnable(GL_NORMALIZE);

  delete[] data;
}

// 0: madera, 1: marmol
int tipoTextura = 0;

void setTipoTextura(int tipo)
{
  tipoTextura = tipo;
}

int getTipoTextura()
{
  return tipoTextura;
}

int cambioModelo = 0;

void setCambioModelo(int cambio)
{
  cambioModelo = cambio;
}

int getCambioModelo()
{
  return cambioModelo;
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

int getModo()
{
  return modo;
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

    aplicarMaterial(mallaCoche);
    if (sombreadoCoche)
    {
      mallaCoche.drawSmooth(); // Dibuja con sombreado suave
    }
    else
    {
      mallaCoche.drawFlat(); // Dibuja con sombreado plano
    }

    // printf("Brillo Coche: %f\n", mallaCoche.getShininess());

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
    //   printf("Brillo Cubo: %f\n", mallaCubo.getShininess());

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

    // Beethoven Vidrio
    glPushMatrix();
    glTranslatef(-10, 0, 0);
    glRotatef(get_roty(), 0, 1, 0);

    aplicarMaterial(mallaBeethoven);

    mallaBeethoven.draw();
    glPopMatrix();

    // Taza Madera
    glPushMatrix();

    if (getCambioModelo()){
      // lobo
      
      glTranslatef(10, 0, 0);
      glScalef(10, 10, 10);
      glRotatef(get_roty(), 0, 1, 0);
      glRotatef(-90, 1, 0, 0);
      aplicarMaterial(mallaLobo);
      // para solo actualizarlo una vez
      static int tipoTexturaAnterior = -1;
      if (tipoTextura != tipoTexturaAnterior)
      {
        if (tipoTextura == 0)
        {
          mallaLobo.asignarTextura("recursos/madera.jpg");
        }
        else
        {
          mallaLobo.asignarTextura("recursos/marmol.jpg");
        }
        tipoTexturaAnterior = tipoTextura; 
      }
      mallaLobo.drawConTexturaCilindrica();
      // mallaLobo.drawConTextura();
      
    } else {
      // taza
      glTranslatef(10, 0, 0);
      glScalef(5, 5, 5);
      glRotatef(get_roty(), 0, 1, 0);

      aplicarMaterial(mallaTaza);
      // para solo actualizarlo una vez
      static int tipoTexturaAnterior = -1;
      if (tipoTextura != tipoTexturaAnterior)
      {
        if (tipoTextura == 0)
        {
          mallaTaza.asignarTextura("recursos/madera.jpg");
        }
        else
        {
          mallaTaza.asignarTextura("recursos/marmol.jpg");
        }
        tipoTexturaAnterior = tipoTextura; 
      }
      mallaTaza.drawConTexturaCilindrica();
      // mallaTaza.drawConTextura();

    }


    

    

    

    glPopMatrix();

    // Vaca Oro
    glPushMatrix();
    glTranslatef(0, 0, 10);
    glRotatef(get_roty(), 0, 1, 0);

    aplicarMaterial(mallaVaca);
    mallaVaca.draw();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0, -10);
    glRotatef(get_roty(), 0, 1, 0);
    glRotatef(-90, 1, 0, 0);

    // Brillo bajo
    aplicarMaterial(mallaTeapot);
    mallaTeapot.draw();
    glPopMatrix();

    glPushMatrix();

    glRotatef(-get_roty(), 0, 1, 0);

    glTranslatef(-0.5, -0.5, -0.5);

    GLfloat color3[4] = {1.0f, 1.0f, 1.0f, 1.0f}; // Blanco
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color3);

    dado.draw();
    // cubo1.draw(); // dibujo el cubo
    // mallaCubo.draw();

    glPopMatrix();

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
