//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Camara.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

Camara::Camara(PV3D* ojo,PV3D* direccion,PV3D* arriba){
    setView(ojo, direccion, arriba);
	setModelViewMatrix();
}

//------------------------------------------------------------------------

Camara::~Camara(){
    if(eye != NULL){
        delete eye;
    }
    if(look != NULL){
        delete look;
    }
    if(up != NULL){
        delete up;
    }
    if(u != NULL){
        delete u;
    }
    if(v != NULL){
        delete v;
    }
    if(n != NULL){
        delete n;
    }
}

//-----------------------------------------------------------------------

void Camara::setView(PV3D* ojo, PV3D* direccion, PV3D* arriba){
    eye = ojo;
    look = direccion;
    up = arriba;
    n = new PV3D(eye->getX()-look->getX(),eye->getY()-look->getY(),eye->getZ()-look->getZ(), 1);
    n->normalizar();
    u = up->prodVectorial(n);
    u->normalizar();
    v = n->prodVectorial(u);
    v->normalizar();
}

//------------------------------------------------------------------------

void Camara::cambiaPosicion(PV3D* ojo,PV3D* direccion,PV3D* arriba) {
    if(eye != NULL){
        delete eye;
    }
    if(look != NULL){
        delete look;
    }
    if(up != NULL){
        delete up;
    }
    if(u != NULL){
        delete u;
    }
    if(v != NULL){
        delete v;
    }
    if(n != NULL){
        delete n;
    }
    setView(ojo, direccion, arriba);
	setModelViewMatrix();
}

//------------------------------------------------------------------------

void Camara::Oblicua(GLfloat xLeft,GLfloat xRight,GLfloat yBot,GLfloat yTop,GLfloat N,GLfloat F,PV3D* direccion){
  glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(xLeft,xRight, yBot,yTop, N,F);
  float matriz[16];
	matriz[0] = 1;
	matriz[1] = 0;
	matriz[2] = 0;
	matriz[3] = 0;
	matriz[4] = 0;
	matriz[5] = 1;
	matriz[6] = 0;
	matriz[7] = 0;
	matriz[8] = (-direccion->getX()/(GLdouble)direccion->getZ());
	matriz[9] = (-direccion->getY()/(GLdouble)direccion->getZ());
	matriz[10] = 1;
	matriz[11] = 0;
	matriz[12] = 0;
	matriz[13] = 0;
	matriz[14] = 0;
	matriz[15] = 1;
	glMultMatrixf(matriz);
	setModelViewMatrix();
    delete direccion;
}

//---------------------------------------------------------------------------

void Camara::setModelViewMatrix(){
  GLdouble matriz[16];
	matriz[0] = u->getX();
	matriz[1] = v->getX();
	matriz[2] = n->getX();
	matriz[3] = 0;
    matriz[4] = u->getY();
	matriz[5] = v->getY();
	matriz[6] = n->getY();
	matriz[7] = 0;
	matriz[8] = u->getZ();
	matriz[9] = v->getZ();
	matriz[10] = n->getZ();
	matriz[11] = 0;
	matriz[12] = -eye->prodEscalar(u);
	matriz[13] = -eye->prodEscalar(v);
	matriz[14] = -eye->prodEscalar(n);
	matriz[15] = 1;
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(matriz);
}

//--------------------------------------------------------------------------

void Camara::roll(float angulo){
    GLfloat cs=cos(M_PI*angulo/(GLdouble)180);
    GLfloat sn=sin(M_PI*angulo/(GLdouble)180);
    PV3D* aux1 = new PV3D(u);
    PV3D* aux2 = new PV3D(v);
    u->setPV3D(cs*aux1->getX()+sn*aux2->getX(),cs*aux1->getY()+sn*aux2->getY(),cs*aux1->getZ()+sn*aux2->getZ(),1);
    v->setPV3D(-sn*aux1->getX()+cs*aux2->getX(),-sn*aux1->getY()+cs*aux2->getY(),-sn*aux1->getZ()+cs*aux2->getZ(),1);
    delete aux1;
    aux1 = NULL;
    delete aux2;
    aux2 = NULL;
    setModelViewMatrix();
}

//-----------------------------------------------------------------------

void Camara::yaw(float angulo){
    GLfloat cs=cos(M_PI*angulo/(GLdouble)180);
    GLfloat sn=sin(M_PI*angulo/(GLdouble)180);
    PV3D* aux1 = new PV3D(u);
    PV3D* aux2 = new PV3D(n);
    u->setPV3D(cs*aux1->getX()+sn*aux2->getX(),cs*aux1->getY()+sn*aux2->getY(),cs*aux1->getZ()+sn*aux2->getZ(),1);
    n->setPV3D(-sn*aux1->getX()+cs*aux2->getX(),-sn*aux1->getY()+cs*aux2->getY(),-sn*aux1->getZ()+cs*aux2->getZ(),1);
    delete aux1;
    aux1 = NULL;
    delete aux2;
    aux2 = NULL;
  setModelViewMatrix();
}

//------------------------------------------------------------------------

void Camara::pitch(float angulo){
    GLfloat cs=cos(M_PI*angulo/(GLdouble)180);
    GLfloat sn=sin(M_PI*angulo/(GLdouble)180);
    PV3D* aux1 = new PV3D(n);
    PV3D* aux2 = new PV3D(v);
    n->setPV3D(cs*aux1->getX()+sn*aux2->getX(),cs*aux1->getY()+sn*aux2->getY(),cs*aux1->getZ()+sn*aux2->getZ(),1);
    v->setPV3D(-sn*aux1->getX()+cs*aux2->getX(),-sn*aux1->getY()+cs*aux2->getY(),-sn*aux1->getZ()+cs*aux2->getZ(),1);
    delete aux1;
    aux1 = NULL;
    delete aux2;
    aux2 = NULL;
    setModelViewMatrix();
}

//----------------------------------------------------------------------------

void Camara::desplazar(GLfloat desU, GLfloat desV, GLfloat desN){
    eye->setX(eye->getX()+ desU);
    eye->setY(eye->getY() + desV);
    eye->setZ(eye->getZ()+ desN);
    setModelViewMatrix();
}

//----------------------------------------------------------------------------

void Camara::ortogonal(GLfloat xLeft,GLfloat xRight,GLfloat yBot,GLfloat yTop,GLfloat N,GLfloat F) {
  glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(xLeft, xRight, yBot, yTop, N, F);
	setModelViewMatrix();
}

//----------------------------------------------------------------------------

void Camara::perspectiva(GLfloat angulo,GLfloat proporcion,GLfloat N,GLfloat F){
  glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(angulo, proporcion, N, F);
	setModelViewMatrix();
}

//----------------------------------------------------------------------------

PV3D* Camara::getEye(){
    return eye;
}

//---------------------------------------------------------------------------

PV3D* Camara::getLook(){
    return look;
}

//---------------------------------------------------------------------------

PV3D* Camara::getUp(){
    return up;
}

//---------------------------------------------------------------------------
