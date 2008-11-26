//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Escena.h"

//---------------------------------------------------------------------------

Escena::Escena()
{
    dibujos = new Lista<DibujoLineas>();
    cortado = NULL;
    xRight=200;
    xLeft=-xRight;
    yTop=xRight;
    yBot=-yTop;
}

//---------------------------------------------------------------------------

Escena::~Escena()
{
    if(dibujos != NULL){
        delete dibujos;
        dibujos = NULL;
    }
    if(cortado != NULL){
        delete cortado;
        cortado = NULL;
    } 
}


Lista<DibujoLineas>* Escena::getDibujos(){
return dibujos;
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
        PuntoV2F* punto = l->getPosicion();
        posAct=new PuntoV2F(punto);
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
  if(cortado != NULL){
    cortado->dibujaCortado();
  }
}

//---------------------------------------------------------------------------

void Escena::inserta(DibujoLineas *dibujo)
{
  dibujos->inserta(dibujo);
}

//---------------------------------------------------------------------------

void Escena::seleccion(float x,float y)
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
  //return selecto;
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

void Escena::enMarca(PuntoV2F* p1,PuntoV2F* p2)
{                    //origen      destino
    wLeft=p1->getX();
    wRight=p2->getX();
    wTop=p1->getY();
    wBot=p2->getY();
    cortado = new DibujoLineas();
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
}

//---------------------------------------------------------------------------

void Escena::borraCortado()
{
    if(cortado != NULL){
        delete cortado;
        cortado = NULL;
    }
}

//---------------------------------------------------------------------------

bool Escena::recorte(PuntoV2F *orig,PuntoV2F *dest)
{
        bool borrado = true;
  dibujos->inicia();
  for(int i=0;i<dibujos->getLongitud();i++){
     DibujoLineas* d=dibujos->getActual();
     if (!d->recorte(orig,dest))

        dibujos->eliminaActual();
     else
     dibujos->avanza();
  }

  if ((dibujos->getLongitud()==0)){
                borrado = false;
        }


  return borrado;
}

//---------------------------------------------------------------------------
DibujoLineas* Escena::damePrueba()
{
dibujos->inicia();
return dibujos->getActual();

}
//---------------------------------------------------------------------------

#pragma package(smart_init)

