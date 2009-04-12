//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Esfera.h"

//---------------------------------------------------------------------------

Esfera::Esfera(GLfloat r,GLint nMeridianos, GLint nParalelos){
    esfera= gluNewQuadric();
    radio=r;
    meridianos=nMeridianos;
    paralelos=nParalelos;
}

//---------------------------------------------------------------------------

Esfera::~Esfera(){
   gluDeleteQuadric(esfera);
   delete color;
   delete matriz;
}

//---------------------------------------------------------------------------

void Esfera::dibujar(){
    gluQuadricDrawStyle(esfera,GLU_FILL);
    glColor3d(color->getRojo(),color->getVerde(),color->getAzul());       
    gluSphere(esfera,radio,meridianos,paralelos);
}

//---------------------------------------------------------------------------

#pragma package(smart_init)
