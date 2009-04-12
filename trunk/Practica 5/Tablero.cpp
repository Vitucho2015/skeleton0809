//---------------------------------------------------------------------------

#include <vcl.h>    
#pragma hdrstop

#include "Tablero.h"

//---------------------------------------------------------------------------

Tablero::Tablero(GLfloat l, GLfloat a, GLfloat g, int divL, int divA, int divG) {
    largo = l;
    ancho = a;
    grueso = g;
    divLargo = divL;
    divAncho = divA;
    divGrueso = divG;

    numVertices = (divGrueso+1)*(divLargo+1)+(2*divAncho*(divLargo+1))+(divGrueso*(divLargo+1))+(2*(divGrueso+1)*(divAncho+1))- (divL+1);
    numCaras = numNormales = 2*((divLargo*divGrueso) + (divAncho*divGrueso) + (divLargo*divAncho));
    vertices = new PV3D*[numVertices];
    caras = new Cara*[numCaras];
    normales = new PV3D*[numNormales];
    //crearVertices
    int contador = 0;
    float trozoL = largo/(float)divL;
    float trozoA = ancho/(float)divA;
    float trozoG = grueso/(float)divG;
    float xAux, yAux, zAux;

    //vertices cara frontal
    xAux = yAux = 0;
    zAux = ancho;
    for(int j = 0; j <= divGrueso; j++){
        for(int k = 0; k <= divLargo; k++){
            vertices[contador] = new PV3D(xAux, yAux, zAux,1);
            xAux = xAux + trozoL;
            contador++;
        }
        xAux = 0;
        yAux = yAux + trozoG;
    }

    //vertices cara superior
    xAux = 0;
    yAux = grueso;
    zAux = ancho - trozoA;
    for(int j = 1; j <= divAncho; j++){
        for(int k = 0; k <= divLargo; k++){
            vertices[contador] = new PV3D(xAux, yAux, zAux,1);
            xAux = xAux + trozoL;
            contador++;
        }
        xAux = 0;
        zAux = zAux - trozoA;
    }

    //vertices cara trasera
    yAux = grueso - trozoG;
    zAux = xAux = 0;
    for(int j = 1; j <= divGrueso; j++){
        for(int k = 0; k <= divLargo; k++){
            vertices[contador] = new PV3D(xAux, yAux, zAux,1);
            xAux = xAux + trozoL;
            contador++;
        }
        xAux = 0;
        yAux = yAux - trozoG;
    }

    //vertices cara inferior
    xAux = yAux = 0;
    zAux = trozoA;
    for(int j = 1; j <= (divAncho-1); j++){
        for(int k = 0; k <= divLargo; k++){
            vertices[contador] = new PV3D(xAux, yAux, zAux,1);
            xAux = xAux + trozoL;
            contador++;
        }
        xAux = 0;
        zAux = zAux + trozoA;
    }

    int indicePrimerVertice = contador;
    //vertices cara izquierda
    xAux = yAux = zAux = 0;
    for(int j = 0; j <= divGrueso; j++){
        for(int k = 0; k <= divAncho; k++){
            vertices[contador] = new PV3D(xAux, yAux, zAux, 1);
            zAux = zAux + trozoA;
            contador++;
        }
        zAux = 0;
        yAux = yAux + trozoG;
    }
    int indicePrimerVertice2 = contador;
    //vertices cara derecha
    xAux = largo;
    yAux = 0;
    zAux = ancho;
    for(int j = 0; j <= divGrueso; j++){
        for(int k = 0; k <= divAncho; k++){
            vertices[contador] = new PV3D(xAux, yAux, zAux, 1);
            zAux = zAux - trozoA;
            contador++;
        }
        zAux = ancho;
        yAux = yAux + trozoG;
    }

    //crear caras
    //caras frontal, superior, trasera e inferior
    int carasCont=0;
    int v[4];
    for(int i = 0; i < (2*divAncho + 2*divGrueso); i++){
      for(int j = 0; j < divL; j++){
        if (i == (2*divAncho + 2*divGrueso)-1) {
          v[0] = (i*(divL+1)) + j;
          v[1] = (i*(divL+1)) + j+1;
          v[2] = j+1;
          v[3] = j;
        }
        else{
          v[0] = j + (i*(divL+1));
          v[1] = (j+1) + (i*(divL+1));
          v[2] = (j+1) + ((i+1)*(divL+1));
          v[3] = j + ((i+1)*(divL+1));
        }
        caras[carasCont] = new Cara(4, v, carasCont);
        carasCont++;
      }
    }

    //caras izquierda y derecha
    for(int i = 0; i < divG; i++){
      for(int j = 0; j < divA; j++){
          v[0] = indicePrimerVertice + (i*(divA+1)) + j;
          v[1] = indicePrimerVertice + (i*(divA+1)) + j+1;
          v[2] = indicePrimerVertice + ((i+1)*(divA+1)) + j+1;
          v[3] = indicePrimerVertice + ((i+1)*(divA+1)) + j;
        caras[carasCont] = new Cara(4, v, carasCont);
        carasCont++;
      }
    }

    for(int i = 0; i < divG; i++){
      for(int j = 0; j < divA; j++){
          v[0] = indicePrimerVertice2 + (i*(divA+1)) + j;
          v[1] = indicePrimerVertice2 + (i*(divA+1)) + j+1;
          v[2] = indicePrimerVertice2 + ((i+1)*(divA+1)) + j+1;
          v[3] = indicePrimerVertice2 + ((i+1)*(divA+1)) + j;
        caras[carasCont] = new Cara(4, v, carasCont);
        carasCont++;
      }
    }

    Newell();

}

//---------------------------------------------------------------------------

Tablero::~Tablero(){
    delete color;
    delete matriz;
}

//---------------------------------------------------------------------------

#pragma package(smart_init)
