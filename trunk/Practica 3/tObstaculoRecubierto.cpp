//---------------------------------------------------------------------------

 #include <vcl.h>
 #pragma hdrstop
 #include "tObstaculoRecubierto.h"

//---------------------------------------------------------------------------

 const double epsilon = 0.0000000001;

//---------------------------------------------------------------------------

 tObstaculoRecubierto::tObstaculoRecubierto():tObstaculo(){

    interior = NULL;
    corteza = NULL; 
 }

//-------------------------------------------------

 tObstaculoRecubierto::tObstaculoRecubierto(PuntoV2F* centro,int nVertices,int lado, double radio)
 {
 /*Hay que tener en cuenta
        int numVertices;
        PuntoV2F** vertices;
        PuntoV2F** normales;
        Que creo que hay que asignarle los valores para la corteza
 */
    //Interior
    /*if (interior != NULL){
        delete interior;
    } */
    //Es un poligono convexo
        interior = new tConvexo(centro,nVertices,lado);

    //Corteza
    /*if (corteza != NULL){
        delete corteza;
    }*/
     PuntoV2F* origen = NULL;
    PuntoV2F* destino = NULL;
    PuntoV2F* normal = NULL;
    //Prueba: El numero de vertices va a ser los del interior*2+interior*numeroPuntosArco( que van a ser 10)
        setNumVertices(interior->getNumVertices()*2);//falta sumar los arcos
        PuntoV2F** verticesAux = new PuntoV2F*[getNumVertices()];
        int num = 0;
    //
    for(int i=0;i<interior->getNumVertices();i++){
        origen = interior->getVertice(i);
        origen = new PuntoV2F(origen);
        if( i == interior->getNumVertices()-1){
            destino = interior->getVertice(0);
            destino = new PuntoV2F(destino);
        }
        else{
            destino = interior->getVertice(i+1);
            destino = new PuntoV2F(destino);
        }
        normal = interior->getNormal(i);
        normal = new PuntoV2F(normal);
        normal->normalizar();
        normal->escalar(radio);
        origen->sumar(normal);
        destino->sumar(normal);
        verticesAux[num] = origen;
        num++;
        verticesAux[num] = destino;
        num++;
        delete normal;
    }

    corteza = new tConvexo(getNumVertices(),verticesAux);
    PuntoV2F** verticesAux2 = new PuntoV2F*[getNumVertices()];
    PuntoV2F* punto = NULL;
    for(int i=0;i<getNumVertices();i++){
        punto = new PuntoV2F(verticesAux[i]);
        verticesAux2[i] = punto;
    }
    setVertices(corteza->getNumVertices(),verticesAux2);


 }

//-------------------------------------------------

 tObstaculoRecubierto::tObstaculoRecubierto(int nVertices,PuntoV2F** vertices,int tipo,double radio):tObstaculo(){
    //Tenemos que construir los 2 obstaculos: interior y corteza
    /*Hay que tener en cuenta
        int numVertices;
        PuntoV2F** vertices;
        PuntoV2F** normales;
        Que creo que hay que asignarle los valores para la corteza
     */
    //Interior
   /* if (interior != NULL){
        delete interior;
    }*/
    if( tipo == 0){
    //Entonces es un poligono convexo
        interior = new tConvexo(nVertices,vertices);
    }
    else{//Es un segmento
        interior = new tSegmento(nVertices,vertices);
    }

    //Corteza
    /* if (corteza != NULL){
        delete corteza;
    } */
    PuntoV2F* origen = NULL;
    PuntoV2F* destino = NULL;
    PuntoV2F* normal = NULL;
    //Prueba: El numero de vertices va a ser los del interior*2+interior*numeroPuntosArco( que van a ser 10)
        setNumVertices(interior->getNumVertices()*2);//falta sumar los arcos
        PuntoV2F** verticesAux = new PuntoV2F*[getNumVertices()];
        int num = 0;
    //
    for(int i=0;i<interior->getNumVertices();i++){
        origen = interior->getVertice(i);
        origen = new PuntoV2F(origen);
        if( i == interior->getNumVertices()-1){
            destino = interior->getVertice(0);
            destino = new PuntoV2F(destino);
        }
        else{
            destino = interior->getVertice(i+1);
            destino = new PuntoV2F(destino);
        }
        normal = interior->getNormal(i);
        normal = new PuntoV2F(normal);
        normal->normalizar();
        normal->escalar(radio);
        origen->sumar(normal);
        destino->sumar(normal);
        verticesAux[num] = origen;
        num++;
        verticesAux[num] = destino;
        num++;
        delete normal;
    }

    corteza = new tConvexo(getNumVertices(),verticesAux);
    PuntoV2F** verticesAux2 = new PuntoV2F*[getNumVertices()];
    PuntoV2F* punto = NULL;
    for(int i=0;i<getNumVertices();i++){
        punto = new PuntoV2F(verticesAux[i]);
        verticesAux2[i] = punto;
    }
    setVertices(corteza->getNumVertices(),verticesAux2);

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
	interior->draw();

    //Para las pruebas, dibujar las normales
    glColor3f(0.5,0.1,0.5);
	glBegin(GL_POINTS);
		for (int i=0;i<corteza->getNumVertices();i++){
			glVertex2f(corteza->getNormal(i)->getX(),corteza->getNormal(i)->getY());
		}
	glEnd();

    //Mas pruebas, dibujar la corteza
    glColor3f(0,1,1);
	glBegin(GL_LINE_LOOP);
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
