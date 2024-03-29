//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Television.h"

//---------------------------------------------------------------------------

Television::Television(GLfloat l, GLfloat a, GLfloat g, int divL, int divA, int divG,bool estado){
    objetos = new Lista<Objeto3D>();

    Tablero* marco = new Tablero(l, a, g, divL, divA, divG);
    marco->setMatriz(new TAfin());
    marco->setColor(new Color(0, 0, 0));
    objetos->inserta((Objeto3D*)marco);

    pantalla = new Tablero(l*0.25, a*0.9,g*0.75, divL, divA, divG);
    pantalla->setMatriz(new TAfin());
    PV3D* vector = new PV3D(0.05, 0.1, 0.05,1);
    pantalla->getM()->trasladar(vector);
    delete vector;
    
    if(estado){//Esta encendida
        pantalla->setColor(new Color(1, 0, 0.3));
    }
    else{
        pantalla->setColor(new Color(0.5, 0.5, 0.5));
    }
    objetos->inserta((Objeto3D*)pantalla);
    encendida = estado;
}

//---------------------------------------------------------------------------

Television::~Television(){
    if(objetos != NULL){
        objetos->inicia();
        for(int i=0;i<objetos->getLongitud();i++){
            objetos->eliminaActual();
            objetos->avanza();
        }
        delete objetos;
        objetos = NULL;
        delete matriz;
    }
}

//---------------------------------------------------------------------------

void Television::cambiaTV(){
    delete pantalla->getColor();
    encendida = !encendida;
    if(encendida){//Esta encendida
        pantalla->setColor(new Color(0.2, 0, 0.3));
    }
    else{
        pantalla->setColor(new Color(0.5, 0.5, 0.5));
    }
}

//---------------------------------------------------------------------------

void Television::dibujar() {
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

#pragma package(smart_init)


