//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "Espiral.h"


Espiral::Espiral():Malla()
{
        numLados = 0;
        numCapas = 0;
        radio = 0;
}



//-------------------------------------------------



 Espiral::Espiral(int nVertices, PV3D** v, int nNormales, PV3D** n,
                  int nCaras, Cara** c, int nP, int nQ, double r):Malla(nVertices, v,
                                                                 nNormales, n, nCaras, c)

 {
        numLados = nP;
        numCapas = nQ;
        radio = r;
 }



//-------------------------------------------------



 Espiral::~Espiral(){}



//-------------------------------------------------



 int Espiral::getNumLados()

 {

        return numLados;

 }



//-------------------------------------------------



 int Espiral::getNumCapas()

 {

        return numCapas;

 }



//-------------------------------------------------



 double Espiral::getRadio()

 {

        return radio;

 }



//---------------------------------------------------------------------------



 #pragma package(smart_init)

//---------------------------------------------------------------------------

#pragma package(smart_init)
