
#include "MiBrazoMecanico.h"
#include "file_ply_stl.h"
#include "modelo.h"
using namespace std;

MiMalla mallaA("./recursos/Brazo/A.ply");
MiMalla mallaB("./recursos/Brazo/B.ply");
MiMalla mallaC("./recursos/Brazo/C.ply");
MiMalla mallaD("./recursos/Brazo/D.ply");
MiMalla mallaG("./recursos/Brazo/G.ply");
MiMalla mallaH("./recursos/Brazo/H.ply");
MiMalla mallaI("./recursos/Brazo/I.ply");
MiMalla mallaE("./recursos/Brazo/C.ply");
MiMalla mallaF("./recursos/Brazo/D.ply");

MiBrazoMecanico::MiBrazoMecanico()
{
    anguloA = anguloB = anguloC = anguloD = anguloE = anguloF = anguloG = anguloH = anguloI = 0.0f;
    anguloA = 35;  // pieza B
    anguloB = 45;  // pieza C
    anguloC = 90;  // pieza D
    anguloD = 25;  // pieza E
    anguloE = 45;  // pieza F
    anguloF = 90;  // pieza G
    anguloG = -30; // Pieza H
    anguloH = 30;  // pieza I

    anguloI = 0; // este para la traslacion del palo si vale
}

// q
float MiBrazoMecanico::getAnguloA() const { return anguloA; } // no tiene restricciones
void MiBrazoMecanico::setAnguloA(float angulo) { anguloA = angulo; }

// w
float MiBrazoMecanico::getAnguloB() const { return anguloB; }
void MiBrazoMecanico::setAnguloB(float angulo)
{
    if (angulo > 70.0f)
    {
        anguloB = 70.0f;
        printf("El valor de anguloB no puede ser mayor que 70. Se ha ajustado a 70.\n");
    }
    else if (angulo < -70.0f)
    {
        anguloB = -70.0f;
        printf("El valor de anguloB no puede ser menor que -70. Se ha ajustado a -70.\n");
    }
    else
    {
        anguloB = angulo;
    }
}

// libre, no tiene restricciones
// e
float MiBrazoMecanico::getAnguloC() const { return anguloC; }
void MiBrazoMecanico::setAnguloC(float angulo) { anguloC = angulo; }

// r
float MiBrazoMecanico::getAnguloD() const { return anguloD; }
void MiBrazoMecanico::setAnguloD(float angulo)
{
    if (angulo > 70.0f)
    {
        anguloD = 70.0f;
        printf("El valor de anguloD no puede ser mayor que 70. Se ha ajustado a 70.\n");
    }
    else if (angulo < -70.0f)
    {
        anguloD = -70.0f;
        printf("El valor de anguloD no puede ser menor que -70. Se ha ajustado a -70.\n");
    }
    else
    {
        anguloD = angulo;
    }
}

// t
float MiBrazoMecanico::getAnguloE()  const { return anguloE; }
void MiBrazoMecanico::setAnguloE(float angulo) { anguloE = angulo; }

// y
float MiBrazoMecanico::getAnguloF() const { return anguloF; }
void MiBrazoMecanico::setAnguloF(float angulo)
{
    if (angulo > 120.0f)
    {
        anguloF = 120.0f;
        printf("El valor de anguloF no puede ser mayor que 120. Se ha ajustado a 120.\n");
    }
    else if (angulo < -120.0f)
    {
        anguloF = -120.0f;
        printf("El valor de anguloD no puede ser menor que -120. Se ha ajustado a -120.\n");
    }
    else
    {
        anguloF = angulo;
    }
}

// u
//-5,40
float MiBrazoMecanico::getAnguloG()  const { return anguloG; }
void MiBrazoMecanico::setAnguloG(float angulo)
{
    if (angulo < -50.0f)
    {
        anguloG = -50.0f;
        printf("El valor de anguloG no puede ser mayor que 40. Se ha ajustado a 40.\n");
    }
    else if (angulo > 10.0f)
    {
        anguloG = 10.0f;
        printf("El valor de anguloG no puede ser menor que -5. Se ha ajustado a -5.\n");
    }
    else
    {
        anguloG = angulo;
    }
}

float MiBrazoMecanico::getAnguloH() const { return anguloH; }
void MiBrazoMecanico::setAnguloH(float angulo)
{
    if (angulo > 50.0f)
    {
        anguloH = 50.0f;
        printf("El valor de anguloG no puede ser mayor que 40. Se ha ajustado a 40.\n");
    }
    else if (angulo < -10.0f)
    {
        anguloH = -10.0f;
        printf("El valor de anguloG no puede ser menor que -5. Se ha ajustado a -5.\n");
    }
    else
    {
        anguloH = angulo;
    }
}

// a
//  30 0
float MiBrazoMecanico::getAnguloI()  const { return anguloI; }
void MiBrazoMecanico::setAnguloI(float angulo)
{
    if (angulo > 0.30f)
    {
        anguloI = 0.30f;
        printf("El valor de anguloI no puede ser mayor que 30. Se ha ajustado a 30.\n");
    }
    else if (angulo < 0.0f)
    {
        anguloI = 0.0f;
        printf("El valor de anguloI no puede ser menor que 0. Se ha ajustado a 0.\n");
    }
    else
    {
        anguloI = angulo;
    }
}


