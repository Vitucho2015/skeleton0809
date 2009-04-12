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

#pragma package(smart_init)
