#ifndef BOTON_H
#define BOTON_H

#include <GL/glut.h>
#include "modelo.h"
#include "file_ply_stl.h"
#include "MiMalla.h"

class Boton : public Objeto3D
{
    int id;
    bool animacionCompleta;
public:
    Boton();

    int getId();

    void draw();

    void animacion();

    void iniciarAnimacion();

};

#endif // BRAZOMECANICO_H