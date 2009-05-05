//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Lampara.h"

//---------------------------------------------------------------------------

Lampara::Lampara(GLfloat nRadioBase,GLfloat nRadioCima,GLfloat nAltura,GLint nNPlados, GLint nNQCapas){
    Lampara = gluNewQuadric();
    radioBase = nRadioBase;
    radioCima = nRadioCima;
    altura = nAltura;
    nLados = nNPlados;
    nCapas = nNQCapas;
}

//---------------------------------------------------------------------------

Lampara::~Lampara(){
    gluDeleteQuadric(Lampara);
    delete color;
    delete matriz;
}

//---------------------------------------------------------------------------

void Lampara::dibujar(){
    gluQuadricDrawStyle(Lampara,GLU_FILL);
  	glColor3d(color->getRojo(),color->getVerde(),color->getAzul());
    gluCylinder(Lampara,radioBase,radioCima,altura,nLados,nCapas);
}

//---------------------------------------------------------------------------

#pragma package(smart_init)
