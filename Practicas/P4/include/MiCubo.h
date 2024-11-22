#ifndef MICUBO_H
#define MICUBO_H

#include <GL/glut.h>
#include "modelo.h"
#include "file_ply_stl.h"


class MiCubo : public Objeto3D {
public:
    float lado;

    MiCubo(float l);

    // Método para dibujar el cubo
    void draw();
};

#endif // MICUBO_H