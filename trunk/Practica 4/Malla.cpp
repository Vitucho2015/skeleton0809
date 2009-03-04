//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Malla.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

Malla::Malla() {
    numVertices = numCaras = numNormales = 0;
}


 Malla::Malla(int nVertices, PV3D** v, int nNormales, PV3D** n, int nCaras, Cara** c)

 {

        numVertices = nVertices;
        numNormales = nNormales;
        numCaras = nCaras;
        vertices = v;
        normales = n;
        caras = c;

 }

Malla::~Malla(){}

void Malla::dibuja() {
    for(int i = 0; i < numCaras; i++) {
        glBegin(GL_LINE_LOOP);
        //glBegin(GL_POLYGON);
        for(int j = 0; j < caras[i]->getNumVertices(); j++) {
            int iV = caras[i]->getIndiceVertice(j);
            int iN = caras[i]->getIndiceNormal(j);
            //
            glVertex3f(vertices[iV]->getX(),vertices[iV]->getY(), vertices[iV]->getZ());
            //creamos la normal de este polígono
            glNormal3f(normales[iN]->getX(),normales[iN]->getY(), normales[iN]->getZ());
        }
        glEnd();
    }
}




