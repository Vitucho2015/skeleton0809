//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MallaPorRevolucion.h"

//---------------------------------------------------------------------------

MallaPorRevolucion::MallaPorRevolucion(PV3D** perfil, int numPuntos, int numLados, int nCaras):Malla(numLados+1,nCaras) {
    GLfloat xAux, yAux, zAux, radio, grados, gradosTotales;
    int numV = numLados+1;

    PV3D** perfilAux = new PV3D*[numV];
    GLfloat t = 2;
    for (int k = 0; k <= numLados; k++){
        GLfloat n;
        GLfloat acumulacionX = 0;
        GLfloat acumulacionY = 0;
        for(int j=0; j<numPuntos;j++) {
            GLfloat valor = t-j;
            //calculo de n(t-j)
            if(valor <= 1 && valor >= 0)
                n = 0.5*valor*valor;
            else if (valor <=2 && valor >1)
                n = (3.0/(GLfloat)4.0) - ((valor - (3.0/(GLfloat)2.0))*(valor - (3.0/(GLfloat)2.0)));
            else if (valor <= 3 && valor >2)
                n = 0.5*(3 - valor)*(3 - valor);
            else
                n = 0;
            //calculo de P(t)
            PV3D* pAux = perfil[j];
            acumulacionX = acumulacionX + (pAux->getX()*n);
            acumulacionY = acumulacionY + (pAux->getY()*n);
         }
         perfilAux[k] = new PV3D(acumulacionX, acumulacionY, 0.0, 1);
         t = t + ((numPuntos-2)/(GLfloat) numLados);
     }

    //crear vertices

    for(int i = 0; i < numV; i++)
        vertices[i] = new PV3D(perfilAux[i]);

    grados = gradosTotales = 2*M_PI/(GLfloat)nCaras;
    for(int i = numV; i < numVertices; i++) {
        xAux = radio = vertices[i%numV]->getX();
        yAux = vertices[i%numV]->getY();
        zAux = vertices[i%numV]->getZ();
        xAux = radio * cos(gradosTotales);
        zAux = -radio * sin(gradosTotales);
        vertices[i] = new PV3D(xAux, yAux, zAux, 1.0);
        if((i % numV) == (numV-1))
            gradosTotales = gradosTotales + grados;
    }

    defineMalla();

    for(int i = 0; i < numV; i++)
      delete perfilAux[i];
    delete []perfilAux;

    Newell();
}

//---------------------------------------------------------------------------

MallaPorRevolucion::~MallaPorRevolucion(){
    delete matriz;
    delete color;
}

//---------------------------------------------------------------------------

#pragma package(smart_init)