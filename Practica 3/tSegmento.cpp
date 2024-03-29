//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "tSegmento.h"

//---------------------------------------------------------------------------

 const double epsilon = 0.0001;

//---------------------------------------------------------------------------

 tSegmento::tSegmento():tObstaculo(){

 }
//-------------------------------------------------
 tSegmento::tSegmento(int nVertices,PuntoV2F** vertices):tObstaculo(nVertices, vertices){}

//-------------------------------------------------

 tSegmento::~tSegmento(){}

//-------------------------------------------------

 void tSegmento::draw()
 {
	glColor3f(1,1,0);
	glBegin(GL_LINES);
		for (int i=0;i<getNumVertices();i++){
			glVertex2f(getVertice(i)->getX(),getVertice(i)->getY());
		}
	glEnd();
    /*
    //Para las pruebas, dibujar las normales
    glColor3f(0.5,0.5,0.5);
	glBegin(GL_POINTS);
		for (int i=0;i<getNumVertices();i++){
			glVertex2f(getNormal(i)->getX(),getNormal(i)->getY());
		}
	glEnd();*/
 }

//-------------------------------------------------

 bool tSegmento::colisionVsPelota(tPelota* pelota, double& tIn, PuntoV2F*& normal)
 {
      PuntoV2F* posicion = new PuntoV2F(pelota->getPosicion());
      PuntoV2F* sentido = new PuntoV2F(pelota->getSentido());
      sentido->sumar(posicion);
      PuntoV2F *puntocolision = new PuntoV2F();
      double tinpre;
      double modulototal;
      puntocolision =  inteseccionSegmento(posicion,sentido,getVertice(0),getVertice(1));
      if(puntocolision!=NULL){


            tinpre=(sqrt(pow((puntocolision->getX() - posicion->getX()),2)+pow((puntocolision->getY() - posicion->getY()),2))) ;
            modulototal =(sqrt(pow((sentido->getX() - posicion->getX()),2)+pow((sentido->getY() - posicion->getY()),2))) ;
            tIn = tinpre / modulototal;
            normal = getNormal(0);
            normal = new PuntoV2F(normal);
      }

      if(puntocolision==NULL){
            puntocolision =  inteseccionSegmento(posicion,sentido,getVertice(1),getVertice(0));
            if(puntocolision!=NULL){
                tinpre=(sqrt(pow((puntocolision->getX() - posicion->getX()),2)+pow((puntocolision->getY() - posicion->getY()),2))) ;
                modulototal =(sqrt(pow((sentido->getX() - posicion->getX()),2)+pow((sentido->getY() - posicion->getY()),2))) ;
                tIn = tinpre / modulototal;
                normal = getNormal(1);
                normal = new PuntoV2F(normal);
            }
            
      }

      return (puntocolision != NULL);
 }






PuntoV2F* tSegmento::inteseccionSegmento(PuntoV2F* p1, PuntoV2F* p2, PuntoV2F* p3, PuntoV2F* p4) {



    double x1;double y1;double x2;double y2;
    double x3; double y3; double x4;double y4;


    x1 = p1->getX();
    y1 = p1->getY();

    x2 = p2->getX();
    y2 = p2->getY();

    x3 = p3->getX();
    y3 = p3->getY();

    x4 = p4->getX();
    y4 = p4->getY();



    double d = (x1-x2)*(y3-y4) - (y1-y2)*(x3-x4);
    if (d == 0) return NULL;

    double xi = ((x3-x4)*(x1*y2-y1*x2)-(x1-x2)*(x3*y4-y3*x4))/d;
    double yi = ((y3-y4)*(x1*y2-y1*x2)-(y1-y2)*(x3*y4-y3*x4))/d;

    PuntoV2F* p = new PuntoV2F(xi,yi);
    if (xi-epsilon < min(x1,x2) || xi+epsilon > max(x1,x2)) return NULL;
    if (xi-epsilon < min(x3,x4) || xi+epsilon > max(x3,x4)) return NULL;
    return p;
  }



