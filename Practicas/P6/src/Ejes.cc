#include "Ejes.h"
#include "file_ply_stl.h"
#include "modelo.h"
using namespace std;

void Ejes::draw()
  {
    glDisable(GL_LIGHTING);
    glBegin(GL_LINES);
    {
      glColor3f(0, 1, 0);
      glVertex3f(0, 0, 0);
      glVertex3f(0, longitud, 0);

      glColor3f(1, 0, 0);
      glVertex3f(0, 0, 0);
      glVertex3f(longitud, 0, 0);

      glColor3f(0, 0, 1);
      glVertex3f(0, 0, 0);
      glVertex3f(0, 0, longitud);
    }
    glEnd();

    // glEnable(GL_LIGHTING);
    //  condicion aqui

    /*
    if (getModo() == GL_FILL && getIluminacion())
    {
      glEnable(GL_LIGHTING);
    }
    */
  }