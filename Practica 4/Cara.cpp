//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Cara.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

Cara::Cara(){
        numVertices = 0;
        tabla = NULL;
}

Cara::~Cara(){
        if (tabla!=NULL)
        {
        for (int i=0;i<numVertices;i++)
        {
        delete tabla[i];
        }
        delete []tabla;
        tabla = NULL;
        }
}

Cara::Cara(int numV, int n[], int numNormal) {
    numVertices = numV;
    tabla = new VerticeNormal*[numVertices];
    for (int i = 0; i < numVertices; i++)
        tabla[i] = new VerticeNormal(n[i], numNormal);
}

int Cara::getIndiceVertice(int n){
    return ((VerticeNormal*)tabla[n])->getVertice();
}

int Cara::getIndiceNormal(int n){
    return ((VerticeNormal*)tabla[n])->getNormal();
}

int Cara::getNumVertices(){
    return numVertices;
}


