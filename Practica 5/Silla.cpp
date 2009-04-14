//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Silla.h"

//---------------------------------------------------------------------------

Silla::Silla() {

    objetos = new Lista<Objeto3D>();

    //respaldo
    Tablero* respaldo = new Tablero(0.3, 0.02, 0.4, 5, 2, 5);
    respaldo->setColor(new Color(0, 0.502, 0.25));
    respaldo->setMatriz(new TAfin());
    PV3D* vector= new PV3D(0,0.3,0,1);
    respaldo->getM()->trasladar(vector);
    delete vector;
    objetos->inserta((Objeto3D*)respaldo);

    //asiento
    Tablero* asiento = new Tablero(0.3, 0.3, 0.03, 5, 5, 2);
    asiento->setColor(new Color(0, 0.502, 0.25));
    asiento->setMatriz(new TAfin());
    vector= new PV3D(0,0.3,0, 1);
    asiento->getM()->trasladar(vector);
    delete vector;
    objetos->inserta((Objeto3D*)asiento);
    
    //pata
    Cilindro* pata1 = new Cilindro(0.03,0.03,0.3,20,20);
    pata1->setColor(new Color(0, 0.502, 0.25));
    pata1->setMatriz(new TAfin());
    vector= new PV3D(0.05,0.3,0,1);
    pata1->getM()->trasladar(vector);
    delete vector;
    PV3D* giro = new PV3D(1.0, 0.0, 0.0, 1);
    pata1->getM()->rotar(90, giro);
    delete giro;
    objetos->inserta((Objeto3D*)pata1);

    //pata
    Cilindro* pata2 = new Cilindro(0.03,0.03,0.3,20,20);
    pata2->setColor(new Color(0, 0.502, 0.25));
    pata2->setMatriz(new TAfin());
    vector= new PV3D(0.25,0.3,0,1);
    pata2->getM()->trasladar(vector);
    delete vector;
    giro = new PV3D(1.0, 0.0, 0.0, 1);
    pata2->getM()->rotar(90, giro);
    delete giro;
    objetos->inserta((Objeto3D*)pata2);

    //pata
    Cilindro* pata3 = new Cilindro(0.03,0.03,0.3,20,20);
    pata3->setColor(new Color(0, 0.502, 0.25));
    pata3->setMatriz(new TAfin());
    vector= new PV3D(0.25,0.3,0.25,1);
    pata3->getM()->trasladar(vector);
    delete vector;
    giro = new PV3D(1.0, 0.0, 0.0, 1);
    pata3->getM()->rotar(90, giro);
    delete giro;
    objetos->inserta((Objeto3D*)pata3);

    //pata
    Cilindro* pata4 = new Cilindro(0.03,0.03,0.3,20,20);
    pata4->setColor(new Color(0, 0.502, 0.25));
    pata4->setMatriz(new TAfin());
    vector= new PV3D(0.05,0.3,0.25,1);
    pata4->getM()->trasladar(vector);
    delete vector;
    giro = new PV3D(1.0, 0.0, 0.0, 1);
    pata4->getM()->rotar(90, giro);
    delete giro;
    objetos->inserta((Objeto3D*)pata4);

    //Reposabrazos
    Tablero* brazo1 = new Tablero(0.03, 0.3, 0.03, 5, 5, 2);
    brazo1->setColor(new Color(0, 0.502, 0.25));
    brazo1->setMatriz(new TAfin());
    vector= new PV3D(0,0.5,0, 1);
    brazo1->getM()->trasladar(vector);
    delete vector;
    objetos->inserta((Objeto3D*)brazo1);

    //Reposabrazos
    Tablero* brazo2 = new Tablero(0.03, 0.3, 0.03, 5, 5, 2);
    brazo2->setColor(new Color(0, 0.502, 0.25));
    brazo2->setMatriz(new TAfin());
    vector= new PV3D(0.25,0.5,0, 1);
    brazo2->getM()->trasladar(vector);
    delete vector;
    objetos->inserta((Objeto3D*)brazo2);
}

//---------------------------------------------------------------------------

void Silla::dibujar(){
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

Silla::~Silla(){
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
