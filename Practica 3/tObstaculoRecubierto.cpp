//---------------------------------------------------------------------------

 #include <vcl.h>
 #pragma hdrstop
 #include "tObstaculoRecubierto.h"

//---------------------------------------------------------------------------

 const double epsilon = 0.0000000001;

//---------------------------------------------------------------------------

 tObstaculoRecubierto::tObstaculoRecubierto(){

    interior = NULL;
    corteza = NULL; 
 }

//-------------------------------------------------

 tObstaculoRecubierto::tObstaculoRecubierto(PuntoV2F* centro,int nVertices,int lado)
 {
    //Interior
    if (interior != NULL){
        delete interior;
    }
    //Es un poligono convexo
        interior = new tConvexo(centro,nVertices,lado);

    //Corteza
    
 }

//-------------------------------------------------

 tObstaculoRecubierto::tObstaculoRecubierto(int nVertices,PuntoV2F** vertices,int tipo){
    //Tenemos que construir los 2 obstaculos: interior y corteza

    //Interior
    if (interior != NULL){
        delete interior;
    }
    if( tipo == 0){
    //Entonces es un poligono convexo
        interior = new tConvexo(nVertices,vertices);
    }
    else{//Es un segmento
        interior = new tSegmento(nVertices,vertices);
    }

    //Corteza



 }

//-------------------------------------------------

 tObstaculoRecubierto::~tObstaculoRecubierto(){
    if (interior != NULL){
        delete interior;
        interior = NULL;
    }
    if (corteza != NULL){
        delete corteza;
        corteza = NULL;
    }  
 }

//-------------------------------------------------

 void tObstaculoRecubierto::draw()
 {
	glColor3f(1,0,0);
	glBegin(GL_POLYGON);
		for (int i=0;i<interior->getNumVertices();i++){
			glVertex2f(interior->getVertice(i)->getX(),interior->getVertice(i)->getY());
		}
	glEnd();

    //Para las pruebas, dibujar las normales
    glColor3f(0.5,0.1,0.5);
	glBegin(GL_POINTS);
		for (int i=0;i<corteza->getNumVertices();i++){
			glVertex2f(corteza->getNormal(i)->getX(),corteza->getNormal(i)->getY());
		}
	glEnd();

    //Mas pruebas, dibujar la corteza
    glColor3f(0,1,1);
	glBegin(GL_LINES);
		for (int i=0;i<corteza->getNumVertices();i++){
			glVertex2f(corteza->getVertice(i)->getX(),corteza->getVertice(i)->getY());
		}
	glEnd();

 }

//-------------------------------------------------

 bool tObstaculoRecubierto::colisionVsPelota(tPelota* pelota, double& tIn, PuntoV2F*& normal)
 {
	return corteza->colisionVsPelota(pelota, tIn, normal);
 }

//---------------------------------------------------------------------------

 #pragma package(smart_init)
