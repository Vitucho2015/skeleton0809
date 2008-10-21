//---------------------------------------------------------------------------
#ifndef USceneH
#define USceneH

#include <windows>
#include <gl\gl.h>
#include <gl\glu.h>
#include "glut.h"
//---------------------------------------------------------------------------
class scene{
private:
 struct{GLUquadricObj *Esf;
 GLint ang;
 GLint dis;} Esfera;
 GLfloat PosicionLuz0[4];
 void drawEsfera();
 void drawTetera(GLdouble size);

public:
scene();
~scene();
void dibujar();
void charPres(unsigned char key);
void keyPres(int key);
};

#endif
