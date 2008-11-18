//---------------------------------------------------------------------------

 #include <vcl.h>
 #pragma hdrstop
 #include "Linea.h"

//---------------------------------------------------------------------------

 Linea::Linea()
 {
        origen = NULL;
        destino = NULL;
 }

//-------------------------------------------------

 Linea::Linea(Punto* puntoOrigen, Punto* puntoDestino)
 {
        origen = puntoOrigen;
        destino = puntoDestino;
 }

//-------------------------------------------------

 Linea::Linea(Linea* linea)
 {
        origen = new Punto(linea->origen);
        destino = new Punto(linea->destino);
 }



//-------------------------------------------------

 Linea::~Linea()
 {
        if (origen != NULL){
                delete origen;
                origen = NULL;
        }

        if (destino != NULL){
                delete destino;
                destino = NULL;
        }
 }

//-------------------------------------------------

 void Linea::setOrigen(Punto* punto)
 {
        if (origen != NULL){
                delete origen;
        }
        origen = punto;
 }

//-------------------------------------------------

 Punto* Linea::getOrigen()
 {
        return origen;
 }

//-------------------------------------------------

 void Linea::setDestino(Punto* punto)
 {
        if (destino != NULL){
                delete destino;
        }
        destino = punto;
 }

//-------------------------------------------------

 Punto* Linea::getDestino()
 {
        return destino;
 }

//-------------------------------------------------

 void Linea::draw()
 {
        Punto* o = new Punto(origen);
        Punto* d = new Punto(destino);
        Lapiz* lapiz = new Lapiz(o, 0);
        lapiz->lineTo(d);
        delete lapiz;
 }

//-------------------------------------------------

 bool Linea::recorte(Punto* ii, Punto* sd)
 {
        return CS(origen,destino,ii,sd);
 }

//-------------------------------------------------

 bool Linea::CS(Punto* p1, Punto* p2, Punto* ii, Punto* sd)
 {
        //Si se borra: devolver falso
        bool control;

        //Obtenemos los codigos de las regiones de los puntos
        GLbyte codP1 = codigoCS(p1,ii,sd);
        GLbyte codP2 = codigoCS(p2,ii,sd);


        //CASOS TRIVIALES
        if ((codP1==0)&&(codP2==0)){   //Está dentro
                control = true;  //NO BORRAR
        }else{
                if (((codP1)&(codP2))!=0){   //Está fuera
                        control = false; //BORRAR
        //CASO RECURSIVO
                }else{
                        Punto* pFuera;
                        Punto* pAux;
                        GLbyte codFuera;
                        if(codP1!=0){//P1 está fuera de alguna frontera?
                                pFuera = p1;
                                pAux = p2;
                                codFuera = codP1;

                        }else{  //si no
                                if(codP2!=0){//P2 está fuera de alguna frontera?
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

//-------------------------------------------------

 bool Linea::estaPuntoVertices(Punto* punto)
 {
        bool encontrado = false;
        if  ((punto->getX()+5>=origen->getX())&&(punto->getX()-5<=origen->getX())){
                if((punto->getY()+5>=origen->getY())&&(punto->getY()-5<=origen->getY())){
                        encontrado = true;
                }
        }

        if (!encontrado){
                        if((punto->getX()+5>=destino->getX())&&(punto->getX()-5<=destino->getX())){

                                if((punto->getY()+5>=destino->getY())&&(punto->getY()-5<=destino->getY())){
                                        encontrado = true;
                                }
                }
        }

        return encontrado;
 }

//-------------------------------------------------

 bool Linea::estaPuntoIzq(Punto* punto)
 {
        bool estaIzq = false;
        GLfloat Ox = getOrigen()->getX();
        GLfloat Oy = getOrigen()->getY();
        GLfloat Dx = getDestino()->getX();
        GLfloat Dy = getDestino()->getY();
        GLfloat Px = punto->getX();
        GLfloat Py = punto->getY();

        GLfloat test = ((Dy-Oy)*(Ox-Px)) - ((Dx-Ox)*(Oy-Py));

        //Si es negativo, está a la derecha
        if (test >=0){
                estaIzq = true;
        }

        return estaIzq;
 }

//-------------------------------------------------

 void Linea::girar(Punto* centro, float ang)
 {
        origen->rotaP(centro,ang);
        destino->rotaP(centro,ang);
 }



//-------------------------------------------------

 GLbyte Linea::codigoCS(Punto* punto, Punto* ii, Punto* sd)
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

//-------------------------------------------------

 void Linea::recortarDer(Punto*& p1, Punto* p2, Punto* sd)
 //P1 fuera de la región derecha
 {
        float d = (p1->getX() - sd->getX())*((p1->getY()-p2->getY())/(p1->getX()-p2->getX()));
        p1->setX(sd->getX());
        p1->setY(p1->getY()-d);
 }

//-------------------------------------------------

 void Linea::recortarIzq(Punto*& p1, Punto* p2, Punto* ii)
 //P1 fuera de la región izquierda
 {
        float d = (p1->getX() - ii->getX())*((p1->getY()-p2->getY())/(p1->getX()-p2->getX()));
        p1->setX(ii->getX());
        p1->setY(p1->getY()-d);
 }

//-------------------------------------------------

 void Linea::recortarSup(Punto*& p1, Punto* p2, Punto* sd)
 //P1 fuera de la región superior
 {
        float d = (p1->getY() - sd->getY())*((p1->getX()-p2->getX())/(p1->getY()-p2->getY()));
        p1->setX(p1->getX()-d);
        p1->setY(sd->getY());
 }

//-------------------------------------------------

 void Linea::recortarInf(Punto*& p1, Punto* p2, Punto* ii)
 //P1 fuera de la región inferior
 {
        float d = (p1->getY() - ii->getY())*((p1->getX()-p2->getX())/(p1->getY()-p2->getY()));
        p1->setX(p1->getX()-d);
        p1->setY(ii->getY());
 }

//-------------------------------------------------

 void Linea::mover(Punto* desplazamiento)
 {
        origen->sumar(desplazamiento);
        destino->sumar(desplazamiento);
 }

//-------------------------------------------------

 void Linea::buscarInfIzqYSupDer(Punto*& a,Punto*& b)
 {
        //Comprobamos coordenadas del origen
        if(origen->getX()<a->getX()){
                a->setX(origen->getX());
        }

        if(origen->getY()<a->getY()){
                a->setY(origen->getY());
        }

        if(origen->getX()>b->getX()){
                b->setX(origen->getX());
        }

        if(origen->getY()>b->getY()){
                b->setY(origen->getY());
        }

        //Comprobamos coordenadas del destino
        if(destino->getX()<a->getX()){
                a->setX(origen->getX());
        }

        if(destino->getY()<a->getY()){
                a->setY(origen->getY());
        }

        if(destino->getX()>b->getX()){
                b->setX(origen->getX());
        }

        if(destino->getY()>b->getY()){
                b->setY(origen->getY());
        }
 }

//---------------------------------------------------------------------------

 #pragma package(smart_init)


