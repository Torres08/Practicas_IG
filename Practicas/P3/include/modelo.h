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
void Dibuja(void);

/**
	Funcion de fondo
**/
void idle(int v);

/**
	Funcion de inicializacion del modelo y de las variables globales
**/
void initModel();

void setModo(int M);

void setIluminacion(int estado);

int getIluminacion();

void setSombreadoCoche(int estado);

int getSombreadoCoche();

void setSombreadoCubo(int estado);

int getSombreadoCubo();

void setEscena(int e);

int getEscena();

void global_setAnguloA(float angulo);
float global_getAnguloA();

void global_setAnguloB(float angulo);
float global_getAnguloB();

void global_setAnguloC(float angulo);
float global_getAnguloC();

void global_setAnguloD(float angulo);
float global_getAnguloD();

void global_setAnguloE(float angulo);
float global_getAnguloE();

void global_setAnguloF(float angulo);
float global_getAnguloF();

void global_setAnguloG(float angulo);
float global_getAnguloG();

void global_setAnguloH(float angulo);
float global_getAnguloH();

void global_setAnguloI(float angulo);
float global_getAnguloI();

/**
 * @brief Clase objeto 3D
 */
class Objeto3D
{
public:
	virtual void draw() = 0; // Dibuja el objeto
};

#endif // MODELO_H
