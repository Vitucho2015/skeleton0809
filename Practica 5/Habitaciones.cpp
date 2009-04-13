//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Habitaciones.h"

//---------------------------------------------------------------------------

Habitacion::Habitacion(int h) {
    nHabitacion = h;
    PV3D* vector;
    if(nHabitacion == 1){ //habitacion amueblada
        objetos = new Lista<Objeto3D>();
        this->matriz = new TAfin();

        //Muebles
        Muebles* muebles = new Muebles();
        objetos->inserta((Objeto3D*)muebles);
       
        //Estanteria
        Estanteria* estanteria = new Estanteria(4, 0.15, 1, 2);
        estanteria->setMatriz(new TAfin());
        vector = new PV3D(0.0, 1.3, 0.0, 1);
        estanteria->getM()->trasladar(vector);
        delete vector;
        objetos->inserta((Objeto3D*)estanteria);
        
        //Lampara
        Cilindro* lampara = new Cilindro(0.15,0.05,0.2,20,20);
        lampara->setMatriz(new TAfin());
        lampara->setColor(new Color(1.0, 0, 1.0));
        vector = new PV3D(1.3,1.8,1,1);
        (lampara->getM())->trasladar(vector);
        delete vector;
        vector = new PV3D(1.0,0.0,0.0,1);
        (lampara->getM())->rotar(270, vector);
        delete vector;
        objetos->inserta((Objeto3D*)lampara);
        
        //Suelo
        Tablero* suelo = new Tablero(2, 2, 0.01, 1, 1, 1);
        suelo->setColor(new Color(0.7, 0.2, 0.3));
        suelo->setMatriz(new TAfin());
        objetos->inserta((Objeto3D*)suelo);
         //Pared Izq
        Tablero* paredIzq = new Tablero(0.05, 2, 2, 1, 1, 1);
        paredIzq->setColor(new Color(0.7, 0.5, 0.5));
        paredIzq->setMatriz(new TAfin());
        objetos->inserta((Objeto3D*)paredIzq);
        //Pared Der1
        Tablero* paredDer1 = new Tablero(0.7, 0.05, 2, 1, 1, 1);
        paredDer1->setColor(new Color(0.7, 0.5, 0.5));
        paredDer1->setMatriz(new TAfin());
        objetos->inserta((Objeto3D*)paredDer1);
        //Pared Der3 (inferior)
        Tablero* paredDer3= new Tablero(0.6, 0.05, 0.7, 10, 2, 10);
        paredDer3->setColor(new Color(0.7, 0.5, 0.5));
        paredDer3->setMatriz(new TAfin());
        vector = new PV3D(0.7,0,0,1);
        paredDer3->getM()->trasladar(vector);
        delete vector;
        objetos->inserta((Objeto3D*)paredDer3);
        //Pared Der4 (superior)
        Tablero* paredDer4 = new Tablero(2, 0.05, 0.7, 10, 2, 10);
        paredDer4->setColor(new Color(0.7, 0.5, 0.5));
        paredDer4->setMatriz(new TAfin());
        vector = new PV3D(0, 1.3,0.0,1);
        paredDer4->getM()->trasladar(vector);
        delete vector;
        objetos->inserta((Objeto3D*)paredDer4);
        //Pared Der2
        Tablero* paredDer2= new Tablero(0.7, 0.05, 2, 1, 1, 1);
        paredDer2->setColor(new Color(0.7, 0.5, 0.5));
        paredDer2->setMatriz(new TAfin());
        vector = new PV3D(1.3, 0.0,0.0,1);
        paredDer2->getM()->trasladar(vector);
        delete vector;
        objetos->inserta((Objeto3D*)paredDer2);

        //Television
        Television* tv = new Television(0.05, 0.8, 0.5, 1, 1, 1,false);
        tv->setMatriz(new TAfin());
        vector = new PV3D(0.05,0.9,0.8,1);
        tv->getM()->trasladar(vector);
        delete vector;
        objetos->inserta((Objeto3D*)tv);
    }
    else {
        this->matriz = new TAfin();
        vector = new PV3D(2, 0.0, 0.0, 1);
        matriz->trasladar(vector);
        delete vector;
        objetos = new Lista<Objeto3D>();

        //Suelo
        Tablero* suelo = new Tablero(2, 2, 0.01, 10, 2, 10);
        suelo->setColor(new Color(0, 0.2, 0.3));
        suelo->setMatriz(new TAfin());
        objetos->inserta((Objeto3D*)suelo);
        //Pared Der1
        Tablero* paredDer = new Tablero(0.5, 0.05, 2, 10, 2, 10);
        paredDer->setColor(new Color(0, 0.9, 0.5));
        paredDer->setMatriz(new TAfin());
        objetos->inserta((Objeto3D*)paredDer);
        //Pared Der3 (inferior)
        Tablero* paredDer3 = new Tablero(1, 0.05, 0.9, 10, 2, 10);
        paredDer3->setColor(new Color(0, 0.9, 0.5));
        paredDer3->setMatriz(new TAfin());
        vector = new PV3D(0.5,0,0.0,1);
        paredDer3->getM()->trasladar(vector);
        delete vector;
        objetos->inserta((Objeto3D*)paredDer3);
        //Pared Der4 (superior)
        Tablero* paredDer4= new Tablero(2, 0.05, 0.5, 10, 2, 10);
        paredDer4->setColor(new Color(0, 0.9, 0.5));
        paredDer4->setMatriz(new TAfin());
        vector = new PV3D(0, 1.5,0.0,1);
        paredDer4->getM()->trasladar(vector);
        delete vector;
        objetos->inserta((Objeto3D*)paredDer4);
        //Pared Der2
        Tablero* paredDer2 = new Tablero(0.5, 0.05, 2, 10, 2, 10);
        paredDer2->setColor(new Color(0, 0.9, 0.5));
        paredDer2->setMatriz(new TAfin());
        vector = new PV3D(1.5, 0.0,0.0,1);
        paredDer2->getM()->trasladar(vector);
        delete vector;
        objetos->inserta((Objeto3D*)paredDer2);
        //Pared Izq1
        Tablero* paredIzq1 = new Tablero(0.05, 0.4, 2, 10, 2, 10);
        paredIzq1->setColor(new Color(0, 0.9, 0.5));
        paredIzq1->setMatriz(new TAfin());
        vector = new PV3D(0.0,0.0,1.6,1);
        paredIzq1->getM()->trasladar(vector);
        delete vector;
        objetos->inserta((Objeto3D*)paredIzq1);
        //Pared Izq2
        Tablero* paredIzq2 = new Tablero(0.05, 0.7, 2, 10, 2, 10);
        paredIzq2->setColor(new Color(0, 0.9, 0.5));
        paredIzq2->setMatriz(new TAfin());
        objetos->inserta((Objeto3D*)paredIzq2);
        //Pared Izq3 (superior)
        Tablero* paredIzq3 = new Tablero(0.05, 0.9, 0.3, 10, 2, 10);
        paredIzq3->setColor(new Color(0, 0.9, 0.5));
        paredIzq3->setMatriz(new TAfin());
        vector = new PV3D(0,1.7,0.7,1);
        paredIzq3->getM()->trasladar(vector);
        delete vector;
        objetos->inserta((Objeto3D*)paredIzq3);

        //Puerta
        Puerta* puerta = new Puerta(0.05, 0.9, 1.7, 1, 1, 1,true,0);
        puerta->setMatriz(new TAfin());
        vector = new PV3D(0.0, 0.0, 0.7, 1);
        puerta->getM()->trasladar(vector);
        delete vector;
        vector = new PV3D(0.0, 1.0, 0.0, 1);
        puerta->getM()->rotar(90,vector);
        delete vector;
        objetos->inserta((Objeto3D*)puerta);
    }
}

//---------------------------------------------------------------------------

void Habitacion::dibujar() {
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

Habitacion::~Habitacion() {
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

void Habitacion::cambiaTV(){
     if(objetos != NULL){
        objetos->inicia();
        Objeto3D* aux;
        for(int i=0;i<objetos->getLongitud();i++){
            aux = objetos->getActual();
            if( typeid(*aux) == typeid(Television)){
                ((Television*)aux)->cambiaTV();
            }
            objetos->avanza();
        }
     }
}

//---------------------------------------------------------------------------

bool Habitacion::cambiaPuerta(){
     if(objetos != NULL){
        objetos->inicia();
        Objeto3D* aux;
        for(int i=0;i<objetos->getLongitud();i++){
            aux = objetos->getActual();
            if( typeid(*aux) == typeid(Puerta)){
                return (((Puerta*)aux)->cambiaPuerta());
            }
            objetos->avanza();
        }
     }
    return false;
}

//---------------------------------------------------------------------------

#pragma package(smart_init)



