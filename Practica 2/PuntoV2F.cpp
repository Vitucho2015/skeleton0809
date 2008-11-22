//---------------------------------------------------------------------------

 #include <vcl.h>
 #pragma hdrstop
 #include "PuntoV2F.h"
 #include<math.h>

//---------------------------------------------------------------------------

 PuntoV2F::PuntoV2F()
 {
        x = 0;
        y = 0;
 }

 
//-------------------------------------------------

 PuntoV2F::PuntoV2F(float coorX, float coorY)
 {
        x = coorX;
        y = coorY;
 }

//-------------------------------------------------

 PuntoV2F::PuntoV2F(PuntoV2F*& p)
 {
        x = p->getX();
        y = p->getY();
 }
//-------------------------------------------------
 PuntoV2F::PuntoV2F(PuntoV2F* p1, PuntoV2F* p2)
 {
    x=(float)p2->getX()-(float)p1->getX();
    y=(float)p2->getY()-(float)p1->getY();
 }
//-------------------------------------------------

 PuntoV2F::~PuntoV2F()
 {
 }

//-------------------------------------------------

 float PuntoV2F::getX()
 {
        return x;
 }

//-------------------------------------------------

 void PuntoV2F::setX(float coorX)
 {
        x = coorX;
 }

//-------------------------------------------------

 float PuntoV2F::getY()
 {
        return y;
 }

//-------------------------------------------------

 void PuntoV2F::setY(float coorY)
 {
        y = coorY;
 }

//-------------------------------------------------

 void PuntoV2F::rotaP(PuntoV2F* centroRot, float ang)
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

 void PuntoV2F::restar(PuntoV2F* pv)
 {
        x = x - pv->x;
        y = y - pv->y;
 }

//-------------------------------------------------

 void PuntoV2F::sumar(PuntoV2F* pv)
 {
        x = x + pv->x;
        y = y + pv->y;
 }

//-------------------------------------------------

 void PuntoV2F::escalar(float valor)
 {
        x = x*valor;
        y = y*valor;
 }

//-------------------------------------------------

 void PuntoV2F::normalizar()
 {
        x = x / sqrt((x*x)+(y*y));
        y = y / sqrt((x*x)+(y*y));
 }

//-------------------------------------------------

 float PuntoV2F::productoEscalar(PuntoV2F* v)
 {
        float valor;
        valor = x*v->x + y*v->y;
        return valor;
 }

//-------------------------------------------------

 float PuntoV2F::longitud()
 {
        float valor;
        valor = (sqrt(pow(x,2)+pow(y,2)));
        return valor;
 }
//-------------------------------------------------
void PuntoV2F::normalIzq(PuntoV2F *v)
{
    x=-v->getY();
    y=v->getX();
}
//---------------------------------------------------------------------------

 #pragma package(smart_init)
