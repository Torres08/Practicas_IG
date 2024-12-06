#ifndef BOTON_H
#define BOTON_H

#include <GL/glut.h>
#include "modelo.h"
#include "file_ply_stl.h"
#include "MiMalla.h"

class Boton : public Objeto3D
{
    int id;
    
public:
    bool animacionCompleta;
    GLfloat colorArriba[4];

    Boton(int _id, GLfloat _colorArriba[4]);

    int getId();

    void draw();


    void animacion();

    void iniciarAnimacion();

};

#endif // BRAZOMECANICO_H