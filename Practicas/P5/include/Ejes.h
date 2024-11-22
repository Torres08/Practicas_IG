#ifndef MIEJES_H
#define MIEJES_H

#include <GL/glut.h>
#include "modelo.h"
#include "file_ply_stl.h"

class Ejes : public Objeto3D {
public:
    float longitud = 30.0f;

    // Dibuja el objeto
    void draw();
    
};

#endif // EJES_H