//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Escena.h"

//---------------------------------------------------------------------------

Escena::Escena() {

    objetos = new Lista<Objeto3D>();
    this->matriz = new TAfin();
    Habitacion *habitacion1 = new Habitacion(1);
    //habitacion1->setMatriz(new TAfin());
    objetos->inserta((Objeto3D*)habitacion1);
    Habitacion *habitacion2 = new Habitacion(2);
    //habitacion2->setMatriz(new TAfin());
    //PV3D* vector = new PV3D(2, 0.0, 0.0, 1);
    //habitacion2->getM()->trasladar(vector);
    //delete vector;
    objetos->inserta((Objeto3D*)habitacion2);
}

//---------------------------------------------------------------------------

void Escena::dibujar() {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glMultMatrixd(this->getM()->getMatriz());    
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
    glPopMatrix();
}

//---------------------------------------------------------------------------

Escena::~Escena() {
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

void Escena::cambiaTV(int numHabitacion) {
     if(objetos != NULL){
        objetos->inicia();
        Objeto3D* aux;
        for(int i=0;i<objetos->getLongitud();i++){
            aux = objetos->getActual();
            if( typeid(*aux) == typeid(Habitacion)){
                ((Habitacion*)aux)->cambiaTV();
            }
            objetos->avanza();
        }
     }
}

//---------------------------------------------------------------------------

bool Escena::cambiaPuerta(int numHabitacion) {
     if(objetos != NULL){
        objetos->inicia();
        Objeto3D* aux;
        for(int i=0;i<objetos->getLongitud();i++){
            aux = objetos->getActual();
            if( typeid(*aux) == typeid(Habitacion)){
                return(((Habitacion*)aux)->cambiaPuerta());
            }
            objetos->avanza();
        }
     }
    return false;
}

//---------------------------------------------------------------------------

void Escena::escalar(PV3D* v, int n) {
    switch (n){
        case 1:{ //Escena entera
                this->getM()->escalar(v);
                break;
               }
        case 2://Lampara
                    {
                if(objetos != NULL){
                    objetos->inicia();
                    Objeto3D* aux;
                    for(int i=0;i<objetos->getLongitud();i++){
                        aux = objetos->getActual();
                        if( typeid(*aux) == typeid(Habitacion)){
							((Habitacion*)aux)->escalarLampara(v);
                        }
                        objetos->avanza();
                    }

                }
                break;
				}
        case 3://Muebles
                 if(objetos != NULL){
                    objetos->inicia();
                    Objeto3D* aux;
                    for(int i=0;i<objetos->getLongitud();i++){
                        aux = objetos->getActual();
                        if( typeid(*aux) == typeid(Habitacion)){
							((Habitacion*)aux)->escalarMuebles(v);
                        }
                        objetos->avanza();
                    }

                }
                break;
    };
}

//---------------------------------------------------------------------------

void Escena::rotar(PV3D* v, int grados, int n) {
        switch (n){
        case 1:{ //Escena entera
                this->getM()->rotar(grados,v);
                break;
               }
        case 2://Lampara
                    {
                if(objetos != NULL){
                    objetos->inicia();
                    Objeto3D* aux;
                    for(int i=0;i<objetos->getLongitud();i++){
                        aux = objetos->getActual();
                        if( typeid(*aux) == typeid(Habitacion)){
							((Habitacion*)aux)->rotarLampara(v,grados);
                        }
                        objetos->avanza();
                    }

                }
                break;
				}
        case 3://Muebles
                 if(objetos != NULL){
                    objetos->inicia();
                    Objeto3D* aux;
                    for(int i=0;i<objetos->getLongitud();i++){
                        aux = objetos->getActual();
                        if( typeid(*aux) == typeid(Habitacion)){
							((Habitacion*)aux)->rotarMuebles(v,grados);
                        }
                        objetos->avanza();
                    }

                }
                break;
    };
}


//---------------------------------------------------------------------------

void Escena::trasladar(PV3D* v, int n) {
        switch (n){
        case 1:{ //Escena entera
                this->getM()->trasladar(v);
                break;
               }
        case 2://Lampara
                    {
                if(objetos != NULL){
                    objetos->inicia();
                    Objeto3D* aux;
                    for(int i=0;i<objetos->getLongitud();i++){
                        aux = objetos->getActual();
                        if( typeid(*aux) == typeid(Habitacion)){
							((Habitacion*)aux)->trasladarLampara(v);
                        }
                        objetos->avanza();
                    }

                }
                break;
				}
        case 3://Muebles
                 if(objetos != NULL){
                    objetos->inicia();
                    Objeto3D* aux;
                    for(int i=0;i<objetos->getLongitud();i++){
                        aux = objetos->getActual();
                        if( typeid(*aux) == typeid(Habitacion)){
							((Habitacion*)aux)->trasladarMuebles(v);
                        }
                        objetos->avanza();
                    }

                }
                break;
    };
}

//---------------------------------------------------------------------------

#pragma package(smart_init)