void MiBrazoMecanico::A()
  {
    //
    glPushMatrix();
    // 1. Set up, poner la figura en el medio
    glTranslatef(0.35, 0.2, 0);

    mallaA.draw();
    glPopMatrix();
  }

  // rotacion sobre el eje Y
  void MiBrazoMecanico::B()
  {
    glPushMatrix();
    // glRotatef(get_roty(), 0, 0, 1); // angulo A
    glRotatef(anguloA, 0, 0, 1);

    glTranslatef(0, 0.55, -0.5);
    mallaB.draw();

    // colocar C en B sin rotacion de C ni de -90
    glPushMatrix();
    glRotatef(11, 0, 0, 1);
    glTranslatef(-0.22, -0.53, 0.75);
    C();

    glPopMatrix();

    /*
    glPushMatrix();
    glRotatef(11, 0, 0, 1);
    glTranslatef(-0.22, -0.53, 1.5);
    E();
    glPopMatrix();
    */

    glPopMatrix();
  }

  void MiBrazoMecanico::C()
  {
    glPushMatrix();

    // glRotatef(get_roty(), 1, 0, 0); // angulo B
    glRotatef(anguloB, 1, 0, 0);
    glTranslatef(0.22, 0.54, -0.75);
    glRotatef(-11, 0, 0, 1);
    mallaC.draw();

    glPushMatrix();
    glTranslatef(0, -0.54, 0.85);
    D();
    glPopMatrix();

    // repetimos el proceso para E F, misma pieza misma rotacion

    glPopMatrix();
  }

  void MiBrazoMecanico::E()
  {

    glPushMatrix();

    // glRotatef(get_roty(), 1, 0, 0); // Angulo D
    glRotatef(anguloD, 1, 0, 0); // Angulo D
    glTranslatef(0.22, 0.54, -0.75);
    glRotatef(-11, 0, 0, 1);
    mallaE.draw();

    glPushMatrix();
    glTranslatef(0, -0.54, 0.85);
    F();
    glPopMatrix();

    // repetimos el proceso para E F, misma pieza misma rotacion

    glPopMatrix();
  }

  void MiBrazoMecanico::D()
  {
    glPushMatrix();
    // glRotatef(get_roty(), 0, 0, 1);// Angulo C
    glRotatef(anguloC, 0, 0, 1); // Angulo C
    glRotatef(3, 0, 0, 1);
    glTranslatef(0, 0.54, -0.85);
    mallaD.draw();

    glPushMatrix();
    glRotatef(11, 0, 0, 1);
    glTranslatef(-0.22, -0.53, 1.5);
    E();
    glPopMatrix();

    glPopMatrix();
  }

  void MiBrazoMecanico::F()
  {
    glPushMatrix();
    // glRotatef(get_roty(), 0, 0, 1); // Angulo E
    glRotatef(anguloE, 0, 0, 1); // Angulo E
    glRotatef(3, 0, 0, 1);
    glTranslatef(0, 0.54, -0.85);
    mallaF.draw();

    glPushMatrix();

    glTranslatef(0.15, -0.5, 1.5);
    glRotatef(9, 0, 0, 1);
    glRotatef(-90, 0, 1, 0);
    G();
    glPopMatrix();

    glPopMatrix();
  }

  void MiBrazoMecanico::G()
  {
    glPushMatrix();

    glScaled(1.3, 1.3, 1.3);

    glRotatef(anguloF, 0, 0, 1); // Angulo F

    glPushMatrix();
    glTranslatef(0, 0, 0.118);
    glRotatef(90, 0, 1, 0);
    I();
    glPopMatrix();

    glTranslatef(-0.05, 0, 0);
    glRotatef(-23, 0, 0, 1);
    glRotatef(15, 1, 0, 0);
    glRotatef(-38, 0, 1, 0);
    glTranslated(0, 1.27, -1.65);
    mallaG.draw();

    glPopMatrix();
  }

  void MiBrazoMecanico::I()
  {
    glPushMatrix();

    // glRotatef(get_roty(), 0, 0, 1);
    glTranslatef(0, 0, anguloI); // me gustaria moverlo sobr el eje Z, angulo I

    glPushMatrix();
    glTranslatef(-0.05, -0.01, 0.7);
    J();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.05, 0.01, 0.7);
    K();
    glPopMatrix();

    glScaled(0.8, 0.8, 0.8);
    glRotatef(-180, 1, 0, 0);
    glRotatef(90, 0, 0, 1);
    glTranslatef(-0.128, -0.055, -0.72);
    glRotatef(-23, 1, 0, 0);
    glRotatef(46, 0, 1, 0);
    glTranslatef(-0.5, 1, -1.15);
    mallaH.draw(); // traslada sobre un eje, no rota

    glPopMatrix();
  }

  void MiBrazoMecanico::J()
  {

    glPushMatrix();

    glRotatef(anguloG, 0, 1, 0); // angulo G

    glRotatef(-135, 0, 1, 0);

    glTranslatef(-0.05, 0, -0.05);
    glRotatef(40, 0, 0, 1);
    glRotatef(-80, 1, 0, 0);
    glTranslatef(-0.65, 0.9, -1.15);
    mallaI.draw();
    glPopMatrix();
  }

  void MiBrazoMecanico::K()
  {
    glPushMatrix();

    // glRotatef(get_roty(),0,1,0); // angulo H
    glRotatef(anguloH, 0, 1, 0); // angulo H

    glRotatef(180, 0, 0, 1);

    glRotatef(-130, 0, 1, 0);

    glTranslatef(-0.05, 0, -0.05);
    glRotatef(40, 0, 0, 1);
    glRotatef(-80, 1, 0, 0);
    glTranslatef(-0.65, 0.9, -1.15);
    mallaI.draw();
    glPopMatrix();
  }

  void MiBrazoMecanico::animacion()
  {
    static float angulo = 0.0f;
    angulo += 1.0f;

    setAnguloA(sin(angulo * M_PI / 180.0f) * 35.0f);
    setAnguloB(sin(angulo * M_PI / 180.0f) * 70.0f);
    setAnguloC(sin(angulo * M_PI / 180.0f) * 90.0f);
    setAnguloD(sin(angulo * M_PI / 180.0f) * 70.0f);
    setAnguloE(sin(angulo * M_PI / 180.0f) * 45.0f);
    setAnguloF(sin(angulo * M_PI / 180.0f) * 120.0f);
    setAnguloG(sin(angulo * M_PI / 180.0f) * 50.0f);
    setAnguloH(sin(angulo * M_PI / 180.0f) * 50.0f);
    setAnguloI(sin(angulo * M_PI / 180.0f) * 0.30f);
  }

  // E F

  void MiBrazoMecanico::draw()
  {

    // base
    float blanco[4] = {1, 1, 1, 1};
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, blanco);

    // set_roty(0);

    glRotated(-90, 1, 0, 0);
    glScaled(2, 2, 2);

    glPushMatrix();

    A();
    glTranslatef(0.36, -0.35, 0.5); // mirandolo sin rotated -90

    B();

    // animacion(); // aqui va bien

    // A();
    // B();
    // C();
    // D();
    // E();
    // F();
    // G();
    //  I();
    // J();

    // Pieza B

    /*
    glRotatef(anguloA, 0, 0, 1);

    glTranslatef(0, 0.55, -0.5);
    mallaB.draw();
    */

    // Pieza C
    /*
    glRotatef(anguloB, 1, 0, 0);
     glTranslatef(0.22, 0.54, -0.75);
     glRotatef(-11, 0, 0, 1);
     mallaC.draw();
     */

    // Pieza D
    /*
    glRotatef(anguloC, 0, 0, 1); // Angulo C
    glRotatef(3, 0, 0, 1);
    glTranslatef(0, 0.54, -0.85);
    mallaD.draw();
    */

    // Pieza E
    /*
    glRotatef(anguloD, 1, 0, 0); // Angulo D
    glTranslatef(0.22, 0.54, -0.75);
    glRotatef(-11, 0, 0, 1);
    mallaE.draw();
    */

    // Pieza F
    /*
    glRotatef(anguloE, 0, 0, 1); // Angulo E
     glRotatef(3, 0, 0, 1);
     glTranslatef(0, 0.54, -0.85);
     mallaF.draw();
     */

    // Pieza G
    /*
    glRotatef(anguloF, 0, 0, 1); // Angulo F
    glTranslatef(-0.05, 0, 0);
    glRotatef(-23, 0, 0, 1);
    glRotatef(15, 1, 0, 0);
    glRotatef(-38, 0, 1, 0);
    glTranslated(0, 1.27, -1.65);
    mallaG.draw();
    */

    // Pieza H
    /*
    glTranslatef(0,0,anguloI); //me gustaria moverlo sobr el eje Z, angulo I
    glScaled(0.8, 0.8, 0.8);
    glRotatef(-180, 1, 0, 0);
    glRotatef(90, 0, 0, 1);
    glTranslatef(-0.128, -0.055, -0.72);
    glRotatef(-23, 1, 0, 0);
    glRotatef(46, 0, 1, 0);
    glTranslatef(-0.5, 1, -1.15);
    mallaH.draw(); // traslada sobre un eje, no rota
    */

    // Pieza I
    // J();

    // Pieza J
    // K();

    glPopMatrix();
  }

  void MiBrazoMecanico::draw_animacion()
  {
    // base
    float blanco[4] = {1, 1, 1, 1};
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, blanco);

    // set_roty(0);

    glRotated(-90, 1, 0, 0);
    glScaled(2, 2, 2);

    glPushMatrix();

    A();
    glTranslatef(0.36, -0.35, 0.5); // mirandolo sin rotated -90

    B();

    animacion();

    glPopMatrix();
  }