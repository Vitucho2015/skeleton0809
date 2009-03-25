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

void Malla::dibuja() {
   glColor3d(color->getRojo(),color->getVerde(),color->getAzul());
    for(int i = 0; i < numCaras; i++) {
        glBegin(GL_POLYGON);
        for(int j = 0; j < caras[i]->getNumVertices(); j++) {
            int iV = caras[i]->getIndiceVertice(j);
            int iN = caras[i]->getIndiceNormal(j);
            glNormal3f(normales[iN]->getX(),normales[iN]->getY(), normales[iN]->getZ());
            glVertex3f(vertices[iV]->getX(),vertices[iV]->getY(), vertices[iV]->getZ());
        }
        glEnd();
    }
}

//-------------------------------------------------------------------------

void Malla::Newell(){
    for(int i = 0; i < numCaras; i++) {
        GLfloat nX, nY, nZ;
        nX = nY = nZ = 0;
        int N = caras[i]->getNumVertices();
        for(int j = 0; j < N; j++) {
            int iV = caras[i]->getIndiceVertice(j);
            int sucI = caras[i]->getIndiceVertice((j+1)%N);
            PV3D* vertI = vertices[iV];
            PV3D* vertSucI = vertices[sucI];
            nX = nX + (vertI->getY() - vertSucI->getY())*(vertI->getZ() + vertSucI->getZ());
            nY = nY + (vertI->getZ() - vertSucI->getZ())*(vertI->getX() + vertSucI->getX());
            nZ = nZ + (vertI->getX() - vertSucI->getX())*(vertI->getY() + vertSucI->getY());
        }
       normales[i] = new PV3D(nX,nY,nZ,0);
       normales[i]->normalizar();
    }
}

//-------------------------------------------------------------------------

void Malla::dibujaNormales() {
 for(int i = 0; i < numCaras; i++) {
        glBegin(GL_LINES);
            glNormal3f(0.577,0.577, 0.577);
            glVertex3f(0.0,0.0, 0.0);
            glVertex3f(normales[i]->getX(),normales[i]->getY(), normales[i]->getZ());
        glEnd();
    }
}

//-------------------------------------------------------------------------
