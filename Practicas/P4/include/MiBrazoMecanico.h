#ifndef MIBRAZOMECANICO_H
#define MIBRAZOMECANICO_H

#include <GL/glut.h>
#include "modelo.h"
#include "file_ply_stl.h"
#include "MiMalla.h"


class MiBrazoMecanico : public Objeto3D {
public:
    float anguloA, anguloB, anguloC, anguloD, anguloE, anguloF, anguloG, anguloH, anguloI;

    MiBrazoMecanico();

    // Métodos para obtener y establecer los ángulos
    float getAnguloA() const;
    void setAnguloA(float angulo);
    float getAnguloB() const;
    void setAnguloB(float angulo);
    float getAnguloC() const;
    void setAnguloC(float angulo);
    float getAnguloD() const;
    void setAnguloD(float angulo);
    float getAnguloE() const;
    void setAnguloE(float angulo);
    float getAnguloF() const;
    void setAnguloF(float angulo);
    float getAnguloG() const;
    void setAnguloG(float angulo);
    float getAnguloH() const;
    void setAnguloH(float angulo);
    float getAnguloI() const;
    void setAnguloI(float angulo);


    void A();
    void B();
    void C();
    void D();
    void E();
    void F();
    void G();
    void I();
    void J();
    void K();

    void animacion();
    
    // Método para dibujar el brazo mecánico
    void draw();

    void draw_animacion();
};

#endif // BRAZOMECANICO_H