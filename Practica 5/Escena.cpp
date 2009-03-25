//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Escena.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

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
    if(habitacion1 != NULL){
        delete habitacion1;
        habitacion1 = NULL;
    }
    if(habitacion2 != NULL){
        delete habitacion2;
        habitacion2 = NULL;
    }
}

//---------------------------------------------------------------------------




