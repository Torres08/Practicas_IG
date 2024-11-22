#include "MiDado.h"
#include "file_ply_stl.h"
#include "modelo.h"
using namespace std;


void MiDado::draw()
{
    // habilitar el mapeo de texturas
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texId);

    glBegin(GL_QUADS);
    {
        // Cara delante
        glNormal3f(0, 0, 1);
        glTexCoord2f(0.5, 0.5);
        glVertex3f(0, 0, lado);
        glTexCoord2f(0.75, 0.5);
        glVertex3f(lado, 0, lado);
        glTexCoord2f(0.75, 0.75);
        glVertex3f(lado, lado, lado);
        glTexCoord2f(0.5, 0.75);
        glVertex3f(0, lado, lado);

        // Cara atrás
        glNormal3f(0, 0, -1);
        glTexCoord2f(0.25, 0.5);
        glVertex3f(0, 0, 0);
        glTexCoord2f(0, 0.5);
        glVertex3f(0, lado, 0);
        glTexCoord2f(0, 0.75);
        glVertex3f(lado, lado, 0);
        glTexCoord2f(0.25, 0.75);
        glVertex3f(lado, 0, 0);

        // Cara izquierda
        glNormal3f(-1, 0, 0);
        glTexCoord2f(0.25, 0.5);
        glVertex3f(0, 0, 0);
        glTexCoord2f(0.25, 0.75);
        glVertex3f(0, 0, lado);
        glTexCoord2f(0.5, 0.75);
        glVertex3f(0, lado, lado);
        glTexCoord2f(0.5, 0.5);
        glVertex3f(0, lado, 0);

        // Cara derecha
        glNormal3f(1, 0, 0);
        glTexCoord2f(0.75, 0.5);
        glVertex3f(lado, 0, 0);
        glTexCoord2f(0.75, 0.75);
        glVertex3f(lado, lado, 0);
        glTexCoord2f(1.0, 0.75);
        glVertex3f(lado, lado, lado);
        glTexCoord2f(1.0, 0.5);
        glVertex3f(lado, 0, lado);

        // Cara arriba
        glNormal3f(0, 1, 0);
        glTexCoord2f(0.5, 0.25);
        glVertex3f(0, lado, 0);
        glTexCoord2f(0.5, 0.5);
        glVertex3f(0, lado, lado);
        glTexCoord2f(0.75, 0.5);
        glVertex3f(lado, lado, lado);
        glTexCoord2f(0.75, 0.25);
        glVertex3f(lado, lado, 0);

        // Cara abajo
        glNormal3f(0, -1, 0);
        glTexCoord2f(0.75, 0.75);
        glVertex3f(0, 0, 0);
        glTexCoord2f(0.5, 0.75);
        glVertex3f(lado, 0, 0);
        glTexCoord2f(0.5, 1.0);
        glVertex3f(lado, 0, lado);
        glTexCoord2f(0.75, 1.0);
        glVertex3f(0, 0, lado);
    }
    glEnd();
    glDisable(GL_TEXTURE_2D);

}