//-------------------------------------------------
  bool tSegmento::CS(PuntoV2F* p1, PuntoV2F* p2, PuntoV2F* ii, PuntoV2F* sd)
 {
        //Si se borra: devolver falso
        bool control;

        //Obtenemos los codigos de las regiones de los puntos
        GLbyte codP1 = codigoCS(p1,ii,sd);
        GLbyte codP2 = codigoCS(p2,ii,sd);


        //CASOS TRIVIALES
        if ((codP1==0)&&(codP2==0)){   //Est� dentro
                control = true;  //NO BORRAR
        }else{
                if (((codP1)&(codP2))!=0){   //Est� fuera
                        control = false; //BORRAR
        //CASO RECURSIVO
                }else{
                        PuntoV2F* pFuera;
                        PuntoV2F* pAux;
                        GLbyte codFuera;
                        if(codP1!=0){//P1 est� fuera de alguna frontera?
                                pFuera = p1;
                                pAux = p2;
                                codFuera = codP1;

                        }else{  //si no
                                if(codP2!=0){//P2 est� fuera de alguna frontera?
                                        pFuera = p2;
                                        pAux = p1;
                                        codFuera = codP2;
                                }
                        }

                        //Frontera IZQ
                        if(((codFuera)&(8))!=0){
                                recortarIzq(pFuera,pAux,ii);
                        }else{
                                //Frontera INF
                                if(((codFuera)&(1))!=0){
                                        recortarInf(pFuera,pAux,ii);
                                }else{
                                        //Frontera DER
                                        if(((codFuera)&(2))!=0){
                                                recortarDer(pFuera,pAux,sd);
                                        }
                                        //Frontera SUP
                                        else{
                                                recortarSup(pFuera,pAux,sd);
                                        }
                                }
                        }
                        control = CS(pFuera,pAux,ii,sd);
                }
        }

        return control;
 }

//---------------------------------------------------------------------------

 GLbyte tSegmento::codigoCS(PuntoV2F* punto, PuntoV2F* ii, PuntoV2F* sd)
 {
         GLbyte codP;

        codP = codP&00;

        //BIT4
        if(punto->getX()<ii->getX()){
                codP = codP|8;
        }
        //BIT3
        if(punto->getY()>sd->getY()){
                codP = codP|4;
        }
        //BIT2
        if(punto->getX()>sd->getX()){
                codP = codP|2;
        }
        //BIT1
        if(punto->getY()<ii->getY()){
                codP = codP|1;
        }
        
        return codP;
 }

//---------------------------------------------------------------------------

 void tSegmento::recortarDer(PuntoV2F*& p1, PuntoV2F* p2, PuntoV2F* sd)
 //P1 fuera de la regi�n derecha
 {
        double d = (p1->getX() - sd->getX())*((p1->getY()-p2->getY())/(p1->getX()-p2->getX()));
        p1->setX(sd->getX());
        p1->setY(p1->getY()-d);
 }

//---------------------------------------------------------------------------

 void tSegmento::recortarIzq(PuntoV2F*& p1, PuntoV2F* p2, PuntoV2F* ii)
 //P1 fuera de la regi�n izquierda
 {
        double d = (p1->getX() - ii->getX())*((p1->getY()-p2->getY())/(p1->getX()-p2->getX()));
        p1->setX(ii->getX());
        p1->setY(p1->getY()-d);
 }

//---------------------------------------------------------------------------

 void tSegmento::recortarSup(PuntoV2F*& p1, PuntoV2F* p2, PuntoV2F* sd)
 //P1 fuera de la regi�n superior
 {
        double d = (p1->getY() - sd->getY())*((p1->getX()-p2->getX())/(p1->getY()-p2->getY()));
        p1->setX(p1->getX()-d);
        p1->setY(sd->getY());
 }

//---------------------------------------------------------------------------

 void tSegmento::recortarInf(PuntoV2F*& p1, PuntoV2F* p2, PuntoV2F* ii)
 //P1 fuera de la regi�n inferior
 {
        double d = (p1->getY() - ii->getY())*((p1->getX()-p2->getX())/(p1->getY()-p2->getY()));
        p1->setX(p1->getX()-d);
        p1->setY(ii->getY());
 }
//---------------------------------------------------------------------------

 #pragma package(smart_init)
