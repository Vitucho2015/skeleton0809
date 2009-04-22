//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Escena.h"

//---------------------------------------------------------------------------

Escena::Escena() {
    habitacion1 = new Habitacion(1);
    habitacion2 = new Habitacion(2);
}

//---------------------------------------------------------------------------

void Escena::dibujar() {
    glMatrixMode(GL_MODELVIEW);
 	glPushMatrix();
   		glMultMatrixd(habitacion1->getM()->getMatriz());
		habitacion1->dibujar();
	glPopMatrix();
    glPushMatrix();
	 	glMultMatrixd(habitacion2->getM()->getMatriz());
		habitacion2->dibujar();
	glPopMatrix();
}

//---------------------------------------------------------------------------

Escena::~Escena() {
    delete habitacion1;
    delete habitacion2;
}

//---------------------------------------------------------------------------

void Escena::cambiaTV(int numHabitacion) {
    if(numHabitacion == 1){
        habitacion1->cambiaTV();
    }
    else{
        habitacion2->cambiaTV();
    }
}

//---------------------------------------------------------------------------

bool Escena::cambiaPuerta(int numHabitacion) {
    if(numHabitacion == 1){
        return (habitacion1->cambiaPuerta());
    }
    else{
        return (habitacion2->cambiaPuerta());
    }
}

//---------------------------------------------------------------------------

void Escena::escalar(PV3D* v, int n) {
    switch (n){
        case 1:{ //Escena entera
                float anchoAnt = habitacion1->getAncho();
                habitacion1->escalar(v,n);
                float anchoNue = v->getX()*anchoAnt;
                float dif = anchoNue - anchoAnt;
                PV3D* vector = new PV3D(dif,0,0,1);
                habitacion2->trasladar(vector,1);
                delete vector;
                habitacion2->escalar(v,n);
                break;
               }
        case 2://Lampara
                habitacion1->escalar(v,n);
                break;
        case 3://Muebles
                habitacion1->escalar(v,n);
                break;
    };
}

//---------------------------------------------------------------------------

void Escena::rotar(PV3D* v, int grados, int n) {
    switch (n){
        case 1:{ //Escena entera
                habitacion1->rotar(v,grados,n);
                habitacion2->rotar(v,grados,n);
                break;
               }
        case 2://Lampara
                habitacion1->rotar(v,grados,n);
                break;
        case 3://Muebles
                habitacion1->rotar(v,grados,n);
            break;
    };
}

//---------------------------------------------------------------------------

void Escena::trasladar(PV3D* v, int n) {
    switch (n){
        case 1:{ //Escena entera
                habitacion1->trasladar(v,n);
                habitacion2->trasladar(v,n);
                break;
               }
        case 2://Lampara
                habitacion1->trasladar(v,n);
                break;
        case 3://Muebles
                habitacion1->trasladar(v,n);
            break;
    };
}

//---------------------------------------------------------------------------

#pragma package(smart_init)
