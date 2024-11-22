#include "MiCubo.h"
#include "file_ply_stl.h"
#include "modelo.h"

MiCubo::MiCubo(float l) {
    lado = l;
}

void MiCubo::draw() {
    glBegin(GL_QUADS);
    {
        // Cara delante
        glNormal3f(0, 0, 1);
        glVertex3f(0, 0, lado);
        glVertex3f(lado, 0, lado);
        glVertex3f(lado, lado, lado);
        glVertex3f(0, lado, lado);

        // Cara atrás
        glNormal3f(0, 0, -1);
        glVertex3f(0, 0, 0);
        glVertex3f(0, lado, 0);
        glVertex3f(lado, lado, 0);
        glVertex3f(lado, 0, 0);

        // Cara izquierda
        glNormal3f(-1, 0, 0);
        glVertex3f(0, 0, 0);
        glVertex3f(0, 0, lado);
        glVertex3f(0, lado, lado);
        glVertex3f(0, lado, 0);

        // Cara derecha
        glNormal3f(-1, 0, 0);
        glVertex3f(lado, 0, 0);
        glVertex3f(lado, lado, 0);
        glVertex3f(lado, lado, lado);
        glVertex3f(lado, 0, lado);

        // Cara arriba
        glNormal3f(0, 1, 0);
        glVertex3f(0, lado, 0);
        glVertex3f(0, lado, lado);
        glVertex3f(lado, lado, lado);
        glVertex3f(lado, lado, 0);

        // Cara abajo
        glNormal3f(0, -1, 0);
        glVertex3f(0, 0, 0);
        glVertex3f(lado, 0, 0);
        glVertex3f(lado, 0, lado);
        glVertex3f(0, 0, lado);
    }
    glEnd();
}