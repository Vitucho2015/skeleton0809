//---------------------------------------------------------------------------

 #include <vcl.h>
 #pragma hdrstop
 #include "tObstaculoRecubierto.h"

//---------------------------------------------------------------------------

 const double epsilon = 0.0001;

//---------------------------------------------------------------------------

 tObstaculoRecubierto::tObstaculoRecubierto():tObstaculo(){

    interior = NULL;
    corteza = NULL;
 }

//-------------------------------------------------

 tObstaculoRecubierto::tObstaculoRecubierto(PuntoV2F* centroPoligono,int nVertices,int lado, double radio)
 {
 /*Hay que tener en cuenta
        int numVertices;
        PuntoV2F** vertices;
        PuntoV2F** normales;
        Que creo que hay que asignarle los valores para la corteza
 */
    //Es un poligono convexo
    interior = new tConvexo(centroPoligono,nVertices,lado);
    PuntoV2F* origen = NULL;
    PuntoV2F* destino = NULL;
    PuntoV2F* normal = NULL;
    PuntoV2F* centro = NULL;
    double angIni = 0.0;
    double angFin = 0.0;
    nLados = 10;
    int ver = interior->getNumVertices()*nLados;
    setNumVertices(ver);//ya estan sumados los puntos del arco
    PuntoV2F** verticesAux = new PuntoV2F*[getNumVertices()];
    int num = 0;
    for(int i=0;i<interior->getNumVertices();i++){
        origen = interior->getVertice(i);
        origen = new PuntoV2F(origen);

        if( i == interior->getNumVertices()-1){//si estamos en el ultimo vertice
            destino = interior->getVertice(0); //cogemos el primer vertice como destino del ultimo segmento
            destino = new PuntoV2F(destino);
        }
        else{
            destino = interior->getVertice(i+1);  //sino cogemos el siguiente vertice
            destino = new PuntoV2F(destino);
        }


        normal = interior->getNormal(i);
        normal = new PuntoV2F(normal);
        normal->normalizar();
        normal->escalar(radio);
        origen->sumar(normal);
        destino->sumar(normal);
        if(i>0){//Si no es el primer vertice entonces calcular los arcos

                centro = interior->getVertice(i);
                angIni = calculoAngulo(centro,verticesAux[num-1]);
                angFin = calculoAngulo(centro,origen);
                PuntoV2F** puntosArco = calculaArco(centro,angIni,angFin,radio,nLados);
                for(int j=0;j<nLados-2;j++){
                    verticesAux[num] = puntosArco[j];
                    num++;
                }
                verticesAux[num] = origen;
                num++;
        }
        else{
            verticesAux[num] = origen;
            num++;
        }

        verticesAux[num] = destino;
        num++;
        if(i == (interior->getNumVertices()-1)){
            centro = interior->getVertice(0);
            angIni = calculoAngulo(centro,destino);
            angFin = calculoAngulo(centro,verticesAux[0]);
            PuntoV2F** puntosArco = calculaArco(centro,angIni,angFin,radio,nLados);
            for(int j=0;j<nLados-2;j++){
                verticesAux[num] = puntosArco[j];
                num++;
            }
        }
        delete normal;
    }
    /*
    for(int i=0;i<getNumVertices();i++){
        PuntoV2F* punt =verticesAux[i];
        AnsiString x = punt->getX();
        AnsiString y = punt->getY();
        AnsiString v = i;
        ShowMessage("Vertice: "+v+" "+x+" "+y);
    } */
    corteza = new tConvexo(getNumVertices(),verticesAux);

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
    PuntoV2F* centro = NULL;
    double angIni = 0.0;
    double angFin = 0.0;
    nLados = 10;
    int ver = interior->getNumVertices()*nLados;
    setNumVertices(ver);//ya estan sumados los puntos del arco
    PuntoV2F** verticesAux = new PuntoV2F*[getNumVertices()];
    int num = 0;

    for(int i=0;i<interior->getNumVertices();i++){
        origen = interior->getVertice(i);
        origen = new PuntoV2F(origen);

        if( i == interior->getNumVertices()-1){//si estamos en el ultimo vertice
            destino = interior->getVertice(0); //cogemos el primer vertice como destino del ultimo segmento
            destino = new PuntoV2F(destino);
        }
        else{
            destino = interior->getVertice(i+1);  //sino cogemos el siguiente vertice
            destino = new PuntoV2F(destino);
        }


        normal = interior->getNormal(i);
        normal = new PuntoV2F(normal);
        normal->normalizar();
        normal->escalar(radio);
        origen->sumar(normal);
        destino->sumar(normal);
        if(i>0){//Si no es el primer vertice entonces calcular los arcos

                centro = interior->getVertice(i);
                angIni = calculoAngulo(centro,verticesAux[num-1]);
                angFin = calculoAngulo(centro,origen);
                PuntoV2F** puntosArco = calculaArco(centro,angIni,angFin,radio,nLados);
                for(int j=0;j<nLados-2;j++){
                    verticesAux[num] = puntosArco[j];
                    num++;
                }
                verticesAux[num] = origen;
                num++;
        }
        else{
            verticesAux[num] = origen;
            num++;
        }

        verticesAux[num] = destino;
        num++;
        if(i == (interior->getNumVertices()-1)){
            centro = interior->getVertice(0);
            angIni = calculoAngulo(centro,destino);
            angFin = calculoAngulo(centro,verticesAux[0]);
            PuntoV2F** puntosArco = calculaArco(centro,angIni,angFin,radio,nLados);
            for(int j=0;j<nLados-2;j++){
                verticesAux[num] = puntosArco[j];
                num++;
            }
        }
        delete normal;
    }
    /*
    for(int i=0;i<getNumVertices();i++){
        PuntoV2F* punt =verticesAux[i];
        AnsiString x = punt->getX();
        AnsiString y = punt->getY();
        AnsiString v = i;
        ShowMessage("Vertice: "+v+" "+x+" "+y);
    } */
    corteza = new tConvexo(getNumVertices(),verticesAux);
    /*PuntoV2F** verticesAux2 = new PuntoV2F*[getNumVertices()];
    PuntoV2F* punto = NULL;
    for(int i=0;i<getNumVertices();i++){
        punto = new PuntoV2F(verticesAux[i]);
        verticesAux2[i] = punto;
    }
    setVertices(corteza->getNumVertices(),verticesAux2);*/

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

 PuntoV2F** tObstaculoRecubierto::calculaArco(PuntoV2F* centro,double angIni, double angArco, double radio, int nLados)
 {
        PuntoV2F** puntosArco = new PuntoV2F*[nLados-2];//El origen y el destino ya estan añadidos antes
        double angulo = angArco - angIni;

        angulo = abs(angulo);

        if (angulo >180) {angulo = angulo -180;}
        double incrAng = angulo / double (nLados);

        double x = centro->getX() + radio*cos(((angIni*3.141592)/180));
        double y = centro->getY() + radio*sin(((angIni*3.141592)/180));
        for (int i=1;i<nLados-1;i++){
            x = centro->getX() + radio*cos((((angIni+i*incrAng)*3.141592)/180));
            y = centro->getY() + radio*sin((((angIni+i*incrAng)*3.141592)/180));
            PuntoV2F* b = new PuntoV2F(x,y);
            puntosArco[i-1] = b;
        }
        return puntosArco;
 }

//---------------------------------------------------------------------------

double tObstaculoRecubierto::calculoAngulo(PuntoV2F* A, PuntoV2F* B)   {

      double angulo = atan2(B->getY()-A->getY(),B->getX()-A->getX());
      angulo = angulo * ( 180.0 / 3.1415926535 );
      return angulo;
 }

//---------------------------------------------------------------------------

 #pragma package(smart_init)
