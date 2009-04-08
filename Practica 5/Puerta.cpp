//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Puerta.h"

//---------------------------------------------------------------------------

Puerta::Puerta(GLfloat l, GLfloat a, GLfloat g, int divL, int divA, int divG){
    double radioPomo = a/40;
    objetos = new Lista<Objeto3D>();
    //Madero
    Tablero* tablero = new Tablero(l,a,g,divL,divA,divG);
    tablero->setColor(new Color(0.4,0.2,0));
    tablero->setMatriz(new TAfin());
    objetos->inserta((Objeto3D*)tablero);
    //Situamos los pomos
    PV3D* translacion = new PV3D(l-0.3,a/2.0,0.3,1);
    TAfin* matrizPomo1 = new TAfin();
    matrizPomo1->trasladar(translacion);
    delete translacion;
    translacion = new PV3D(l-0.3,a/2.0,-0.1,1);
    TAfin* matrizPomo2 = new TAfin();
    matrizPomo2->trasladar(translacion);
    delete translacion;
    //Creamos los pomo
    Esfera* pomo1 = new Esfera(radioPomo,20,20);
    pomo1->setColor(new Color(1,1,0));
    pomo1->setMatriz(matrizPomo1);
    objetos->inserta((Objeto3D*)pomo1);
    Esfera* pomo2 = new Esfera(radioPomo,20,20);
    pomo2->setColor(new Color(1,1,0));
    pomo2->setMatriz(matrizPomo2);
    objetos->inserta((Objeto3D*)pomo2);

}

//---------------------------------------------------------------------------

Puerta::~Puerta(){
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

void Puerta::dibujar(){
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

//---------------------------------------------------------------------------
