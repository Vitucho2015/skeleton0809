//---------------------------------------------------------------------------

 #include <vcl.h>
 #pragma hdrstop
 #include "Linea.h"
 #include "DibujoLineas.h"
//---------------------------------------------------------------------------

 Linea::Linea()
 {
        origen = NULL;
        destino = NULL;
 }

//---------------------------------------------------------------------------

 Linea::Linea(PuntoV2F* puntoOrigen, PuntoV2F* puntoDestino)
 {
        origen = puntoOrigen;
        destino = puntoDestino;
 }

//---------------------------------------------------------------------------

 Linea::Linea(Linea* linea)
 {
        origen = new PuntoV2F(linea->origen);
        destino = new PuntoV2F(linea->destino);
 }

//---------------------------------------------------------------------------

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

//---------------------------------------------------------------------------

 void Linea::setOrigen(PuntoV2F* punto)
 {
        if (origen != NULL){
                delete origen;
        }
        origen = punto;
 }

//---------------------------------------------------------------------------

 PuntoV2F* Linea::getOrigen()
 {
        return origen;
 }

//---------------------------------------------------------------------------

 void Linea::setDestino(PuntoV2F* punto)
 {
        if (destino != NULL){
                delete destino;
        }
        destino = punto;
 }

//---------------------------------------------------------------------------

 PuntoV2F* Linea::getDestino()
 {
        return destino;
 }

//---------------------------------------------------------------------------

 void Linea::draw()
 {
        PuntoV2F* o = new PuntoV2F(origen);
        PuntoV2F* d = new PuntoV2F(destino);
        Lapiz* lapiz = new Lapiz(o, 0);
        lapiz->lineTo(d);
        delete lapiz;
  }

//---------------------------------------------------------------------------

 bool Linea::recorte(PuntoV2F* ii, PuntoV2F* sd)
 {
        return CS(origen,destino,ii,sd);
 }

//---------------------------------------------------------------------------

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

//---------------------------------------------------------------------------

 bool Linea::estaPuntoV2FVertices(PuntoV2F* punto)
 {
        bool encontrado = false;
        float incr = 5.0;
        float x_punto = punto->getX();
        float y_punto = punto->getY();

        float x_origen = origen->getX();
        float y_origen = origen->getY();

        float x_destino = destino->getX();
        float y_destino = destino->getY();
        
        if  ((x_punto+incr>=x_origen)&&(x_punto-incr<=x_origen)){
            if((y_punto+incr>=y_origen)&&(y_punto-incr<=y_origen)){
                encontrado = true;
            }
        }
        if (!encontrado){
            if((x_punto+incr>=x_destino)&&(x_punto-incr<=x_destino)){
                if((y_punto+incr>=y_destino)&&(y_punto-incr<=y_destino)){
                    encontrado = true;
                }
            }
        }
        return encontrado;
 }

//---------------------------------------------------------------------------

 void Linea::girar(PuntoV2F* centro, float ang)
 {
        origen->rotaP(centro,ang);
        destino->rotaP(centro,ang);
 }

//---------------------------------------------------------------------------

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

//---------------------------------------------------------------------------

 void Linea::recortarDer(PuntoV2F*& p1, PuntoV2F* p2, PuntoV2F* sd)
 //P1 fuera de la región derecha
 {
        float d = (p1->getX() - sd->getX())*((p1->getY()-p2->getY())/(p1->getX()-p2->getX()));
        p1->setX(sd->getX());
        p1->setY(p1->getY()-d);
 }

//---------------------------------------------------------------------------

 void Linea::recortarIzq(PuntoV2F*& p1, PuntoV2F* p2, PuntoV2F* ii)
 //P1 fuera de la región izquierda
 {
        float d = (p1->getX() - ii->getX())*((p1->getY()-p2->getY())/(p1->getX()-p2->getX()));
        p1->setX(ii->getX());
        p1->setY(p1->getY()-d);
 }

//---------------------------------------------------------------------------

 void Linea::recortarSup(PuntoV2F*& p1, PuntoV2F* p2, PuntoV2F* sd)
 //P1 fuera de la región superior
 {
        float d = (p1->getY() - sd->getY())*((p1->getX()-p2->getX())/(p1->getY()-p2->getY()));
        p1->setX(p1->getX()-d);
        p1->setY(sd->getY());
 }

//---------------------------------------------------------------------------

 void Linea::recortarInf(PuntoV2F*& p1, PuntoV2F* p2, PuntoV2F* ii)
 //P1 fuera de la región inferior
 {
        float d = (p1->getY() - ii->getY())*((p1->getX()-p2->getX())/(p1->getY()-p2->getY()));
        p1->setX(p1->getX()-d);
        p1->setY(ii->getY());
 }

