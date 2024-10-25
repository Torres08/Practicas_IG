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
modulo entradaTeclado.c
  Gestion de eventos de teclado
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h> // Libreria de utilidades de OpenGL
#include "practicasIG.h"
/**

Imprime en la consola las instrucciones del programa

**/
void printHelp()
{

  printf("\n\n     Prácticas de Informática Gráfica	Curso 2023-2024");
  printf("\n\n Dpto. Lenguajes y Sistemas Informaticos");
  printf("\n E.T.S.I. Informatica		Univ. de Granada ");
  printf("\n");
  printf("\n Opciones: \n\n");
  printf("h, H: Imprime informacion de ayuda \n");
  printf("PgUp, PgDn: avanza y retrocede la cámara \n\n");
  printf("+,-: avanza y retrocede la cámara \n\n");
  printf("Teclas de movimiento de cursor: giran la camara\n");
  // Anyade la informacion de las opciones que introduzcas aqui !!

  printf("\n Escape: Salir");
  printf("\n\n\n");
}

/* @teclado ---------------------------------------------------------------- */

/** 		void letra (unsigned char k, int x, int y)

Este procedimiento es llamado por el sistema cuando se pulsa una tecla normal
El codigo k es el ascii de la letra

Para anyadir nuevas ordenes de teclado coloca el correspondiente case.

Parametros de entrada:

k: codigo del caracter pulsado

x:

y:

**/

float rotxCamara = 30, rotyCamara = 45;
float dCamara = 10;

