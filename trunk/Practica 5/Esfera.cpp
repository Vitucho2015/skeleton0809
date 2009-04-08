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
    glColor3d(color->getRojo(),color->getVerde(),color->getAzul());
    gluQuadricDrawStyle(esfera,GLU_FILL);    
    gluSphere(esfera,radio,meridianos,paralelos);
}

//---------------------------------------------------------------------------

