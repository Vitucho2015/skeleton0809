//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Estanteria.h"

//---------------------------------------------------------------------------

Estanteria::Estanteria(int numLibros, GLfloat a, int divA, int divL){
    GLfloat l = numLibros*a;
    objetos = new Lista<Objeto3D>();

    PV3D* vector = new PV3D(0.2,0.0, 0.2, 1);
    Tablero* balda = new Tablero(l,a,0.1,divL,divA,1);
    balda->setMatriz(new TAfin());
    balda->getM()->trasladar(vector);
    delete vector;
    balda->setColor(new Color(0,0,0));
    objetos->inserta((Objeto3D*)balda);

    Color* c1 = new Color(0.9,0,0.2);
    Color* c2 = new Color(0.2,0.9,1);

    vector = new PV3D(0.2,0.1, 0.2, 1);
    PV3D* v2 = new PV3D(0,0,1,1);
    PV3D* v3 = new PV3D(0,0.1,0,1);
    for(int i=0;i<numLibros;i++){
        Tablero* libro = new Tablero(0.1,0.2,0.4,divL,divA,1);
        libro->setMatriz(new TAfin());
        if((i % 2) == 0){
            libro->setColor(new Color(c1));
        }
        else{
            libro->setColor(new Color(c2));
        }
        if((i/(double)numLibros) < 0.5){
            libro->getM()->trasladar(vector);
            vector->setX(vector->getX()+ 0.15);
        }
        else{
            libro->getM()->trasladar(vector);
            libro->getM()->trasladar(v3);
            libro->getM()->rotar(270,v2);
            v3->setY(v3->getY()+0.1);
        }
        objetos->inserta((Objeto3D*)libro);

    }
    delete c1;
    delete c2;
    delete vector;
    delete v2;
    delete v3;
}

//---------------------------------------------------------------------------

void Estanteria::dibujar() {
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

Estanteria::~Estanteria() {
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

#pragma package(smart_init)


