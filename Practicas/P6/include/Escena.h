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

void initModelEscena();

void cambioTexturaManzana(bool value);

void setAnimacion(int a);
int getAnimacion();	

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