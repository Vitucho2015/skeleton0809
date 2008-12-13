//---------------------------------------------------------------------------

 #include <vcl.h>
 #pragma hdrstop
 #include "tCirculo.h"

//---------------------------------------------------------------------------

 tCirculo::tCirculo():tObstaculo()
 {
	centro = NULL;
 }

//-------------------------------------------------

 tCirculo::tCirculo(double r, PuntoV2F* c):tObstaculo()
 {
	centro = c;
	radio = r;

	//Aproximamos un circulo con 20 lineas
	int nVertices = 20;
	PuntoV2F** vVertices = new PuntoV2F*[nVertices];
	double alfa = 360/nVertices;

	//Calculamos los vértices
	PuntoV2F* origen = new PuntoV2F(centro->getX()+radio,centro->getY());
	vVertices[0] = origen;
	for (int i=1;i<nVertices;i++){
		//Calculamos el punto
		PuntoV2F* punto = new PuntoV2F(
		  centro->getX()+radio*cos((i*alfa*3.141592)/180),
		  centro->getY()+radio*sin((i*alfa*3.141592)/180));
		vVertices[i] = punto;
	}

	setVertices(nVertices,vVertices);
 }

//-------------------------------------------------

 tCirculo::~tCirculo()
 {
	if (centro != NULL){
		delete centro;
		centro = NULL;
	}
 }

//-------------------------------------------------

 void tCirculo::draw()
 {
	glColor3f(1,0,0);
	glBegin(GL_POLYGON);
	for (int i=0;i<getNumVertices();i++){
		glVertex2f(getVertice(i)->getX(),getVertice(i)->getY());
	}
    glEnd();
 }

//-------------------------------------------------

 bool tCirculo::colisionVsPelota(tPelota* pelota, double& tIn, PuntoV2F*& normal)
 {
	//Función booleana para evaluar el corte
	bool corte = false;
	//Radio del circulo
	double r1 = radio;
	//Radio de la pelota
	double r2 = pelota->getRadio();
	//Centro del ciculo
	PuntoV2F* a1 = new PuntoV2F(centro);
	//Centro de la pelota
	PuntoV2F* posicion = pelota->getPosicion();
	PuntoV2F* a2 = new PuntoV2F(posicion);
	//Sentido de la pelota
	PuntoV2F* sentido = pelota->getSentido();
	PuntoV2F* s = new PuntoV2F(sentido);
	//Sentido en perpendicular de la pelota
	PuntoV2F* sPer = new PuntoV2F(-(s->getY()),s->getX());
	//Vector entre los dos centros
	PuntoV2F* a2a1 = new PuntoV2F(a1->getX()-a2->getX(),a1->getY()-a2->getY());
	//Módulo de s
	double modS = s->modulo();
	//Módulo de sPer
	double modSPer = sPer->modulo();

	//Calculamos parámentros
	double a0 = a2a1->productoEscalar(sPer) / sPer->productoEscalar(sPer);
	double b0 = a2a1->productoEscalar(s) / s->productoEscalar(s);
	double d0 = sqrt(a0*a0) * modSPer;
	if((d0<(r1+r2))&&(b0>0)){
		double d2 = sqrt((r1+r2)*(r1+r2)-(d0*d0));
		double d1 = (sqrt(b0*b0) * modS) - d2;

		//Comprobamos condición de corte
		if(modS >= d1){
			corte = true;
			
			//Actualizamos variables a devolver
			tIn=d1/modS;
			double pImpX = pelota->getPosicion()->getX()+pelota->getSentido()->getX()*tIn;
			double pImpY = pelota->getPosicion()->getY()+tIn*(pelota->getSentido()->getY());
			normal = new PuntoV2F(centro->getX()-pImpX,centro->getY()-pImpY);
		}
	}

	//Borramos variables usadas
	delete a1;
	a1 = NULL;
	delete a2;
	a2 = NULL;
	delete s;
	s = NULL;
	delete sPer;
	sPer = NULL;
	delete a2a1;
	a2a1 = NULL;

	return corte;
 }

//-------------------------------------------------

 PuntoV2F* tCirculo::getCentro()
 {
    return centro;
 }

//-------------------------------------------------

 double tCirculo::getRadio()
 {
	return radio;
 }

//-------------------------------------------------

 void tCirculo::rotar(PuntoV2F* c, double angulo)
 {
	centro->rotaP(c,angulo);
	PuntoV2F** v = new PuntoV2F*[getNumVertices()];
	for (int i=0;i<getNumVertices();i++){
		PuntoV2F* vOriginal = getVertice(i);
		PuntoV2F* vRotado = new PuntoV2F(vOriginal);
		vRotado->rotaP(c, angulo);
		v[i] = vRotado;
	}
	setVertices(getNumVertices(),v);
 }

//---------------------------------------------------------------------------

 #pragma package(smart_init)
