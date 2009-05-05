//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Cilindro.h"

//---------------------------------------------------------------------------

Cilindro::Cilindro(GLfloat nRadioBase,GLfloat nRadioCima,GLfloat nAltura,GLint nNPlados, GLint nNQCapas){
    cilindro = gluNewQuadric();
    radioBase = nRadioBase;
    radioCima = nRadioCima;
    altura = nAltura;
    nLados = nNPlados;
    nCapas = nNQCapas;
}

//---------------------------------------------------------------------------

Cilindro::~Cilindro(){
    gluDeleteQuadric(cilindro);
    delete color;
    delete matriz;
}

//---------------------------------------------------------------------------

void Cilindro::dibujar(){
    gluQuadricDrawStyle(cilindro,GLU_FILL);
  	glColor3d(color->getRojo(),color->getVerde(),color->getAzul());
    gluCylinder(cilindro,radioBase,radioCima,altura,nLados,nCapas);
}

//---------------------------------------------------------------------------

#pragma package(smart_init)
