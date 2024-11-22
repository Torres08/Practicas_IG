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
#include "mouse.h"
using namespace std;

/**
 * Creo aqui todos los objetos que voy a utilizar
 */

Ejes ejesCoordenadas;
MiBrazoMecanico brazoMecanico;
MiDado dado;

MiCubo cubo1(1.0f);
MiPiramide piramide1(1.0f, 2.0f);
MiMalla mallaCoche("./recursos/big_dodge.ply");
MiMalla mallaVaca("./recursos/cow.ply");
MiMalla mallaBeethoven("./recursos/beethoven.ply");
MiMalla mallaTeapot("./recursos/teapot.ply");
MiMalla mallaCubo("./recursos/cubo.ply");
MiMalla mallaLobo("./recursos/lobo.ply");
MiMalla mallaTaza("./recursos/mug.ply");
MiMalla mallaManzana("./recursos/apple.ply");

/**
 * @brief Aplicar material a una malla.
 * @param malla La malla a la que se le aplicará el material.
 */
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

/**
 * @brief Inicializa las variables del modelo
 * @note Esta función se llama desde el main. Aqui inicializo tanto texturas como materiales.
 */
void initModel()
{
  glEnable(GL_DEPTH_TEST); // Habilitar el depth test
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);

  dado.asignarTextura("recursos/dado.jpg");
  mallaLobo.asignarTextura("recursos/lobo.jpeg");

  // mallaLobo.asignarTextura("recursos/marmol.jpg");

  if (getTipoTextura)
  {
    mallaTaza.asignarTextura("recursos/madera.jpg");
    mallaLobo.asignarTextura("recursos/lobo.jpeg");
  }
  else
  {
    mallaTaza.asignarTextura("recursos/madera.jpeg");
    mallaLobo.asignarTextura("recursos/taza.jpg");
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

  // coche no le aplico valores (aunque se ven los valores por defecto)
  mallaCoche.setDiffuseReflectivity(1.0f, 0.0f, 0.0f);
  mallaCoche.setSpecularReflectivity(0, 0, 0);
  mallaCoche.setAmbientReflectivity(0, 0, 0);
  mallaCoche.setShininess(0);

  // Configurar material para mallaLobo por defecto
  mallaLobo.setDiffuseReflectivity(1.0f, 1.0f, 1.0f);
  mallaLobo.setSpecularReflectivity(1.0f, 1.0f, 1.0f);
  mallaLobo.setAmbientReflectivity(1.0f, 1.0f, 1.0f);
  mallaLobo.setShininess(100.0f);

  mallaManzana.setDiffuseReflectivity(1.0f, 0.0f, 0.0f);
  mallaManzana.setSpecularReflectivity(0, 0, 0);
  mallaManzana.setAmbientReflectivity(0, 0, 0);
  mallaManzana.setShininess(0);
}

/**
 * @brief Asignar Textura a partir de una ruta de archivo.
 * @note Con GL_DECAL se ve la textura sin sombra y bien iluminada
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

/**
 * @brief TipoTextura set y get para manejar desde la entrada teclado el tipo de textura
 * @param tipo 0: madera, 1: marmol
 */
int tipoTextura = 0;

void setTipoTextura(int tipo)
{
  tipoTextura = tipo;
}

int getTipoTextura()
{
  return tipoTextura;
}

/**
 * @brief CambioModelo set y get para manejar desde la entrada teclado la malla a dibujar con textura
 * @param tipo 0: taza, 1: lobo
 */
int cambioModelo = 1;

void setCambioModelo(int cambio)
{
  cambioModelo = cambio;
}

int getCambioModelo()
{
  return cambioModelo;
}

/**
 * @brief get y set para jugar con la iluminacion y el modo (fill)
 */

int modo = GL_FILL;
int iluminacion = 1;

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
 * @brief Variables globales para sombreado del coche y cubo por separado
 * @note 1: suave, 0: plano
 */
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

/**
 * @brief Get y set para cambiar la escena
 */

int numeroEscena = 5;

void setEscena(int e)
{
  numeroEscena = e;
}

int getEscena()
{
  return numeroEscena;
}

/**
 * @brief Get y set para cambiar angulo para cada punto del brazo Mecánico
 */

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

/**
 * @brief Get y set para cinicializar la animacion, ademas de la funcion global_animacion para llamar a la animacion directamente
 */

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

/**
 * @brief Color Seleccion para el raton
 * @param id id del objeto seleccionado
 * @note Asigna un color unico a cada objeto basado en su identificador
 */
void ColorSeleccion(int i)
{
  unsigned char r = (i & 0xFF);
  glColor3ub(r, 0, 0);
}

/**
 * @brief Pick para seleccionar objetos
 * @param x coordenada x
 * @param y coordenada y
 * @param i identificador del objeto seleccionado
 * @note Lee el color del pixel y decodifica el identificador del objeto seleccionado
 */
int pick(int x, int y, int *i)
{
  GLint viewport[4];
  unsigned char data[4];
  int f = 0;

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
    f = 1;
  *i = data[0];

  glPopAttrib(); // Restaurar el estado anterior de OpenGL

  return f;
}
/**
 * @brief Clase Escena, cada escena contiene cada practica
 */
class Escena
{
public:
  /**
   * @brief Constructor de la clase Escena.
   * @note COntiene todo lo que necesita y comparte cada escena
   */

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

  /**
   * @brief Escena P1
   */
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

  /**
   * @brief Escena P2
   */
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

  /**
   * @brief Escena P3
   */
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

