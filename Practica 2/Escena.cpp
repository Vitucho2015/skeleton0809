//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Escena.h"

//---------------------------------------------------------------------------

Escena::Escena()
{
    dibujos=new Lista<DibujoLineas>();
    cortado=NULL;
    poliLineas=new DibujoLineas();
    xRight=200;
    xLeft=-xRight;
    yTop=xRight;
    yBot=-yTop;
    modificada=false;
    nombre = new String("Escena");
}
//---------------------------------------------------------------------------
Escena::~Escena()
{
    if(dibujos != NULL){
        delete dibujos;
        dibujos = NULL;
        delete nombre;
        nombre = NULL;
    }
    if(poliLineas != NULL){
        delete poliLineas;
        poliLineas = NULL;
    }
    if(cortado != NULL){
        delete cortado;
        cortado = NULL;
    }
}
//---------------------------------------------------------------------------
void Escena::poliEspiral(PuntoV2F *posInicial,float incrAng,float angInicial,float incrLong,float longInicial,int nPasos)
{
  Lapiz *l=new Lapiz(posInicial,angInicial);
  DibujoLineas *nuevoDibujo= new DibujoLineas();
  PuntoV2F *posAct=new PuntoV2F(posInicial);
  for (int i=0;i<nPasos;i++){
        l->avanzar(longInicial,true);
        longInicial+=incrLong;
        l->turn(incrAng);
        Linea *nuevaLinea=new Linea(posAct,l->getPosicion());
        nuevoDibujo->insertaLinea(nuevaLinea);
        delete posAct;
        posAct=new PuntoV2F(l->getPosicion());
  }
  dibujos->inserta(nuevoDibujo);
  delete l;
  l=NULL;
  delete posAct;
  posAct=NULL;
}
//---------------------------------------------------------------------------
void Escena::dibuja()
{
  DibujoLineas *aux;
  if(dibujos!=NULL && dibujos->getLongitud()>0){
      dibujos->inicia();
      for(int i=0;i<dibujos->getLongitud();i++){
            aux=dibujos->getActual();
            aux->draw();
            dibujos->avanza();
      }
  }
  if(poliLineas!=NULL){
    poliLineas->draw();
  }
  if(cortado!=NULL){
    cortado->dibujaCortado();
  }
}
//---------------------------------------------------------------------------
void Escena::lineas(PuntoV2F *ant,PuntoV2F *sig)
{
  Linea *nuevaLinea=new Linea(ant,sig);
  if(poliLineas==NULL){
    poliLineas=new DibujoLineas();
  }
  poliLineas->insertaLinea(nuevaLinea);
}
//---------------------------------------------------------------------------
void Escena::inserta(DibujoLineas *dibujo)
{
  dibujos->inserta(dibujo);
}
//---------------------------------------------------------------------------
void Escena::insertaPoliLinea()
{
  dibujos->inserta(poliLineas);
  poliLineas=NULL;
}
//---------------------------------------------------------------------------
DibujoLineas* Escena::seleccion(float x,float y)
{
  DibujoLineas *selecto=NULL;
  bool encontrado=false;
  dibujos->inicia();
  DibujoLineas *actual;
  PuntoV2F* punto = new PuntoV2F(x,y);
  for(int i=0;i<dibujos->getLongitud();i++){
     actual=dibujos->getActual();
     actual->setSeleccionado(false);
     if(!encontrado){
        encontrado=actual->seleccionar(punto);
        if(encontrado) {
                actual->setSeleccionado(true);
                selecto=actual;
        }
     }
     dibujos->avanza();
  }
  delete punto;
  punto = NULL;
  return selecto;
}
//---------------------------------------------------------------------------
void Escena::borraDibujo(DibujoLineas *d)
{
   int i=0;
   bool encontrado=false;
   dibujos->inicia();
   DibujoLineas *aux;
   while(i<dibujos->getLongitud() && !encontrado){
      aux=dibujos->getActual();
      if(aux!=d) {
         dibujos->avanza();
         i++;
      }
      else{
         dibujos->eliminaActual();
         encontrado=true;
         for(int j=i;j<dibujos->getLongitud();j++){
            dibujos->avanza();
         }
      }
   }
}
//---------------------------------------------------------------------------
bool Escena::dameAngulos(PuntoV2F* centro,PuntoV2F* p1,PuntoV2F* p2,GLdouble& ang,GLdouble& angIni)
{
  GLfloat a,b,c;
  PuntoV2F* aux=new PuntoV2F(centro);
  PuntoV2F* AY,AY1;
  PuntoV2F* s;
  PuntoV2F* v;
  PuntoV2F* u;
  aux->setX(p2->getX());    //misma X que p2 y misma Y que centro
  AY = new PuntoV2F(aux,p2);
  v = new PuntoV2F(centro,p2);
  GLdouble alfa=asin(AY->longitud()/v->longitud());
  if(p2->getX()<centro->getX())
    alfa=M_PI-alfa;
  delete v;
  v=NULL;
  delete AY;
  AY=NULL;
  aux->setX(p1->getX());
  AY=new PuntoV2F(aux,p1);
  v=new PuntoV2F(centro,p1);
  GLdouble beta=asin(AY->longitud()/v->longitud());
  delete AY;
  AY=NULL;
  delete aux;
  aux=NULL;
  delete v;
  v=NULL;

  if(p2->getY() > centro->getY()){
    if(p1->getY() >= centro->getY()){
      s=new PuntoV2F(p1,p2);
      v=new PuntoV2F(centro,p1);
      u=new PuntoV2F(centro,p2);
      a=s->longitud();
      b=v->longitud();
      c=u->longitud();
      angIni=alfa;
      ang=acos((-pow(a,2) + pow(b,2) + pow(c,2))/(2*b*c));
      delete s;
      s=NULL;
      delete v;
      v=NULL;
      delete u;
      u=NULL;
      return true;
     }
     else{//p1.y<c.y
          angIni=alfa;
          ang=M_PI-angIni+beta;
          return true;
     }//else

  }else if(p1->getY()>=centro->getY()){
          angIni=M_PI-beta;
          ang=M_PI-alfa+beta;
          return false;
         }
         else{
             angIni=M_PI+beta;
             s=new PuntoV2F(p1,p2);
             v=new PuntoV2F(centro,p1);
             u=new PuntoV2F(centro,p2);
             a=s->longitud();
             b=v->longitud();
             c=u->longitud();
             ang=acos((-pow(a,2) + pow(b,2) + pow(c,2))/(2*b*c));
             delete s;
             s=NULL;
             delete v;
             v=NULL;
             delete u;
             u=NULL;
             return false;
           }

  }
