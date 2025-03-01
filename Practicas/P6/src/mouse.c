/*	Prácticas de Informática Gráfica

	Grupo C					Curso 2023-24

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

=======================================================

	 mouse.c
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include "practicasIG.h"
#include "Escena.h"

#include <unistd.h> // Añadir esta línea para declarar sleep

#define __mouse__
#include "mouse.h"

int MOUSE_LEFT_DOWN = 0;
int MOUSE_MIDDLE_DOWN = 0;
int MOUSE_RIGHT_DOWN = 0;
int MOUSE_X, MOUSE_Y;

int ISINTERACTING;

int selectedObjectId = -1;

extern bool changeLightEnabled; // Declara la variable global

void setSelectedObjectId(int id)
{
	selectedObjectId = id;
}

int getSelectedObjectId()
{
	return selectedObjectId;
}

/**

Procedimiento para gestionar los eventos de pulsacion de los botones del raton.

Argumentos:

boton: Codigo glut del boton que ha manipulado el usuario.

estado: Estado en el que esta el boton que se ha pulsado.

x,y: Posicion, en coordenadas de pantalla, en que se encuantra el cursor.

**/

void clickRaton(int boton, int estado, int x, int y)
{
	ISINTERACTING = 1;
	if (boton == GLUT_LEFT_BUTTON && estado == GLUT_DOWN)
	{
		MOUSE_LEFT_DOWN = 1;
		MOUSE_X = x;
		MOUSE_Y = y;
	}
	else if (boton == GLUT_MIDDLE_BUTTON && estado == GLUT_DOWN)
	{
		MOUSE_MIDDLE_DOWN = 1;
		MOUSE_X = x;
		MOUSE_Y = y;

		int id;
		if (pick(x, y, &id))
		{

			/*
			if (getSelectedObjectId() == id){
				printf("Deseleccionado: %d\n", id);
				selectedObjectId = -1;
			} else {
				printf("Selected object ID: %d\n", id);
				selectedObjectId = id;
			}
			*/

			// printf("Selected object ID: %d\n", id);
			selectedObjectId = id;

			// Luz
			if (selectedObjectId == 100)
			{ // 100 es boton
				setBotonAnimacionLuz(true);
				setBotonAnimacionEscena(false);
				setBotonAnimacionAccion(false);
				setBotonAnimacionDisco(false);

				setIluminacion(!getIluminacion());
			}

			// Escena
			if (selectedObjectId == 101)
			{

				setBotonAnimacionDisco(false);
				setBotonAnimacionEscena(true);
				setBotonAnimacionLuz(false);
				setBotonAnimacionAccion(false);

				if (getEscena() == 2)
				{
					printf("Cambio a Escena 1\n");
					setEscena(1);
				}
				else
				{
					printf("Cambio a Escena 2\n");
					setEscena(2);
				}
			}

			if (selectedObjectId == 102)
			{
				setBotonAnimacionDisco(false);
				setBotonAnimacionEscena(false);
				setBotonAnimacionLuz(false);
				setBotonAnimacionAccion(true);

				// printf("Boton Accion\n");

				// printf("Escenario Accion %d\n", getEscenarioAccion());
				if (getEscena() == 1)
				{
					printf("Animacion\n");
					setAnimacion(!getAnimacion());
					// printf("Modo Animacion: %d\n", getAnimacion());
				}
				else
				{
					/*

					*/
					int siguiente_escenario = getEscenarioAccion() + 1;
					if (siguiente_escenario > 8)
					{
						siguiente_escenario = 1;
					}

					switch (siguiente_escenario)
					{
					case 1:
						printf("Dibujado Flat\n");
						break;
					case 2:
						printf("Dibujado Smooth\n");
						break;
					case 3:
						printf("Material Oro\n");
						break;
					case 4:
						printf("Dibujado con lineas\n");
						break;
					case 5:
						printf("Texturizado Cilíndrico\n");
						cambioTexturaManzana(1);
						break;
					case 6:
						printf("Texturizado Automatica lineal de OpenGL\n");
						cambioTexturaManzana(2);
						break;
					case 7:
						printf("Texturizado Esférico\n");
						cambioTexturaManzana(3);
						break;
					case 8:
						printf("Dado\n");
						break;
					}

					setEscenarioAccion(siguiente_escenario);
				}
			}

			// Disco
			if (selectedObjectId == 103)
			{
				printf("Discoteca\n");
				setBotonAnimacionDisco(true);
				setBotonAnimacionLuz(false);
				setBotonAnimacionEscena(false);
				setBotonAnimacionAccion(false);

				set_changeLightEnabled(!get_changeLightEnabled());

				if (!get_changeLightEnabled())
				{
					setIluminacion(true);
				}
			}
		}
		else
		{
			printf("No object selected.\n");
			selectedObjectId = -1; // No hay ningún objeto seleccionado
		}
	}
	else if (boton == GLUT_RIGHT_BUTTON && estado == GLUT_DOWN)
	{
		MOUSE_RIGHT_DOWN = 1;
		MOUSE_X = x;
		MOUSE_Y = y;
	}
	else
	{
		MOUSE_LEFT_DOWN = 0;
		MOUSE_MIDDLE_DOWN = 0;
		MOUSE_RIGHT_DOWN = 0;
		ISINTERACTING = 0;
	}
	glutPostRedisplay();
}

/**

Procedimiento para gestionar los eventos de movimiento del raton.

Argumentos:

x,y: Posicion, en coordenadas de pantalla, en que se encuantra el cursor.

**/

void RatonMovido(int x, int y)
{
	char texto[30];
	float ax, ay, az, d;
	getCamara(ax, ay, az, d);
	if (MOUSE_LEFT_DOWN)
	{
		if (x != MOUSE_X)
			ay += x - MOUSE_X;
		if (y != MOUSE_Y)
			ax += y - MOUSE_Y;
		setCamara(ax, ay, az, d);
	}
	else if (MOUSE_RIGHT_DOWN)
	{
		//   if(x!=MOUSE_X) z_camara=10.0*(anchoVentana/2-MOUSE_X)/(x+1.0);
		if (y != MOUSE_Y)
		{
			d += 100.0 * (y - MOUSE_Y) / 200; // escalar el zoom
			setCamara(ax, ay, az, d);
		}
	}
	else if (MOUSE_MIDDLE_DOWN)
	{
		if (x != MOUSE_X)
			az += x - MOUSE_X;
		if (y != MOUSE_Y)
			ax += y - MOUSE_Y;
		setCamara(ax, ay, az, d);
	}
	MOUSE_X = x;
	MOUSE_Y = y;
	glutPostRedisplay();
}