  /**
   * @brief Escena P4
   */
  void drawEscena4()
  {
    glPushMatrix();

    // Beethoven
    glPushMatrix();
    glTranslatef(-10, 0, 0);
    glRotatef(get_roty(), 0, 1, 0);

    aplicarMaterial(mallaBeethoven);

    mallaBeethoven.draw();
    glPopMatrix();

    // Taza con textura
    glPushMatrix();

    if (getCambioModelo())
    {
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
          mallaLobo.asignarTextura("recursos/lobo.jpeg");
          mallaLobo.drawLobo();
        }
        else
        {
          mallaLobo.asignarTextura("recursos/marmol.jpg");
          mallaLobo.drawConTexturaCilindrica();
        }
        tipoTexturaAnterior = tipoTextura;
      }
      // mallaLobo.drawConTexturaCilindrica();
      mallaLobo.drawLobo();
    }
    else
    {
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
      // mallaTaza.drawConTexturaCilindrica();
      mallaTaza.drawConTextura();
    }

    glPopMatrix();

    // Vaca Oro
    glPushMatrix();
    glTranslatef(0, 0, 10);
    glRotatef(get_roty(), 0, 1, 0);

    aplicarMaterial(mallaVaca);
    mallaVaca.draw();
    glPopMatrix();

    // Tetera
    glPushMatrix();
    glTranslatef(0, 0, -10);
    glRotatef(get_roty(), 0, 1, 0);
    glRotatef(-90, 1, 0, 0);

    aplicarMaterial(mallaTeapot);
    mallaTeapot.draw();
    glPopMatrix();

    // Dado
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


  void drawEscena5(bool seleccion)
  {

    /*
      ID Lobo: 6
      ID Manzana: 8
      ID Cubo: 5
      ID taza: 7
    */

    // printf("Get Selected objetd: %d", getSelectedObjectId());

    if (seleccion)
    {
      glPushAttrib(GL_ALL_ATTRIB_BITS); // Guardar el estado actual de OpenGL
      glDisable(GL_LIGHTING);
      glDisable(GL_DITHER);
      glDisable(GL_TEXTURE_2D);
      glDisable(GL_BLEND);
      glDisable(GL_FOG);
      glDisable(GL_MULTISAMPLE);
    }

    // taza
    glPushMatrix();
    glTranslatef(1.5, 0, 0);
    glScalef(5, 5, 5);

    if (seleccion)
    {
      ColorSeleccion(mallaManzana.getId());
    }
    else
    {
      GLfloat color5[4] = {1.0f, 0.0f, 0.0f, 1.0f};
      glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color5);
    }

    if (getSelectedObjectId() == mallaManzana.getId())
    {
      mallaManzana.drawWithOutlineNormal();
    }
    else
    {
      mallaManzana.draw();
    }

    glPopMatrix();

    // cubo
    glPushMatrix();
    glTranslatef(-1.6, 0.2, 0);
    glScalef(0.5, 0.5, 0.5);

    if (seleccion)
    {
      ColorSeleccion(mallaCubo.getId());
    }
    else
    {
      GLfloat color6[4] = {0.0f, 1.0f, 0.0f, 1.0f};
      glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color6);
    }

    if (getSelectedObjectId() == mallaCubo.getId())
    {
      mallaCubo.drawWithOutlineNormal();
    }
    else
    {
      mallaCubo.draw();
    }

    glPopMatrix();

    // taza
    glPushMatrix();

    glTranslatef(0.0, 0.0, -3.0);
    //glScalef(5, 5, 5);

    if (seleccion)
    {
      ColorSeleccion(mallaTaza.getId());
      aplicarMaterial(mallaTaza);
      mallaTaza.draw(); // Dibujar sin textura
    }
    else
    {
      aplicarMaterial(mallaTaza);
      if (getSelectedObjectId() == mallaTaza.getId())
      {
      mallaTaza.drawWithOutlineTextura();
      }
      else
      {
      mallaTaza.drawConTextura();
      }
    }

    glPopMatrix();

    // lobo
    glPushMatrix();

    glTranslatef(0.0, 0.0, 3.0);
    glScalef(5, 5, 5);
    glRotatef(-90,1,0,0);

    if (seleccion)
    {
      ColorSeleccion(mallaLobo.getId());
      aplicarMaterial(mallaLobo);
      mallaLobo.draw(); // Dibujar sin textura, si no no va 
    }
    else
    {
      aplicarMaterial(mallaLobo);
      if (getSelectedObjectId() == mallaLobo.getId())
      {
      mallaLobo.drawWithOutlineLobo();
      }
      else
      {
      mallaLobo.drawLobo();
      }
    }

    glPopMatrix();
    
    if (seleccion)
    {
      glPopAttrib(); // Restaurar el estado anterior de OpenGL
    }
  }
};

/**
 * @brief Dibuja el modelo.
 * @note Procedimiento de dibujo del modelo. Es llamado por glut cada vez que se debe redibujar.
 */
void dibujoEscena(bool seleccion)
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

  case 5:
    escena.drawEscena5(seleccion);
    break;
  }

  glPopMatrix();
}

void Dibuja(void)
{
  dibujoEscena(false);
  glutSwapBuffers();
}

/**
 * @brief Procedimiento de fondo.
 * @note Es llamado por glut cuando no hay eventos pendientes.
 */
void idle(int v)
{
  glutPostRedisplay();        // Redibuja
  glutTimerFunc(30, idle, 0); // Vuelve a activarse dentro de 30 ms
}
