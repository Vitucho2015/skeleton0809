//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Esfera.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

//---------------------------------------------------------------------------

Esfera::Esfera(GLfloat radio,GLint nMeridianos, GLint nParalelos){
    esfera= gluNewQuadric();
    radio=radio;
    Meridianos=nMeridianos;
    Paralelos=nParalelos;
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
    gluSphere(esfera,radio,Meridianos,Paralelos);
}

//---------------------------------------------------------------------------
