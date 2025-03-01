// Escena.h
#ifndef ESCENA_H
#define ESCENA_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/gl.h>
#include "Ejes.h"
#include "MiMalla.h"
#include "practicasIG.h"
#include "modelo.h"
#include "boton.h"
#include "mouse.h"
#include "MiBrazoMecanico.h"
#include "MiDado.h"


extern bool botonAnimacionLuz;

bool getBotonAnimacionLuz();
void setBotonAnimacionLuz(bool value);

extern bool botonAnimacionEscena;

bool getBotonAnimacionEscena();
void setBotonAnimacionEscena(bool value);

extern bool botonAnimacionAccion;

bool getBotonAnimacionAccion();
void setBotonAnimacionAccion(bool value);

extern bool botonAnimacionDisco;

bool getBotonAnimacionDisco();
void setBotonAnimacionDisco(bool value);

void initModelEscena();

void cambioTexturaManzana(int value);

void setAnimacion(int a);
int getAnimacion();	

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

void aplicarMaterial(const MiMalla &malla);

class Escena
{
private:
    
public:
    Escena();

    void configurarSeleccion();
    void restaurarEstado();

    void Escena1(bool seleccion);
    void Escena2(bool seleccion);

    void ComenzarAnimacionBoton();

    void PanelControlModelo(bool seleccion);
    void LaboratorioModelo();
};

#endif // ESCENA_H