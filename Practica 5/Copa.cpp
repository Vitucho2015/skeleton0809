//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Copa.h"

//---------------------------------------------------------------------------

Copa::Copa(PV3D** perfil,int numPuntos, int numLados, int nCaras){
    objetos = new Lista<Objeto3D>();
    
    MallaPorRevolucion* malla = new MallaPorRevolucion(perfil, numPuntos, numLados, nCaras);

    malla->setMatriz(new TAfin());
    objetos->inserta((Objeto3D*)malla);
}

//---------------------------------------------------------------------------

Copa::~Copa(){
    if(objetos != NULL){
        objetos->inicia();
        for(int i=0;i<objetos->getLongitud();i++){
            objetos->eliminaActual();
            objetos->avanza();
        }
        delete objetos;
        objetos = NULL;
        delete matriz;
        delete color;
    }
}

//---------------------------------------------------------------------------

void Copa::dibujar(){
    glMatrixMode(GL_MODELVIEW);
    objetos->inicia();
    Objeto3D* aux;
    for(int i=0;i<objetos->getLongitud();i++){
        aux = objetos->getActual();
        glPushMatrix();
    	    glMultMatrixd(aux->getM()->getMatriz());
            aux->dibujar();
        glPopMatrix();
        objetos->avanza();
    }
}

//---------------------------------------------------------------------------

void Copa::setColor(Color* color){
    this->color = color;
    objetos->inicia();
    Objeto3D* aux;
    for(int i=0;i<objetos->getLongitud();i++){
        aux = objetos->getActual();
        aux->setColor(new Color(color));
        objetos->avanza();
    }
}

//---------------------------------------------------------------------------

#pragma package(smart_init)
