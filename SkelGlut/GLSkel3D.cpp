//---------------------------------------------------------------------------
#pragma hdrstop
//---------------------------------------------------------------------------
#pragma argsused

#include <iostream>
using namespace std;
#include "UScene.h"

GLfloat N=1; GLfloat F=1000;
GLfloat W=400; GLfloat H=400;
GLfloat xLeft=-200; GLfloat xRight=200;
GLfloat yBot=-200; GLfloat yTop=200;

scene escena;
void GLScene(){escena.dibujar();}
void GLCharPres(unsigned char key, int x, int y){escena.charPres(key);}
void GLKeyPres(int key, int x, int y){escena.keyPres(key);}
void GLResize(int w, int h){
 //puerto de vista
 glViewport(0,0,W,H);
 W=w;H=h;
 if (H==0.0) H=1.0;
 if (W==0.0) W=1.0;
  // volumen de vista
 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();
 GLfloat nRange=50.0; //=400/8
 if (W<=H){
    nRange=W/8;
    xLeft=-nRange; xRight=nRange;
    yBot=-nRange*H/W; yTop=nRange*H/W;
    //glOrtho(left,right, bottom,top, near,far);
    glOrtho(xLeft,xRight, yBot,yTop, N,F);
    }
 else{
    nRange=H/8;
    xLeft=-nRange*W/H; xRight=nRange*W/H;
    yBot=-nRange; yTop=nRange;
    //glOrtho(left,right, bottom,top, near,far);
    glOrtho(xLeft,xRight, yBot,yTop, N,F);
    }
 //glMatrixMode(GL_MODELVIEW);
 GLScene();
}
void main(int argc, char* argv[])
{
 glutInit(&argc,argv);
 glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
 glutInitWindowSize(400,400);
 glutInitWindowPosition(100,100);
 glutCreateWindow("Ventana GLUT - Escena 3D");
 glutDisplayFunc(GLScene);
 glutKeyboardFunc(GLCharPres);
 glutSpecialFunc(GLKeyPres);
 glutReshapeFunc(GLResize);

 glEnable(GL_LIGHTING);
 glEnable(GL_LIGHT0);
 glShadeModel(GL_SMOOTH);
 glEnable(GL_DEPTH_TEST);
 glEnable(GL_NORMALIZE);
 GLfloat LuzDifusa[]={1.0,1.0,1.0,1.0};
 glLightfv(GL_LIGHT0,GL_DIFFUSE,LuzDifusa);
 GLfloat LuzAmbiente[]={0.3,0.3,0.3,1.0};
 glLightfv(GL_LIGHT0,GL_AMBIENT,LuzAmbiente);
 glEnable(GL_COLOR_MATERIAL);
 glClearColor(0.6,0.7,0.8,1.0);
 // puerto de vista
 glViewport(0,0,W,H);
 // cámara
 glMatrixMode(GL_MODELVIEW);
 glLoadIdentity();
 //gluLookAt(eyeX,eyeY,eyeZ, lookX,lookY,lookZ, upX,upY,upZ);
 gluLookAt(50.0,50.0,50.0, 0.0,0.0,0.0, 0.0,1.0,0.0);
 // volumen de vista
 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();
 GLfloat nRange=50.0; //=400/8
 if (W<=H){
    //nRange=W/8;
    xLeft=-nRange; xRight=nRange;
    yBot=-nRange*H/W; yTop=nRange*H/W;
    //glOrtho(left,right, bottom,top, near,far);
    glOrtho(xLeft,xRight, yBot,yTop, N,F);
    }
 else{
    //nRange=H/8;
    xLeft=-nRange*W/H; xRight=nRange*W/H;
    yBot=-nRange; yTop=nRange;
    //glOrtho(left,right, bottom,top, near,far);
    glOrtho(xLeft,xRight, yBot,yTop, N,F);
    }

 glutMainLoop();

// destruir la ventana !! 
}
//---------------------------------------------------------------------------
