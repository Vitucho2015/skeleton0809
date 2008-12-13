//---------------------------------------------------------------------------

 #include <vcl.h>
 #pragma hdrstop
 #include "tConvexo.h"

//---------------------------------------------------------------------------

 const double epsilon = 0.0000000001;

//---------------------------------------------------------------------------

 tConvexo::tConvexo():tObstaculo(){
 
 }

//-------------------------------------------------

 tConvexo::tConvexo(PuntoV2F* centro,int nVertices,int lado):tObstaculo()
 {
	PuntoV2F** vVertices = new PuntoV2F*[nVertices];
	float alfa = 360/nVertices;
	float radio = lado / sin((alfa*3.141592)/180);

	//Calculamos los v�rtices
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

 tConvexo::tConvexo(int nVertices,PuntoV2F** vertices):tObstaculo(nVertices, vertices){}

//-------------------------------------------------

 tConvexo::~tConvexo(){}

//-------------------------------------------------

 void tConvexo::draw()
 {
	glColor3f(1,1,0);
	glBegin(GL_POLYGON);
		for (int i=0;i<getNumVertices();i++){
			glVertex2f(getVertice(i)->getX(),getVertice(i)->getY());
		}
	glEnd();
 }

//-------------------------------------------------

 bool tConvexo::colisionVsPelota(tPelota* pelota, double& tIn, PuntoV2F*& normal)
 {
	//ALGORITMO DE CYRUS-BECK

	int i = 0;
	bool seguir = true;
	bool corte = false;
	PuntoV2F* n;

	//Inicializamos tIn, tOut
	tIn = 0;
	double tOut = 1;
	PuntoV2F* A = pelota->getPosicion();
	PuntoV2F* v = pelota->getSentido();
	double radio = pelota->getRadio();

	while((i<getNumVertices())&&(seguir)){
		//Punto B de la arista
		PuntoV2F* destino;
		if (i == getNumVertices()-1){
			destino = getVertice(0);
		}
		else{
			destino = getVertice(i+1);
		}
		PuntoV2F* B = new PuntoV2F(destino);

		//Normal de la arista
		n = getNormal(i);

		//Obtenemos el punto A especial para la arista
		PuntoV2F* nAux = new PuntoV2F(n);
		nAux->normalizar();
		nAux->escalar(radio);
		PuntoV2F* Ae =  new PuntoV2F(A);
		Ae->restar(nAux);
		delete nAux;
		nAux = NULL;

		//V*n
		double vn = v->productoEscalar(n);
		//Vector AB
		PuntoV2F* ab = new PuntoV2F(B);
		ab->restar(Ae);

		if (vn == 0){
			if(ab->productoEscalar(n)<=epsilon){
				seguir = false;
			}
		}
		else{
			double tHit = ab->productoEscalar(n)/vn;
			//Entrada
			if(vn <= epsilon){
				if(tIn < tHit){
					tIn = tHit;
					normal = n;
				}
			}
			//Salida
			else{
				if(tOut > tHit){
					tOut = tHit;
				}
			}
		}
		seguir = (tIn <= tOut);
		i++;

		//Borramos estructuras de apoyo
		delete B;
		B = NULL;
		delete ab;
		ab = NULL;
		delete Ae;
		Ae = NULL;
	}

	//Comprobamos condiciones de colisi�n
	if(((tIn>epsilon)&&(tIn<=1)&&(tOut>=1))){
		corte = true;
	}

	//Clonamos la normal
	if(corte){
		normal = new PuntoV2F(normal);
	}

	return corte;
 }

//-------------------------------------------------

 void tConvexo::rotar(PuntoV2F* c, double angulo)
 {
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