//---------------------------------------------------------------------------
void Escena::dameCentro(PuntoV2F* p1,PuntoV2F*p2,PuntoV2F*p3,GLdouble& x,GLdouble& y)
{

 PuntoV2F* v=new PuntoV2F(p1,p3);
 PuntoV2F* u=new PuntoV2F(p3,p2);

 PuntoV2F* a=new PuntoV2F((p1->getX()+p3->getX())/2.0,(p1->getY()+p3->getY())/2.0);
 PuntoV2F* b=new PuntoV2F((p3->getX()+p2->getX())/2.0,(p3->getY()+p2->getY())/2.0);

 PuntoV2F* va=new PuntoV2F();
 va->normalIzq(v);

 PuntoV2F* vb=new PuntoV2F();
 vb->normalIzq(u);

 PuntoV2F* BA=new PuntoV2F(b,a);

 float k2=BA->productoEscalar(v)/vb->productoEscalar(v);

 x=b->getX()+k2*vb->getX();
 y=b->getY()+k2*vb->getY();
 delete u;
 u=NULL;
 delete v;
 v=NULL;
 delete a;
 a=NULL;
 delete b;
 b=NULL;
 delete va;
 va=NULL;
 delete vb;
 vb=NULL;
 delete BA;
 BA=NULL;
}
//---------------------------------------------------------------------------
void Escena::enMarca(PuntoV2F* p1,PuntoV2F* p2)
{                    //origen      destino
 wLeft=p1->getX();
 wRight=p2->getX();
 wTop=p1->getY();
 wBot=p2->getY();
 if(cortado!=NULL){
    delete cortado;
 }
 cortado=new DibujoLineas();
 Linea* lin;
 PuntoV2F* aux=new PuntoV2F(p2->getX(),p1->getY());
 PuntoV2F* aux2=new PuntoV2F(p1->getX(),p2->getY());
 lin=new Linea(p1,aux);
 cortado->insertaLinea(lin);
 lin=new Linea(aux,p2);
 cortado->insertaLinea(lin);
 lin=new Linea(aux2,p2);
 cortado->insertaLinea(lin);
 lin=new Linea(p1,aux2);
 cortado->insertaLinea(lin);
 dibuja();
 delete aux;
 aux=NULL;
 delete aux2;
 aux2=NULL;
}
//---------------------------------------------------------------------------
void Escena::borraCortado()
{
 if(cortado != NULL){
    delete cortado;
    cortado=NULL;
 }
}
//---------------------------------------------------------------------------
void Escena::recorte()
{
  dibujos->inicia();
  for(int i=0;i<dibujos->getLongitud();i++){
     DibujoLineas* d=dibujos->getActual();
     //d->recorte(wLeft,wRight,wTop,wBot);
     if(d->vacia()){
       dibujos->eliminaActual();
     }
     dibujos->avanza();
  }
}
//---------------------------------------------------------------------------
#pragma package(smart_init)

