//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Toro.h"

//---------------------------------------------------------------------------

Toro::Toro(int numLados, int particiones, GLfloat r1, GLfloat r2) {
    nQ = particiones;
	nP = numLados;
	radio1 = r1;  //(r1, 0, 0) dentro del polígono
	radio2 = r2;

	numVertices = nQ * nP;
	numCaras = numNormales = numVertices;
	vertices = new PV3D*[numVertices];
	caras = new Cara*[numCaras];
	normales = new PV3D*[numNormales];
	lados = nQ;

	//polígono
	PV3D** poligono = new PV3D*[numLados];
	GLfloat grados =  2*M_PI/ (GLfloat) numLados;
	for(int i = 0; i<numLados; i++)
	  poligono[i] = new PV3D(radio2*cos(i*grados), radio2*sin(i*grados), 0.0, 1);

	//crear vertices
	Frenet(poligono, numLados);

	for(int i = 0; i < numLados; i++){
		delete poligono[i];
	}
	delete []poligono;

	int cont = 0;
	int v2[4];
	int valor;
	for(int i = 1; i <= nQ; i++) {
		for(int j = 0; j < nP; j++) {
			if(i == nQ) {
				v2[0] = nP*(i-1)+j;
				v2[1] = nP*(i-1)+((j+1)%nP);
				v2[2] = ((j+1)%nP);
				v2[3] = j;
			}
			else {
				v2[0] = nP*(i-1)+j;
				v2[1] = nP*(i-1)+((j+1)%nP);
				v2[2] = nP*(i)+((j+1)%nP);
				v2[3] = nP*(i)+j;
			}
			caras[cont] = new Cara(4, v2, cont);
			cont++;
		}
	}
	Newell();
}

//----------------------------------------------------------------------

Toro::~Toro(){
    delete matriz;
    delete color;
}

//----------------------------------------------------------------------

void Toro::Frenet(PV3D** poligono, int l){

	PV3D* puntoC; //circunferencia
	PV3D* puntoT; //primera derivada de c
	PV3D* puntoC2; //segunda derivada de c
	PV3D* puntoB;
	PV3D* puntoN; //normal del punto
	GLfloat xAux, yAux, zAux;
	GLfloat angulo = 0;

	for(int i = 0; i < lados; i++) {
	
		puntoC = new PV3D(radio2*sin(angulo), 0, radio2*cos(angulo),1);
		puntoC->normalizar();

		puntoT = new PV3D(radio2*cos(angulo), 0, -radio2*sin(angulo),1);
		puntoT->normalizar();

		puntoC2 = new PV3D(-radio2*sin(angulo), 0, -radio2*cos(angulo),1);
		puntoC2->normalizar();

		puntoB = puntoT->prodVectorial(puntoC2);
		puntoB->normalizar();

		puntoN = puntoB->prodVectorial(puntoT);
		puntoN->normalizar();

		for(int j = 0; j < l; j++) {
		
			xAux = (puntoN->getX()* poligono[j]->getX()) +(puntoB->getX()* poligono[j]->getY()) + (puntoN->getX()* poligono[j]->getZ()) + (puntoC->getX());
			yAux = (puntoN->getY()* poligono[j]->getX()) +(puntoB->getY()* poligono[j]->getY()) + (puntoT->getY()* poligono[j]->getZ()) + (puntoC->getY());
			zAux = (puntoN->getZ()* poligono[j]->getX()) +(puntoB->getZ()* poligono[j]->getY()) + (puntoN->getZ()* poligono[j]->getZ()) + (puntoC->getZ());
			vertices[i*l + j] = new PV3D(xAux, yAux, zAux, 1);
		}
		delete puntoC;
		delete puntoT;
		delete puntoC2;
		delete puntoB;
		delete puntoN;
		angulo = angulo + (2*M_PI/(GLfloat)lados);
	}
}

//----------------------------------------------------------------------

/*
void Toro::moverPoligono(PV3D** poligono, int lados, PV3D* centro, GLfloat grados, int indice){
    GLfloat xAux, yAux, zAux;
    PV3D* punto;
    for(int i = 0; i < lados; i++) {
        punto = poligono[i];
        xAux = ((centro->getX() + punto->getX())*cos(grados)) + ((centro->getZ() + punto->getZ())*sin(grados));
        yAux = punto->getY() + centro->getY();
        zAux = ((centro->getZ() + punto->getZ())*cos(grados)) - ((centro->getX() + punto->getX())*sin(grados));
        vertices[(indice*lados) + i] = new PV3D(xAux, yAux, zAux, 1);
    }
}
*/

//----------------------------------------------------------------------

#pragma package(smart_init)
