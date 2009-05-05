//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TAfin.h"

//---------------------------------------------------------------------------

TAfin::TAfin(){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        glLoadIdentity();
        glGetDoublev(GL_MODELVIEW_MATRIX,matriz);
    glPopMatrix();
}

//---------------------------------------------------------------------------

void TAfin::trasladar(PV3D* vector){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    	glLoadIdentity();
    	glTranslated(vector->getX(),vector->getY(),vector->getZ());
    	GLdouble aux[16];
    	glGetDoublev(GL_MODELVIEW_MATRIX,aux);
    glPopMatrix();
    glPushMatrix();
    	glLoadMatrixd(matriz);
    	glMultMatrixd(aux);
    	glGetDoublev(GL_MODELVIEW_MATRIX,matriz);
    glPopMatrix();
}

//---------------------------------------------------------------------------

void TAfin::rotar(GLdouble angulo,PV3D* vector){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    	glLoadIdentity();
    	glRotated(angulo,vector->getX(),vector->getY(),vector->getZ());
    	GLdouble aux[16];
	    glGetDoublev(GL_MODELVIEW_MATRIX,aux);
    glPopMatrix();
    glPushMatrix();
    	glLoadMatrixd(matriz);
    	glMultMatrixd(aux);
    	glGetDoublev(GL_MODELVIEW_MATRIX,matriz);
    glPopMatrix();
}

//---------------------------------------------------------------------------

void TAfin::escalar(PV3D* escalacion){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    	glLoadIdentity();
    	glScaled(escalacion->getX(),escalacion->getY(),escalacion->getZ());
    	GLdouble aux[16];
    	glGetDoublev(GL_MODELVIEW_MATRIX,aux);
    glPopMatrix();
    glPushMatrix();
    	glLoadMatrixd(matriz);
    	glMultMatrixd(aux);
    	glGetDoublev(GL_MODELVIEW_MATRIX,matriz);
    glPopMatrix();
}

//---------------------------------------------------------------------------

GLdouble* TAfin::getMatriz(){
	return matriz;
}

//---------------------------------------------------------------------------

#pragma package(smart_init)
