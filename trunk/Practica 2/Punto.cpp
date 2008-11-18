//---------------------------------------------------------------------------

 #include <vcl.h>
 #pragma hdrstop
 #include "Punto.h"
 #include<math.h>

//---------------------------------------------------------------------------

 Punto::Punto()
 {
        x = 0;
        y = 0;
 }

 
//-------------------------------------------------

 Punto::Punto(float coorX, float coorY)
 {
        x = coorX;
        y = coorY;
 }

//-------------------------------------------------

 Punto::Punto(Punto*& p)
 {
        x = p->getX();
        y = p->getY();
 }

//-------------------------------------------------

 Punto::~Punto()
 {
 }

//-------------------------------------------------

 float Punto::getX()
 {
        return x;
 }

//-------------------------------------------------

 void Punto::setX(float coorX)
 {
        x = coorX;
 }

//-------------------------------------------------

 float Punto::getY()
 {
        return y;
 }

//-------------------------------------------------

 void Punto::setY(float coorY)
 {
        y = coorY;
 }

//-------------------------------------------------

 void Punto::rotaP(Punto* centroRot, float ang)
 {
        float cx= centroRot->getX();
        float cy= centroRot->getY();
        float dx=(1.0-cos(ang))*cx + sin(ang)*cy;
        float dy=-sin(ang)*cx + (1.0-cos(ang))*cy;
        float x1= x*cos(ang)-y*sin(ang)+dx;
        float y1= x*sin(ang)+y*cos(ang)+dy;
        x=x1;
        y=y1;
 }

//-------------------------------------------------

 void Punto::restar(Punto* pv)
 {
        x = x - pv->x;
        y = y - pv->y;
 }

//-------------------------------------------------

 void Punto::sumar(Punto* pv)
 {
        x = x + pv->x;
        y = y + pv->y;
 }

//-------------------------------------------------

 void Punto::escalar(float valor)
 {
        x = x*valor;
        y = y*valor;
 }

//-------------------------------------------------

 void Punto::normalizar()
 {
        x = x / sqrt((x*x)+(y*y));
        y = y / sqrt((x*x)+(y*y));
 }

//-------------------------------------------------

 float Punto::productoEscalar(Punto* v)
 {
        float valor;
        valor = x*v->x + y*v->y;
        return valor;
 }



//---------------------------------------------------------------------------

 #pragma package(smart_init)
