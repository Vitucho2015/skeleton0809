//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Malla.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

Malla::Malla() {
    numVertices = numCaras = numNormales = 0;
}

Malla::~Malla(){}

void Malla::dibuja() {
    for(int i = 0; i < numCaras; i++) {
        glBegin(GL_POLYGON);
        for(int j = 0; j < caras[i]->getNumVertices(); j++) {
            int iV = caras[i]->getIndiceVertice(j);
            int iN = caras[i]->getIndiceNormal(j);
            glVertex3f(vertices[iV]->getX(),vertices[iV]->getY(), vertices[iV]->getZ());
            glNormal3f(normales[iN]->getX(),normales[iN]->getY(), normales[iN]->getZ());
        }
        glEnd();
    }
}




