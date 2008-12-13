//---------------------------------------------------------------------------

 #include <vcl.h>
 #pragma hdrstop
 #include "PuntoV2F.h"
 #include <math.h>

//---------------------------------------------------------------------------

 PuntoV2F::PuntoV2F()
 {
        x = 0;
        y = 0;
 }

 
//-------------------------------------------------

 PuntoV2F::PuntoV2F(double coorX, double coorY)
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
    x=(double)p2->getX()-(double)p1->getX();
    y=(double)p2->getY()-(double)p1->getY();
 }
//-------------------------------------------------

 PuntoV2F::~PuntoV2F()
 {
 }

//-------------------------------------------------

 double PuntoV2F::getX()
 {
        return x;
 }

//-------------------------------------------------

 void PuntoV2F::setX(double coorX)
 {
        x = coorX;
 }

//-------------------------------------------------

 double PuntoV2F::getY()
 {
        return y;
 }

//-------------------------------------------------

 void PuntoV2F::setY(double coorY)
 {
        y = coorY;
 }

//-------------------------------------------------

 void PuntoV2F::rotaP(PuntoV2F* centroRot, double ang)
 {
        double cx= centroRot->getX();
        double cy= centroRot->getY();
        double dx=(1.0-cos(ang))*cx + sin(ang)*cy;
        double dy=-sin(ang)*cx + (1.0-cos(ang))*cy;
        double x1= x*cos(ang)-y*sin(ang)+dx;
        double y1= x*sin(ang)+y*cos(ang)+dy;
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

 void PuntoV2F::escalar(double valor)
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

 double PuntoV2F::productoEscalar(PuntoV2F* v)
 {
        double valor;
        valor = x*v->x + y*v->y;
        return valor;
 }

//-------------------------------------------------

 double PuntoV2F::modulo()
 {
        double valor;
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
void PuntoV2F::dibuja(){
    glPointSize(3);
    glColor3f(1,0,1);
    glBegin(GL_POINTS);
        glVertex2f(x,y);
    glEnd();
}

//---------------------------------------------------------------------------

 #pragma package(smart_init)
