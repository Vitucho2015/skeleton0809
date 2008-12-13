//---------------------------------------------------------------------------

 #include <vcl.h>
 #pragma hdrstop
 #include "tPelota.h"

//---------------------------------------------------------------------------

 tPelota::tPelota()
 {
	circulo = NULL;
	sentido = NULL;
	posicion = NULL;
 }

//-------------------------------------------------

 tPelota::tPelota(double r, PuntoV2F* pos, PuntoV2F* paso)
 {
	circulo = new Lista<PuntoV2F>;
	sentido = paso;
	posicion = pos;
	radio = r;
	//Aproximamos un circulo con 60 lineas
	int nVertices = 60;
	double alfa = 360/nVertices;

	//Calculamos los vértices
	PuntoV2F* origen = new PuntoV2F(posicion->getX()+radio,posicion->getY());
	circulo->inserta(origen);
	for (int i=1;i<nVertices;i++){
		//Calculamos el punto
		PuntoV2F* punto = new PuntoV2F(
			posicion->getX()+radio*cos((i*alfa*3.141592)/180.0),
			posicion->getY()+radio*sin((i*alfa*3.141592)/180.0));
		circulo->inserta(punto);
	}
 }

//-------------------------------------------------

 tPelota::~tPelota()
 {
	if(sentido != NULL){
		delete sentido;
		sentido = NULL;
	}
	
	if(posicion != NULL){
		delete posicion;
		posicion = NULL;
	}

	if(circulo != NULL){
		delete circulo;
		circulo = NULL;
	}
 }

//-------------------------------------------------

 void tPelota::avanza()
 {
	posicion->sumar(sentido);
	circulo->inicia();
	for (int i=0;i<circulo->getLongitud();i++){
		PuntoV2F* vertice = circulo->getActual();
		vertice->sumar(sentido);
		circulo->avanza();
	}
 }

//-------------------------------------------------

 void tPelota::draw()
 {
	glColor3f(0,0,1);
	glBegin(GL_POLYGON);
	circulo->inicia();
	for (int i=0;i<circulo->getLongitud();i++){
		PuntoV2F* vertice = circulo->getActual();
		glVertex2f(vertice->getX(),vertice->getY());
		circulo->avanza();
	}
	glEnd();
 }

//-------------------------------------------------

 void tPelota::avanzaYRebota(double tIn, PuntoV2F* normal)
 {;
	PuntoV2F* sAux = new PuntoV2F(sentido);
	sAux->escalar(tIn);
	posicion->sumar(sAux);
	circulo->inicia();
	for (int i=0;i<circulo->getLongitud();i++){
		PuntoV2F* vertice = circulo->getActual();
		vertice->sumar(sAux);
		circulo->avanza();
	}
	delete sAux;

	//Calcular nuevo sentido (choque, refelexion)
	PuntoV2F* v = new PuntoV2F(sentido);
	double valor = 2*((v->productoEscalar(normal))/(normal->productoEscalar(normal)));
	normal->escalar(valor);
	v->restar(normal);
	delete normal;
	delete sentido;
	sentido = v;
 }

//-------------------------------------------------

 double tPelota::getRadio()
 {
        return radio;
 }

//-------------------------------------------------

 PuntoV2F* tPelota::getSentido()
 {
        return sentido;
 }

//-------------------------------------------------

 PuntoV2F* tPelota::getPosicion()
 {
        return posicion;
 }

//-------------------------------------------------

 void tPelota::setSentido(PuntoV2F* s)
 {
        if (sentido != NULL){
			delete sentido;
			sentido = NULL;
        }
        sentido = s;
 }

//---------------------------------------------------------------------------

 #pragma package(smart_init)
