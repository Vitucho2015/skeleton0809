//---------------------------------------------------------------------------
#pragma hdrstop
#include "UScene.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

scene::scene(){
  Esfera.Esf=gluNewQuadric();
  gluQuadricDrawStyle(Esfera.Esf,GLU_FILL);
  //gluQuadricNormals(Esfera.Esf,GLU_SMOOTH);  //defecto
  Esfera.ang=0;
  Esfera.dis=0;
  PosicionLuz0[0]=25.0; PosicionLuz0[1]=25.0;
  PosicionLuz0[2]=0.0; PosicionLuz0[3]=1.0;
}
scene::~scene(){
  gluDeleteQuadric(Esfera.Esf);
}

void scene::dibujar(){
  glMatrixMode(GL_MODELVIEW);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLightfv(GL_LIGHT0,GL_POSITION,PosicionLuz0);
  //drawEsfera();
  drawTetera(15.0);

  //glFlush();
  glutSwapBuffers();
}

void scene::drawEsfera(){
//glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
    glColor4f(1.0,1.0,0.0,1.0);
    glRotated(Esfera.ang,0,1,0);
    glTranslated(Esfera.dis,0,0);
    gluSphere(Esfera.Esf,10,16,16);
  glPopMatrix();
}

void scene::drawTetera(GLdouble size){
//glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
    glColor4f(1.0,1.0,0.0,1.0);
    glRotated(Esfera.ang,0,1,0);
    glTranslated(Esfera.dis,0,0);
    glutSolidTeapot(size);
  glPopMatrix();
}

void scene::charPres(unsigned char key){
 switch (key){
    case 'D': Esfera.dis=Esfera.dis+5;
              break;
    case 'd': Esfera.dis=Esfera.dis-5;
              break;
    case 'A': Esfera.ang=(Esfera.ang-5)%360;
              break;
    case 'a': Esfera.ang=(Esfera.ang+5)%360;
              break;
    default:  break;
  }
  dibujar();
}

void scene::keyPres(int key){
 switch (key){
    case GLUT_KEY_UP: Esfera.dis=Esfera.dis+5;
         break;
    case GLUT_KEY_DOWN: Esfera.dis=Esfera.dis-5;
         break;
    case GLUT_KEY_RIGHT: Esfera.ang=(Esfera.ang-5)%360;
         break;
    case GLUT_KEY_LEFT: Esfera.ang=(Esfera.ang+5)%360;
         break;
    default: break;
  }
  dibujar();
}

