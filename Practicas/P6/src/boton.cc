#include "boton.h"
#include "file_ply_stl.h"
#include "modelo.h"
using namespace std;

MiMalla cuboBotonArriba("recursos/cubo.ply");
MiMalla cuboBotonAbajo("recursos/cubo.ply");

Boton::Boton(int _id, GLfloat _colorArriba[4])
{
    id = _id; 
    animacionCompleta = false;

    std::copy(_colorArriba, _colorArriba + 4, colorArriba);

    printf("Boton id: %d\n", id);
}

int Boton::getId()
{
    return id;
}

void Boton::draw()
{
    // parte de arriba
    glPushMatrix();
    glTranslatef(0, 0.25, 0);
    glScalef(0.75, 0.5, 0.75);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, colorArriba);
    cuboBotonArriba.draw();
    glPopMatrix();

    // parte de abajo
    glPushMatrix();
    glTranslatef(0, 0, 0);
    glScalef(1, 0.5, 1);
    GLfloat colorAbajo[4] = {0.5f, 0.5f, 0.5f, 1.0f}; // Gray
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, colorAbajo);
    cuboBotonAbajo.draw();
    glPopMatrix();

}

void Boton::iniciarAnimacion()
{
    animacionCompleta = false; // Reiniciar la animación
}

void Boton::animacion()
{
    // printf("Animacion completa: %s\n", animacionCompleta ? "true" : "false");
    
    static bool bajando = true;
    static float desplazamiento = 0.0f;
    const float velocidad = 0.01f;
    const float limiteInferior = -0.1f;
    const float limiteSuperior = 0.0f;

    if (!animacionCompleta)
    {
        if (bajando)
        {
            desplazamiento -= velocidad;
            if (desplazamiento <= limiteInferior)
            {
                bajando = false;
            }
        }
        else
        {
            desplazamiento += velocidad;
            if (desplazamiento >= limiteSuperior)
            {
                bajando = true;
                animacionCompleta = true;
            }
        }
    }

    // parte de arriba
    glPushMatrix();
    glTranslatef(0, 0.25 + desplazamiento, 0);
    glScalef(0.75, 0.5, 0.75);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, colorArriba);
    cuboBotonArriba.draw();
    glPopMatrix();

    // parte de abajo
    glPushMatrix();
    glTranslatef(0, 0, 0);
    glScalef(1, 0.5, 1);
    GLfloat colorAbajo[4] = {0.5f, 0.5f, 0.5f, 1.0f}; // Gray
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, colorAbajo);
    cuboBotonAbajo.draw();
    glPopMatrix();

    //printf("Animacion completa: %s\n", animacionCompleta ? "true" : "false");
}
