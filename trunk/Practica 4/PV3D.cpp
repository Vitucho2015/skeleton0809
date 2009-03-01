//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "PV3D.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

PV3D::PV3D(GLfloat coordX, GLfloat coordY, GLfloat coordZ, int valor){
    x = coordX;
    y = coordY;
    z = coordZ;
    PoV = valor;
}

PV3D::PV3D() {
    x = 0;
    y = 0;
    z = 0;
    PoV = 1;
}

PV3D::PV3D(PV3D* punto){
    x = punto->getX();
    y = punto->getY();
    z = punto->getZ();
    PoV = punto->getValor();
}

GLfloat PV3D::getX() {
    return x;
}

GLfloat PV3D::getY(){
    return y;
}

GLfloat PV3D::getZ(){
    return z;
}

int PV3D::getValor() {
   return PoV;
}

void PV3D::setPV3D(GLfloat coordX, GLfloat coordY, GLfloat coordZ, int valor){
    x = coordX;
    y = coordY;
    z = coordZ;
    PoV = valor;
}

void PV3D::setX(GLfloat coordX){
    x = coordX;
}

void PV3D::setY(GLfloat coordY){
    y = coordY;
}

void PV3D::setZ(GLfloat coordZ){
    z = coordZ;
}

GLfloat PV3D::modulo(){
    return sqrt((x*x)+(y*y)+(z*z));
}

GLfloat PV3D::distancia(PV3D* punto){
    GLfloat x1, y1, z1;
    x1 = x - punto->x;
    y1 = y - punto->y;
    z1 = z - punto->z;
    return sqrt((x1*x1)+(y1*y1)+(z1*z1));
}

GLfloat PV3D::prodEscalar(PV3D* punto){
    return ((x*punto->x) + (y*punto->y) + (z*punto->z));
}

PV3D* PV3D::prodVectorial(PV3D* punto){
    GLfloat i = (y*punto->z) - (z*punto->y);
    GLfloat j = (z*punto->x) - (x*punto->z);
    GLfloat k = (x*punto->y) - (y*punto->x);
    PV3D* solucion = new PV3D(i,j,k,0);
    return solucion;
}