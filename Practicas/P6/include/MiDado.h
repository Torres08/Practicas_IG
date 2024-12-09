#ifndef MIDADO_H
#define MIDADO_H

#include <GL/glut.h>
#include "modelo.h"
#include "file_ply_stl.h"

class MiDado : public Objeto3D {
public:
    float lado = 1.0f;
    
    void draw();
};

#endif // MIDADO_H