//---------------------------------------------------------------------------

 void Linea::mover(PuntoV2F* desplazamiento)
 {
        origen->sumar(desplazamiento);
        destino->sumar(desplazamiento);
 }

//---------------------------------------------------------------------------
void Linea::fractalizaK1(void* & nuevaLista){




          DibujoLineas* dj;

          dj = (DibujoLineas*)nuevaLista;



          float angl = calculoAngulo(getOrigen(),getDestino());




          Lapiz *lz = new Lapiz(getOrigen());

          lz->turnTo(angl);

          float tercio = calculoLongitud() / 3.0;

          PuntoV2F* orig = new PuntoV2F(getOrigen());
          PuntoV2F* dest =new PuntoV2F(getDestino());




          lz->avanzar(tercio,false);
          dest = new PuntoV2F(lz->getPosicion());



          int a= orig->getX();
          int b= orig->getY();
          int c= dest->getX();
          int d= dest->getY();
          Linea * linaux = new Linea(orig,dest);


          dj->insertaLinea(linaux);
          //primera linea de 4 metida




          orig = new PuntoV2F(dest);





          
          lz->turn(60);
          lz->avanzar(tercio,false);
          dest = new PuntoV2F(lz->getPosicion());



          int aa= orig->getX();
          int ba= orig->getY();
          int ca= dest->getX();
          int da= dest->getY();
          linaux = new Linea(orig,dest);

          dj->insertaLinea(linaux);




          orig = new PuntoV2F(dest);




          //segunda linea metida

          lz->turn(240);
          lz->avanzar(tercio,false);
          dest = new PuntoV2F(lz->getPosicion());



          int aaa= orig->getX();
          int baa= orig->getY();
          int caa= dest->getX();
          int daa= dest->getY();
          linaux = new Linea(orig,dest);

          dj->insertaLinea(linaux);

          orig = new PuntoV2F(dest);
          //tercera linea metida

          lz->turn(60);
          lz->avanzar(tercio,false);
          dest = new PuntoV2F(lz->getPosicion());


          int aaaa= orig->getX();
          int baaa= orig->getY();
          int caaa= dest->getX();
          int daaa= dest->getY();
          linaux = new Linea(orig,dest);

          dj->insertaLinea(linaux);



          //int add= dj->getSegmentos()->getLongitud();

          //int adsads= dj->getSegmentos()->getActual()->getOrigen()->getX();

          //dj->getSegmentos()->inicia();

          //int adsdsdads= dj->getSegmentos()->getActual()->getOrigen()->getX();



          //SwapBuffers(hdc);
          //delete lz;
          //delete orig;
          //delete dest;
          //delete linaux;


          //cuarta linea metida


 }

  void Linea::fractalizaK2(void* & nuevaLista){




          DibujoLineas* dj;

          dj = (DibujoLineas*)nuevaLista;



          float angl = calculoAngulo(getOrigen(),getDestino());




          Lapiz *lz = new Lapiz(getOrigen());

          lz->turnTo(angl);

          float cuarto = calculoLongitud() / 4.0;

          PuntoV2F* orig = new PuntoV2F(getOrigen());
          PuntoV2F* dest =new PuntoV2F(getDestino());




          lz->avanzar(cuarto,false);
          dest = new PuntoV2F(lz->getPosicion());



          int a= orig->getX();
          int b= orig->getY();
          int c= dest->getX();
          int d= dest->getY();
          Linea * linaux = new Linea(orig,dest);


          dj->insertaLinea(linaux);
          //primera linea de 4 metida




          orig = new PuntoV2F(dest);





          
          lz->turn(90);
          lz->avanzar(cuarto,false);
          dest = new PuntoV2F(lz->getPosicion());



          int aa= orig->getX();
          int ba= orig->getY();
          int ca= dest->getX();
          int da= dest->getY();
          linaux = new Linea(orig,dest);

          dj->insertaLinea(linaux);




          orig = new PuntoV2F(dest);




          //segunda linea metida

          lz->turn(270);
          lz->avanzar(cuarto,false);
          dest = new PuntoV2F(lz->getPosicion());



          int aaa= orig->getX();
          int baa= orig->getY();
          int caa= dest->getX();
          int daa= dest->getY();
          linaux = new Linea(orig,dest);

          dj->insertaLinea(linaux);

          orig = new PuntoV2F(dest);
          //tercera linea metida

          lz->turn(270);
          lz->avanzar(2*cuarto,false);
          dest = new PuntoV2F(lz->getPosicion());


          int aaaa= orig->getX();
          int baaa= orig->getY();
          int caaa= dest->getX();
          int daaa= dest->getY();
          linaux = new Linea(orig,dest);

          dj->insertaLinea(linaux);

          orig = new PuntoV2F(dest);
          //tercera linea metida

          lz->turn(90);
          lz->avanzar(cuarto,false);
          dest = new PuntoV2F(lz->getPosicion());


          int aa2aa= orig->getX();
          int ba2aa= orig->getY();
          int ca2aa= dest->getX();
          int da2aa= dest->getY();
          linaux = new Linea(orig,dest);

          dj->insertaLinea(linaux);


          orig = new PuntoV2F(dest);
          //tercera linea metida

          lz->turn(90);
          lz->avanzar(cuarto,false);
          dest = new PuntoV2F(lz->getPosicion());


          int aa1aa= orig->getX();
          int ba1aa= orig->getY();
          int ca1aa= dest->getX();
          int da1a= dest->getY();
          linaux = new Linea(orig,dest);

          dj->insertaLinea(linaux);


          orig = new PuntoV2F(dest);
          //tercera linea metida

          lz->turn(270);
          lz->avanzar(cuarto,false);
          dest = new PuntoV2F(lz->getPosicion());


          int aaa4a= orig->getX();
          int baa4a= orig->getY();
          int ca4aa= dest->getX();
          int da4aa= dest->getY();
          linaux = new Linea(orig,dest);

          dj->insertaLinea(linaux);

          //int add= dj->getSegmentos()->getLongitud();

          //int adsads= dj->getSegmentos()->getActual()->getOrigen()->getX();

          //dj->getSegmentos()->inicia();

          //int adsdsdads= dj->getSegmentos()->getActual()->getOrigen()->getX();



          //SwapBuffers(hdc);
          //delete lz;
          //delete orig;
          //delete dest;
          //delete linaux;


          //cuarta linea metida


 }



 void Linea::fractalizaDRAGON(void* & nuevaLista){




          DibujoLineas* dj;

          dj = (DibujoLineas*)nuevaLista;



          float angl = calculoAngulo(getOrigen(),getDestino());




          Lapiz *lz = new Lapiz(getOrigen());

          lz->turnTo(angl);

          float hipp = ((calculoLongitud() / 2.0) / 0.7071067811);

          PuntoV2F* orig = new PuntoV2F(getOrigen());
          PuntoV2F* dest =new PuntoV2F(getDestino());



          lz->turn(45);
          lz->avanzar(hipp,false);
          dest = new PuntoV2F(lz->getPosicion());



          int a= orig->getX();
          int b= orig->getY();
          int c= dest->getX();
          int d= dest->getY();
          Linea * linaux = new Linea(orig,dest);


          dj->insertaLinea(linaux);
          //primera linea de 4 metida




          orig = new PuntoV2F(dest);



          lz->turn(270);
          lz->avanzar(hipp,false);
          dest = new PuntoV2F(lz->getPosicion());



          int a3= orig->getX();
          int b3= orig->getY();
          int c3= dest->getX();
          int d3= dest->getY();
          linaux = new Linea(orig,dest);


          dj->insertaLinea(linaux);
          //primera linea de 4 metida




          orig = new PuntoV2F(dest);




 }

  float Linea::calculoLongitud(){
        float altura = abs(getDestino()->getY() - getOrigen()->getY());
        float anchura = abs(getDestino()->getX() - getOrigen()->getX());

        float longitud = sqrt(pow(altura,2)+pow(anchura,2));
        return longitud;

 }




float Linea::calculoAngulo(PuntoV2F* A, PuntoV2F* B)   {

      float hipo = sqrt(pow(B->getX()-A->getX(),2) + pow(B->getY()-A->getY(),2));

      float altura = B->getY()-A->getY();

      altura = abs (altura);

      float division =   (altura/hipo) ;

      float angulo = asin(division);

      angulo = angulo * ( 180.0 / 3.1415926535 );

      if ( (B->getY()>=A->getY()) && (B->getX()>=A->getX()) ) return angulo;
      else if ((B->getY()<A->getY()) && (B->getX()>=A->getX())) return -angulo;
      else if ((B->getY()<A->getY()) && (B->getX()<A->getX())) return angulo+180;
      else if ((B->getY()>=A->getY()) && (B->getX()<A->getX())) return 180-angulo;

      //Seguro que siempre entre por alguno??
      return angulo;
 }




 
//---------------------------------------------------------------------------

void Linea::dibujaCortado()
{
    glColor3f(0,1,1);
    glBegin(GL_LINES);
        glVertex2f(origen->getX(),origen->getY());
        glVertex2f(destino->getX(),destino->getY());
    glEnd();
    glColor3f(1,1,1);
}

//---------------------------------------------------------------------------

 #pragma package(smart_init)


