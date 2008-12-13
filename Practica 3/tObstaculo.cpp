//---------------------------------------------------------------------------

 #include <vcl.h>
 #pragma hdrstop
 #include "tObstaculo.h"

//---------------------------------------------------------------------------

 tObstaculo::tObstaculo()
 {
	numVertices = 0;
	vertices = NULL;
	normales = NULL;
 }

//-------------------------------------------------

 tObstaculo::tObstaculo(int nVertices,PuntoV2F** vVertices)
 {
	numVertices = nVertices;
	vertices = vVertices;

	//CALCULAMOS LAS NORMALES
	normales = new PuntoV2F*[numVertices];
	for (int i=0;i<numVertices;i++){
		//Calculamos la normal
		PuntoV2F* origen = vertices[i];
		PuntoV2F* destino;
		if (i == (numVertices-1)){
			destino = new PuntoV2F(vertices[0]);
		}
		else{
			destino = new PuntoV2F(vertices[i+1]);
		}
		destino->restar(origen);
		PuntoV2F* normal = new PuntoV2F(destino->getY()/2.0,-(destino->getX())/2.0);
		delete destino;
		destino = NULL;
		normales[i] = normal;
	}
 }

//-------------------------------------------------

 tObstaculo::~tObstaculo()
 {
	if(vertices != NULL){
		for(int i=0;i<numVertices;i++){
			if (vertices[i] != NULL){
				delete vertices[i];
				vertices[i] = NULL;
			}
		}
		delete []vertices;
		vertices = NULL;
	}

	if(normales != NULL){
		for(int i=0;i<numVertices;i++){
			if (normales[i] != NULL){
				delete normales[i];
				normales[i] = NULL;
			}
		}
		delete []normales;
		normales = NULL;
	}
 }

//-------------------------------------------------

 int tObstaculo::getNumVertices()
 {
    return numVertices;
 }

//-------------------------------------------------

 void tObstaculo::draw(){}

//-------------------------------------------------

 void tObstaculo::setVertices(int nVertices, PuntoV2F** vVertices)
 {
        if(vertices != NULL){
            for(int i=0;i<numVertices;i++){
				if (vertices[i] != NULL){
					delete vertices[i];
					vertices[i] = NULL;
				}
	        }
			delete []vertices;
			vertices = NULL;
        }

        if(normales != NULL){
			for(int i=0;i<numVertices;i++){
				if (normales[i]!=NULL){
					delete normales[i];
					normales[i] = NULL;
				}
	        }
            delete []normales;
			normales = NULL;
        }

        numVertices = nVertices;
        vertices = vVertices;

        //CALCULAMOS LAS NORMALES
        normales = new PuntoV2F*[numVertices];
        for (int i=0;i<numVertices;i++){
			//Calculamos la normal
			PuntoV2F* origen = vertices[i];
			PuntoV2F* destino;
			if (i==numVertices-1){
				destino = new PuntoV2F(vertices[0]);
			}
			else{
				destino = new PuntoV2F(vertices[i+1]);
			}
			destino->restar(origen);
			PuntoV2F* normal = new PuntoV2F(destino->getY()/2.0,-(destino->getX())/2.0);
			delete destino;
			destino = NULL;
			normales[i] = normal;
        }
 }

//-------------------------------------------------

 bool tObstaculo::colisionVsPelota(tPelota* pelota, double& tIn, PuntoV2F*& normal){}

//-------------------------------------------------

 PuntoV2F* tObstaculo::getVertice(int i)
 {
	PuntoV2F* vertice = NULL;
	if(i < numVertices){
		vertice = vertices[i];
	}
	return vertice;

 }

//-------------------------------------------------

 PuntoV2F* tObstaculo::getNormal(int i)
 {
	PuntoV2F* normal = NULL;
	if(i < numVertices){
		normal = normales[i];
	}
	return normal;

 }

//---------------------------------------------------------------------------

 #pragma package(smart_init)
