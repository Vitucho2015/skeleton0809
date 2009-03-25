//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Objeto3D.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

void Objeto3D::setColor(Color* color){
	this->color=color;
}

//---------------------------------------------------------------------------

void Objeto3D::setMatriz(TAfin* m){
    matriz = m;
}

//---------------------------------------------------------------------------

TAfin* Objeto3D::getM(){
	return this->matriz;
}

//---------------------------------------------------------------------------

Color* Objeto3D::getColor(){
    return color;
}

//---------------------------------------------------------------------------
