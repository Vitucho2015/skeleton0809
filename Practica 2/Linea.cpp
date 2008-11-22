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

 Linea::Linea(PuntoV2F* puntoOrigen, PuntoV2F* puntoDestino)
 {
        origen = puntoOrigen;
        destino = puntoDestino;
 }

//-------------------------------------------------

 Linea::Linea(Linea* linea)
 {
        origen = new PuntoV2F(linea->origen);
        destino = new PuntoV2F(linea->destino);
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

 void Linea::setOrigen(PuntoV2F* punto)
 {
        if (origen != NULL){
                delete origen;
        }
        origen = punto;
 }

//-------------------------------------------------

 PuntoV2F* Linea::getOrigen()
 {
        return origen;
 }

//-------------------------------------------------

 void Linea::setDestino(PuntoV2F* punto)
 {
        if (destino != NULL){
                delete destino;
        }
        destino = punto;
 }

//-------------------------------------------------

 PuntoV2F* Linea::getDestino()
 {
        return destino;
 }

//-------------------------------------------------

 void Linea::draw()
 {
        PuntoV2F* o = new PuntoV2F(origen);
        PuntoV2F* d = new PuntoV2F(destino);
        Lapiz* lapiz = new Lapiz(o, 0);
        lapiz->lineTo(d);
        delete lapiz;
 }

//-------------------------------------------------

 bool Linea::recorte(PuntoV2F* ii, PuntoV2F* sd)
 {
        return CS(origen,destino,ii,sd);
 }

//-------------------------------------------------

 bool Linea::CS(PuntoV2F* p1, PuntoV2F* p2, PuntoV2F* ii, PuntoV2F* sd)
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
                        PuntoV2F* pFuera;
                        PuntoV2F* pAux;
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

 bool Linea::estaPuntoV2FVertices(PuntoV2F* punto)
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

 bool Linea::estaPuntoV2FIzq(PuntoV2F* punto)
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

 void Linea::girar(PuntoV2F* centro, float ang)
 {
        origen->rotaP(centro,ang);
        destino->rotaP(centro,ang);
 }



//-------------------------------------------------

 GLbyte Linea::codigoCS(PuntoV2F* punto, PuntoV2F* ii, PuntoV2F* sd)
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

 void Linea::recortarDer(PuntoV2F*& p1, PuntoV2F* p2, PuntoV2F* sd)
 //P1 fuera de la región derecha
 {
        float d = (p1->getX() - sd->getX())*((p1->getY()-p2->getY())/(p1->getX()-p2->getX()));
        p1->setX(sd->getX());
        p1->setY(p1->getY()-d);
 }

//-------------------------------------------------

 void Linea::recortarIzq(PuntoV2F*& p1, PuntoV2F* p2, PuntoV2F* ii)
 //P1 fuera de la región izquierda
 {
        float d = (p1->getX() - ii->getX())*((p1->getY()-p2->getY())/(p1->getX()-p2->getX()));
        p1->setX(ii->getX());
        p1->setY(p1->getY()-d);
 }

//-------------------------------------------------

 void Linea::recortarSup(PuntoV2F*& p1, PuntoV2F* p2, PuntoV2F* sd)
 //P1 fuera de la región superior
 {
        float d = (p1->getY() - sd->getY())*((p1->getX()-p2->getX())/(p1->getY()-p2->getY()));
        p1->setX(p1->getX()-d);
        p1->setY(sd->getY());
 }

//-------------------------------------------------

 void Linea::recortarInf(PuntoV2F*& p1, PuntoV2F* p2, PuntoV2F* ii)
 //P1 fuera de la región inferior
 {
        float d = (p1->getY() - ii->getY())*((p1->getX()-p2->getX())/(p1->getY()-p2->getY()));
        p1->setX(p1->getX()-d);
        p1->setY(ii->getY());
 }

//-------------------------------------------------

 void Linea::mover(PuntoV2F* desplazamiento)
 {
        origen->sumar(desplazamiento);
        destino->sumar(desplazamiento);
 }

//-------------------------------------------------

 void Linea::buscarInfIzqYSupDer(PuntoV2F*& a,PuntoV2F*& b)
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

void Linea::dibujaCortado()
{
   glColor3f(0,1,0);
   glBegin(GL_LINES);
      glVertex2f(origen->getX(),origen->getY());
      glVertex2f(destino->getX(),destino->getY());
   glEnd();
}

//---------------------------------------------------------------------------

 #pragma package(smart_init)


