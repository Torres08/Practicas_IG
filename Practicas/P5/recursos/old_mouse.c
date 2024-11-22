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
#include "modelo.h"

#define __mouse__
#include "mouse.h"

int MOUSE_LEFT_DOWN = 0;
int MOUSE_MIDDLE_DOWN = 0;
int MOUSE_RIGHT_DOWN = 0;
int MOUSE_X, MOUSE_Y;

int ISINTERACTING;

/**

Procedimiento para gestionar los eventos de pulsacion de los botones del raton.

Argumentos:

boton: Codigo glut del boton que ha manipulado el usuario.

estado: Estado en el que esta el boton que se ha pulsado.

x,y: Posicion, en coordenadas de pantalla, en que se encuantra el cursor.

**/

int selectedObjectId = -1;

void setSelectedObjectId(int id)
{
	selectedObjectId = id;
}

int getSelectedObjectId()
{
	return selectedObjectId;
}

int isDragging = 0; // Estado de arrastre
//float objectPosX = 0.0f, objectPosY = 0.0f;
//float lastMouseX = 0.0f, lastMouseY = 0.0f;

/*
void setObjectPosX(float x)
{
	objectPosX = x;
}

float getObjectPosX()
{
	return objectPosX;
}

void setObjectPosY(float y)
{
	objectPosY = y;
}

float getObjectPosY()
{
	return objectPosY;
}

void setLastMouseX(float x)
{
	lastMouseX = x;
}
*/

/*
void clickRaton(int boton, int estado, int x, int y)
{
	ISINTERACTING = 1;
	if (boton == GLUT_LEFT_BUTTON && estado == GLUT_DOWN)
	{
		MOUSE_LEFT_DOWN = 1;
		MOUSE_X = x;
		MOUSE_Y = y;

		if (getEscena() == 5)
		{
			int id;
			if (pick(x, y, &id))
			{
				printf("Seleccionado: %d\n", id);
				setSelectedObjectId(id);
				isDragging = 1;
				lastMouseX = x;
				lastMouseY = y;
				//glutPostRedisplay();
			}
			else
			{
				printf("No seleccionado\n");
				setSelectedObjectId(-1);
				isDragging = 0;

			}
		}
	}
	else if (boton == GLUT_MIDDLE_BUTTON && estado == GLUT_DOWN)
	{
		MOUSE_MIDDLE_DOWN = 1;
		MOUSE_X = x;
		MOUSE_Y = y;
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
*/
void clickRaton(int boton, int estado, int x, int y)
{
	if (boton == GLUT_LEFT_BUTTON && estado == GLUT_DOWN)
	{
		int id;
		if (pick(x, y, &id))
		{
			printf("Selected object ID: %d\n", id);
			selectedObjectId = id; // Actualizar el ID del objeto seleccionado
			isDragging = 1;		   // Iniciar arrastre
			//lastMouseX = x;
			//lastMouseY = y;
		}
		else
		{
			printf("No object selected.\n");
			selectedObjectId = -1; // No hay ningún objeto seleccionado
			isDragging = 0;		   // Detener arrastre
		}
	}
	else if (boton == GLUT_LEFT_BUTTON && estado == GLUT_UP)
	{
		isDragging = 0; // Detener arrastre
	}
	else if (boton == GLUT_MIDDLE_BUTTON && estado == GLUT_DOWN)
	{
		MOUSE_MIDDLE_DOWN = 1;
		MOUSE_X = x;
		MOUSE_Y = y;
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
	printf("IsDragging: %d\n", isDragging);

	if (MOUSE_LEFT_DOWN && !isDragging)
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


/*
void RatonMovido(int x, int y)
{
	char texto[30];
	float ax, ay, az, d;
	getCamara(ax, ay, az, d);

	//printf("IsDragging: %d\n", isDragging);

	if (isDragging && selectedObjectId != -1)
	{
		
		float dx = x - lastMouseX;
		float dy = y - lastMouseY;

		// Actualizar la posición del objeto basado en el movimiento del mouse
		objectPosX += dx * 0.01f; // Ajusta el factor de escala según sea necesario
		objectPosY -= dy * 0.01f; // Ajusta el factor de escala según sea necesario

		lastMouseX = x;
		lastMouseY = y;

		glutPostRedisplay(); // Solicitar redibujar la escena
		
	}
	else if (MOUSE_LEFT_DOWN && !isDragging)
	{
		if (x != MOUSE_X)
			ay += x - MOUSE_X;
		if (y != MOUSE_Y)
			ax += y - MOUSE_Y;
		setCamara(ax, ay, az, d);
	}
	else if (MOUSE_RIGHT_DOWN)
	{
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
*/