void letra(unsigned char k, int x, int y)
{

  switch (k)
  {

  case '1':
    // dibujar escena 1
    // Escena escena;
    setEscena(1);
    printf("Escena 1\n");
    // hazlo como ilumincacion
    break;

  case '2':
    // dibujar escena 2
    // Escena escena;
    setEscena(2);
    printf("Escena 2\n");
    break;

  case '3':
    // dibujar escena 3
    // Escena escena;
    setEscena(3);
    printf("Escena 3\n");
    break;

  case 'q':
    // dibujar escena 3
    // Escena escena;
    {
      printf("Angulo A: %f\n", global_getAnguloA());
      float nuevo = global_getAnguloA() - 5.0;
      global_setAnguloA(nuevo);
    }
    break;

  case 'Q':
    // dibujar escena 3
    // Escena escena;
    {
      printf("Angulo A: %f\n", global_getAnguloA());
      float nuevo = global_getAnguloA() + 5.0;
      global_setAnguloA(nuevo);
    }
    break;

  case 'w':
  {
    printf("Angulo B: %f\n", global_getAnguloB());
    float nuevo = global_getAnguloB() - 5.0;
    global_setAnguloB(nuevo);
  }
  break;

  case 'W':
  {
    printf("Angulo B: %f\n", global_getAnguloB());
    float nuevo = global_getAnguloB() + 5.0;
    global_setAnguloB(nuevo);
  }
  break;

  case 'e':
  {
    printf("Angulo C: %f\n", global_getAnguloC());
    float nuevo = global_getAnguloC() - 5.0;
    global_setAnguloC(nuevo);
  }
  break;

  case 'E':
  {
    printf("Angulo C: %f\n", global_getAnguloC());
    float nuevo = global_getAnguloC() + 5.0;
    global_setAnguloC(nuevo);
  }
  break;

  case 'r':
  {
    printf("Angulo D: %f\n", global_getAnguloD());
    float nuevo = global_getAnguloD() - 5.0;
    global_setAnguloD(nuevo);
  }
  break;

  case 'R':
  {
    printf("Angulo D: %f\n", global_getAnguloD());
    float nuevo = global_getAnguloD() + 5.0;
    global_setAnguloD(nuevo);
  }
  break;

  case 't':
  {
    printf("Angulo E: %f\n", global_getAnguloE());
    float nuevo = global_getAnguloE() - 5.0;
    global_setAnguloE(nuevo);
  }
  break;

  case 'T':
  {
    printf("Angulo E: %f\n", global_getAnguloE());
    float nuevo = global_getAnguloE() + 5.0;
    global_setAnguloE(nuevo);
  }
  break;

  case 'y':
  {
    printf("Angulo F: %f\n", global_getAnguloF());
    float nuevo = global_getAnguloF() - 5.0;
    global_setAnguloF(nuevo);
  }
  break;

  case 'Y':
  {
    printf("Angulo F: %f\n", global_getAnguloF());
    float nuevo = global_getAnguloF() + 5.0;
    global_setAnguloF(nuevo);
  }
  break;

  case 'u':
  {
    printf("Angulo G: %f\n", global_getAnguloG());
    float nuevo = global_getAnguloG() - 5.0;
    global_setAnguloG(nuevo);

    printf("AnguloH: %f\n", global_getAnguloH());
    float nuevoH = global_getAnguloH() + 5.0;
    global_setAnguloH(nuevoH);
  }
  break;

  case 'U':
  {
    printf("Angulo G: %f\n", global_getAnguloG());
    float nuevo = global_getAnguloG() + 5.0;
    global_setAnguloG(nuevo);

    printf("AnguloH: %f\n", global_getAnguloH());
    float nuevoH = global_getAnguloH() - 5.0;
    global_setAnguloH(nuevoH);
  }
  break;

  case 'a':
  {
    printf("AnguloI: %f\n", global_getAnguloI());
    float nuevoI = global_getAnguloI() - 0.05;
    global_setAnguloI(nuevoI);
  }
  break;

  case 'A':
  {
    printf("AnguloI: %f\n", global_getAnguloI());
    float nuevoI = global_getAnguloI() + 0.05;
    global_setAnguloI(nuevoI);
  }
  break;

  case 'S':
  case 's': // coche
    printf("Animacion\n");
    setAnimacion(!getAnimacion());
    printf("Modo Animacion: %d\n", getAnimacion());
    //global_animacion();
    break;

  case 'n':
  case 'N': // coche
    setSombreadoCoche(!getSombreadoCoche());
    printf("Sombreado Coche: %d\n", getSombreadoCoche());
    break;

  case 'm':
  case 'M': // cubo
    setSombreadoCubo(!getSombreadoCubo());
    printf("Sombreado Cubo: %d\n", getSombreadoCubo());
    break;

  case 'p':
  case 'P': // punto
    setModo(GL_POINT);
    break;

  case 'l':
  case 'L': // linea
    setModo(GL_LINE);
    break;

  case 'f':
  case 'F': // relleno
    setModo(GL_FILL);
    break;

  case 'i':
  case 'I': // activar desactivar iluminacion
    setIluminacion(!getIluminacion());
    printf("iluminacion: %d\n", getIluminacion());
    break;

  case 'h':
  case 'H':
    printHelp(); // H y h imprimen ayuda
    break;
  case '+': // acerca la cámara
    dCamara -= 5.0;
    break;
  case '-': // aleja la cámara
    dCamara += 5.0;
    break;
  case 27: // Escape  Terminar
    exit(0);
  default:
    return;
  }
  // setCamara (rotxCamara, rotyCamara, 0.0, dCamara);
  glutPostRedisplay(); // Algunas de las opciones cambian paramentros
} // de la camara. Es necesario actualziar la imagen

/**		void especial(int k, int x, int y)
Este procedimiento es llamado por el sistema cuando se pulsa una tecla
especial. El codigo k esta definido en glut mediante constantes

Parametros de entrada:

k: codigo del caracter pulsado (definido en glut mediante constantes).

x:

y:

**/
void especial(int k, int x, int y)
{

  switch (k)
  {
  case GLUT_KEY_UP:
    rotxCamara += 5.0; // Cursor arriba + rotacion x
    if (rotxCamara > 360)
      rotxCamara -= 360;
    break;
  case GLUT_KEY_DOWN:
    rotxCamara -= 5.0;
    if (rotxCamara < 0)
      rotxCamara += 360;
    break;
  case GLUT_KEY_LEFT:
    rotyCamara += 5.0;
    if (rotyCamara > 360)
      rotyCamara -= 360;
    break;
  case GLUT_KEY_RIGHT:
    rotyCamara -= 5.0;
    if (rotyCamara < 0)
      rotyCamara += 360;
    break;
  case GLUT_KEY_PAGE_DOWN: // acerca la cámara
    dCamara -= 5.0;
    break;
  case GLUT_KEY_PAGE_UP: // aleja la cámara
    dCamara += 5.0;
    break;
  default:
    return;
  }
  setCamara(rotxCamara, rotyCamara, 0.0, dCamara);
  glutPostRedisplay(); // Actualiza la imagen (ver proc. letra)
}
