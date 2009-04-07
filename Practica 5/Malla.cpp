//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Malla.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

//---------------------------------------------------------------------------

Malla::Malla(){}

//---------------------------------------------------------------------------

Malla::Malla(int numV, int numC) {
    lados = numC;
    vertLado = numV;
    numVertices = numC * numV;
    numCaras = numNormales = numC*(numV-1);
    vertices = new PV3D*[numVertices];
    caras = new Cara*[numCaras];
    normales = new PV3D*[numNormales];
}

//----------------------------------------------------------------------

Malla::~Malla(){
    for(int i=0; i < numCaras; i++) {
        delete caras[i];
        delete normales[i];
    }
    delete []caras;
    delete []normales;
    for(int i = 0; i < numVertices; i++)
        delete vertices[i];
    delete []vertices;
}

//------------------------------------------------------------------------

void Malla::dibujar() {
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

//--------------------------------------------------------------------------

void Malla::defineMalla() {
    int v[4];
    int cont = 0;
    for(int i = 0; i < lados; i++) {
        for(int j = 0; j < vertLado-1; j++) {
            if (i == lados - 1) {
                v[0] = j;
                v[1] = j + 1;
                v[2] = (i*vertLado) + j + 1;
                v[3] = (i*vertLado) + j;
            }
            else{
                v[0] = ((i+1)*vertLado) + j;
                v[1] = ((i+1)*vertLado) + j + 1;
                v[2] = (i*vertLado) + j + 1;
                v[3] = (i*vertLado) + j;
            }
            caras[cont] = new Cara(4, v, cont);
            cont++;
        }
    }
}

//--------------------------------------------------------------------------


