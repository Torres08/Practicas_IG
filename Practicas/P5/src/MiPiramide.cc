#include "MiPiramide.h"
#include "file_ply_stl.h"
#include "modelo.h"
#include <cmath>
using namespace std;

MiPiramide::MiPiramide(float l, float h)
{
    lado = l;
    alto = h;
}

void MiPiramide::calcularNormal(float Ax, float Ay, float Az, float Bx, float By, float Bz, float Cx, float Cy, float Cz)
{
    // Calcular los dos vectores
    // v1 -v0
    // v2 - v0
    float ux = Bx - Ax;
    float uy = By - Ay;
    float uz = Bz - Az;

    float vx = Cx - Ax;
    float vy = Cy - Ay;
    float vz = Cz - Az;

    // Calcular el producto vectorial para la normal
    float nx = uy * vz - uz * vy;
    float ny = uz * vx - ux * vz;
    float nz = ux * vy - uy * vx;

    // Normalizar la normal (opcional) hacer raiz cuadrada, si es distinto de 0 dividirlo
    float length = sqrt(nx * nx + ny * ny + nz * nz);
    if (length != 0)
    {
        nx /= length;
        ny /= length;
        nz /= length;
    }

    // Usar la normal calculada
    glNormal3f(nx, ny, nz);
}

void MiPiramide::draw()
{
    float Cx = lado / 2.0f;
    float Cy = alto;
    float Cz = lado / 2.0f;

    glBegin(GL_TRIANGLES);
    {

        // Cara delante
        calcularNormal(0, 0, lado, lado, 0, lado, Cx, Cy, Cz);
        glVertex3f(0, 0, lado);
        glVertex3f(lado, 0, lado);
        glVertex3f(lado / 2, alto, lado / 2); // arriba

        // Cara atras
        calcularNormal(lado, 0, 0, 0, 0, 0, Cx, Cy, Cz);
        glVertex3f(lado, 0, 0);
        glVertex3f(0, 0, 0);
        glVertex3f(lado / 2, alto, lado / 2);

        // Cara derecha
        calcularNormal(lado, 0, lado, lado, 0, 0, Cx, Cy, Cz);
        glVertex3f(lado, 0, lado);
        glVertex3f(lado, 0, 0);
        glVertex3f(lado / 2, alto, lado / 2);

        // Cara izquierda
        calcularNormal(0, 0, 0, 0, 0, lado, Cx, Cy, Cz);
        glVertex3f(0, 0, 0);
        glVertex3f(0, 0, lado);
        glVertex3f(lado / 2, alto, lado / 2);
    }
    glEnd();

    // Base de la pirámide
    glBegin(GL_QUADS);
    {
        glNormal3f(0, -1, 0);
        glVertex3f(0, 0, 0);
        glVertex3f(lado, 0, 0);
        glVertex3f(lado, 0, lado);
        glVertex3f(0, 0, lado);
    }
    glEnd();
}

