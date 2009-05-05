//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Mesa.h"

//---------------------------------------------------------------------------

Mesa::Mesa(GLfloat l, GLfloat a, GLfloat g, int divL, int divA, int divG,PV3D** perfil,int numPuntos, int numLados, int nCaras){

    objetos = new Lista<Objeto3D>();

    Tablero* tablero = new Tablero(l, a, g, divL, divA, divG);
    tablero->setMatriz(new TAfin());
    objetos->inserta((Objeto3D*)tablero);

    Copa* copa = new Copa(perfil, numPuntos, numLados, nCaras);
    copa->setMatriz(new TAfin());
    PV3D* vector = new PV3D(0.35, -0.03, 0.25, 1);
    copa->getM()->trasladar(vector);
    delete vector;
    objetos->inserta((Objeto3D*)copa);
    
}

//---------------------------------------------------------------------------

void Mesa::dibujar() {
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

Mesa::~Mesa(){
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

void Mesa::setColor(Color* color){
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
