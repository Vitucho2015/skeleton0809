//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Muebles.h"

//---------------------------------------------------------------------------

Muebles::Muebles() {
    objetos = new Lista<Objeto3D>();
    this->matriz = new TAfin();

    //Mesa
    PV3D** perfil = new PV3D*[5];
    perfil[0] = new PV3D(0.2, 0, 0, 1);
    perfil[1] = new PV3D(0.05, 0.1, 0, 1);
    perfil[2] = new PV3D(0.05, 0.3, 0, 1);
    perfil[3] = new PV3D(0.1, 0.4, 0, 1);
    perfil[4] = new PV3D(0.15, 0.5, 0, 1);

    Mesa* mesa = new Mesa(0.7, 0.5, 0.02, 1, 1, 1,perfil, 5, 50, 20);

    for(int i = 0; i < 5; i++){
        delete perfil[i];
    }
    delete []perfil;
    
    mesa->setMatriz(new TAfin());
    mesa->setColor(new Color(0, 0.502, 0.25));
    PV3D* vector = new PV3D(0.7, 0.45, 1.8, 1);
    mesa->getM()->trasladar(vector);
    delete vector;
    vector = new PV3D(1,0,0,1);
    mesa->getM()->rotar(180,vector);
    delete vector;
    objetos->inserta((Objeto3D*)mesa);

    //Copas
    perfil = new PV3D*[7];
    perfil[0] = new PV3D(0.2, 0, 0, 1);
    perfil[1] = new PV3D(0, 0.1, 0, 1);
    perfil[2] = new PV3D(0.03, 0.3, 0, 1);
    perfil[3] = new PV3D(0.1, 0.4, 0, 1);
    perfil[4] = new PV3D(0.15, 0.5, 0, 1);
    Copa* copa1 = new Copa(perfil, 5, 30, 30);

    Copa* copa2 = new Copa(perfil, 5, 30, 30);

    for(int i = 0; i < 5; i++){
        delete perfil[i];
    }
    delete []perfil;

    copa1->setColor(new Color(0.9,0.7,0.9));
    copa1->setMatriz(new TAfin());
    vector = new PV3D(0.85, 0.47,1.55, 1);
    copa1->getM()->trasladar(vector);
    delete vector;
    vector = new PV3D(0.5,0.5,0.5, 1);
    copa1->getM()->escalar(vector);
    delete vector;
    objetos->inserta((Objeto3D*)copa1);

    copa2->setColor(new Color(0.9,0.7,0.9));
    copa2->setMatriz(new TAfin());
    vector = new PV3D(1.25, 0.47,1.55, 1);
    copa2->getM()->trasladar(vector);
    delete vector;
    vector = new PV3D(0.5,0.5,0.5, 1);
    copa2->getM()->escalar(vector);
    delete vector;
    objetos->inserta((Objeto3D*)copa2);

    //Plato
    Cilindro* plato = new Cilindro(0.1, 0, 0.02, 20, 20);
    plato->setColor(new Color(0.0,0.2, 1.0));
    plato->setMatriz(new TAfin());
    vector = new PV3D(1.05, 0.47,1.55, 1);
    plato->getM()->trasladar(vector);
    delete vector;
    vector = new PV3D(1,0,0,1);
    plato->getM()->rotar(90,vector);
    delete vector;
    objetos->inserta((Objeto3D*)plato);

    //Donut
    Toro* donut = new Toro(50, 50, 0.9, 0.5);
    donut->setColor(new Color(0,0.8,0.3));
    donut->setMatriz(new TAfin());
    vector = new PV3D(1.05, 0.47, 1.55,1);
    donut->getM()->trasladar(vector);
    delete vector;
    vector = new PV3D(0.05, 0.05, 0.05,1);
    donut->getM()->escalar(vector);
    delete vector;
    objetos->inserta((Objeto3D*)donut);

    //Silla izquierda
    Silla* silla1 = new Silla();
    silla1->setMatriz(new TAfin());
    vector = new PV3D(0.2, 0.0, 1.6,1);
    silla1->getM()->trasladar(vector);
    delete vector;
    PV3D* giro = new PV3D(0.0, 1.0, 0.0, 1);
    silla1->getM()->rotar(90, giro);
    delete giro;
    objetos->inserta((Objeto3D*)silla1);

    //Silla derecha
    Silla* silla2 = new Silla();
    silla2->setMatriz(new TAfin());
    vector = new PV3D(1.85, 0.0, 1.3,1);
    silla2->getM()->trasladar(vector);
    delete vector;
    giro = new PV3D(0.0, 1.0, 0.0, 1);
    silla2->getM()->rotar(270, giro);
    delete giro;
    objetos->inserta((Objeto3D*)silla2);

    //Sofa
    Sofa* sofa = new Sofa();
    sofa->setMatriz(new TAfin());
    vector = new PV3D(0.9, 0.0, 0.06,1);
    sofa->getM()->trasladar(vector);
    delete vector;
    objetos->inserta((Objeto3D*)sofa);

    /*numObjetos = 0;
    PV3D* vector;
    mesa = new Mesa();
    mesa->setMatriz(new TAfin());
    vector = new PV3D(0.7, 0.0, 0.5,1);
    mesa->getM()->trasladar(vector);
    delete vector;

    silla1 = new Silla();
    silla1->setMatriz(new TAfin());
    vector = new PV3D(0.2, 0.0, 1.2,1);
    silla1->getM()->trasladar(vector);
    delete vector;
    PV3D* giro = new PV3D(0.0, 1.0, 0.0, 1);
    silla1->getM()->rotar(90, giro);


    silla2 = new Silla();
    silla2->setMatriz(new TAfin());
    vector = new PV3D(2.4, 0.0, 0.8,1);
    silla2->getM()->trasladar(vector);
    delete vector;
    silla2->getM()->rotar(270, giro);
    delete giro;

    PV3D** perfil = new PV3D*[7];
    perfil[0] = new PV3D(0.1, 0.0, 0.0, 1);
    perfil[1] = new PV3D(0.1, 0.1, 0.0, 1);
    perfil[2] = new PV3D(0.1, 0.2, 0.0, 1);
    perfil[3] = new PV3D(0.08, 0.3, 0.0, 1);
    perfil[4] = new PV3D(0.05, 0.5, 0.0, 1);
    perfil[5] = new PV3D(0.05, 0.6, 0.0, 1);
    perfil[6] = new PV3D(0.05, 0.7, 0.0, 1);
    botella = new MallaPorSplineYRevolucion(perfil, 7, 30, 30);
    botella->setColor(new Color(0.0,0.2, 1.0));
    botella->setMatriz(new TAfin());
    vector = new PV3D(0.9, 0.75, 0.9,1);
    botella->getM()->trasladar(vector);
    delete vector;

    PV3D** perfil2 = new PV3D*[7];
    perfil2[0] = new PV3D(0.1, 0.0, 0.0, 1);
    perfil2[1] = new PV3D(0.05, 0.04, 0.0, 1);
    perfil2[2] = new PV3D(0.05, 0.08, 0.0, 1);
    perfil2[3] = new PV3D(0.15, 0.12, 0.0, 1);
    perfil2[4] = new PV3D(0.15, 0.16, 0.0, 1);
    perfil2[5] = new PV3D(0.15, 0.20, 0.0, 1);
    perfil2[6] = new PV3D(0.15, 0.24, 0.0, 1);
    copa = new MallaPorSplineYRevolucion (perfil2, 7, 30, 30);

    copa->setColor(new Color(0.0,0.2, 1.0));
    copa->setMatriz(new TAfin());
    vector = new PV3D(1.2, 0.78, 0.9,1);
    copa->getM()->trasladar(vector);
    delete vector;

    donut = new Toro(50, 50, 0.2, 0.1);
    donut->setColor(new Color(0.1, 0.1, 0.1));
    donut->setMatriz(new TAfin());
    vector = new PV3D(1.2, 0.76, 1.25,1);
    donut->getM()->trasladar(vector);
    delete vector;

    plato = new Disco(0.0, 0.2, 20, 20);
    plato->setColor(new Color(0.0,0.2, 1.0));
    plato->setMatriz(new TAfin());
    vector = new PV3D(1.2, 0.81, 1.25,1);
    plato->getM()->trasladar(vector);
    delete vector;
    vector = new PV3D(1.0, 0.0,0.0,1);
    plato->getM()->rotar(90,vector);
    delete vector;

    for(int i = 0; i < 7 ;i++) {
        delete perfil[i];
        delete perfil2[i];
    }
    delete []perfil;
    delete []perfil2;
      */
}

//---------------------------------------------------------------------------

void Muebles::dibujar(){
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

Muebles::~Muebles(){
    if(objetos != NULL){
        objetos->inicia();
        for(int i=0;i<objetos->getLongitud();i++){
            objetos->eliminaActual();;
            objetos->avanza();
        }
        delete objetos;
        objetos = NULL;
        delete matriz;
    }
}

//---------------------------------------------------------------------------

#pragma package(smart_init)
