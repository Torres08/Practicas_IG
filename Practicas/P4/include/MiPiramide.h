#ifndef MIPIRAMIDE_H
#define MIPIRAMIDE_H

#include <GL/glut.h>
#include "modelo.h"
#include "file_ply_stl.h"

class MiPiramide : public Objeto3D
{
public:
    float lado;
    float alto;

    MiPiramide(float l, float h);

    void calcularNormal(float Ax, float Ay, float Az, float Bx, float By, float Bz, float Cx, float Cy, float Cz);
    
    void draw();
};

#endif // MIPIRAMIDE_H