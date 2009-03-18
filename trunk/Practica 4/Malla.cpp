//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Malla.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

Malla::Malla() {
    numVertices = numCaras = numNormales = 0;
}

//---------------------------------------------------------------------------

 Malla::Malla(int nVertices, PV3D** v, int nNormales, PV3D** n, int nCaras, Cara** c)
 {

        numVertices = nVertices;
        numNormales = nNormales;
        numCaras = nCaras;
        vertices = v;
        normales = n;
        caras = c;
 }

//---------------------------------------------------------------------------

Malla::~Malla(){
//Borramos el array de vértices
    if (vertices!=NULL){
        for (int i=0;i<numVertices;i++){
            delete vertices[i];
        }
        delete []vertices;
        vertices = NULL;
    }
 //Borramos el array de normales
    if (normales!=NULL){
        for (int i=0;i<numNormales;i++){
            delete normales[i];
        }
        delete []normales;
        normales = NULL;
    }
//Borramos el array de caras
    if (caras!=NULL){
        for (int i=0;i<numCaras;i++){
            delete caras[i];
        }
        delete []caras;
        caras = NULL;
    }
}

//---------------------------------------------------------------------------

void Malla::dibuja(int modo) {
    for(int i = 0; i < numCaras; i++) {
        switch (modo){
            case 1:
                  glBegin(GL_POLYGON);
                  break;
            default:
                glBegin(GL_LINE_LOOP);
        }
        for(int j = 0; j < caras[i]->getNumVertices(); j++) {
            int iV = caras[i]->getIndiceVertice(j);
            int iN = caras[i]->getIndiceNormal(j);
            //
            glNormal3f(normales[iN]->getX(),normales[iN]->getY(), normales[iN]->getZ());
       

            glVertex3f(vertices[iV]->getX(),vertices[iV]->getY(), vertices[iV]->getZ());
            //creamos la normal de este polígono
             }
        glEnd();
    }
}




