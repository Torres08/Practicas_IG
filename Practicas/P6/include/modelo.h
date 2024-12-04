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

=======================================================

	 modelo.h
*/

#ifndef MODELO_H
#define MODELO_H

/**
	Funcion de redibujado. Se ejecuta con los eventos postRedisplay
**/
void Dibuja (void);

/**
	Funcion de fondo
**/
void idle (int v);

/**
	Funcion de inicializacion del modelo y de las variables globales
**/
void initModel ();

void setEscena(int e);

int getEscena();

void setModo(int M);

int getModo();

int getIluminacion();

void setIluminacion(int estado);

void ColorSeleccion(int id);

int pick(int x, int y, int *id);

void dibujoEscena(bool seleccion);


class Objeto3D
{
public:
	virtual void draw() = 0; // Dibuja el objeto
	void asignarTextura(const char *nombre_arch);
	GLuint getTextId() { return texId; } // Nuevo método para obtener texId
protected:
	GLuint texId;
};

#endif // MODELO_H


