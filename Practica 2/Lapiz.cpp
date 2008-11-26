//---------------------------------------------------------------------------

 #include <vcl.h>
 #pragma hdrstop
 #include "Lapiz.h"

//---------------------------------------------------------------------------

 Lapiz::Lapiz()
 {
        PuntoV2F* punto = new PuntoV2F();
        posicion = punto;
        direccion = 0;
 }

//-------------------------------------------------

 Lapiz::Lapiz(PuntoV2F* pos)
 {
        posicion = pos;
        direccion = 0;
 }

//-------------------------------------------------

 Lapiz::Lapiz(PuntoV2F* pos, double dir)
 {
        posicion = pos;
        direccion = dir;
 }

//-------------------------------------------------

 Lapiz::~Lapiz()
 {
        if (posicion!=NULL)
        {
                delete posicion;
        }
 }

//-------------------------------------------------

 PuntoV2F* Lapiz::getPosicion()
 {
        return posicion;
 }

//-------------------------------------------------

 void Lapiz::lineTo(PuntoV2F* punto)
 {
        glBegin(GL_LINES);
                glVertex2f(posicion->getX(),posicion->getY());
                glVertex2f(punto->getX(),punto->getY());
        glEnd();
        delete posicion;
        posicion = punto;
 }

//-------------------------------------------------

 void Lapiz::moveTo(PuntoV2F* punto)
 {
        delete posicion;
        posicion = punto;
 }

//-------------------------------------------------

 void Lapiz::moveToRel(double incrX, double incrY)
 {
        posicion->setX(posicion->getX()+incrX);
        posicion->setY(posicion->getY()+incrY);
 }

//-------------------------------------------------

 void Lapiz::turn(double dir)
 {
        direccion = direccion + dir;
        while (direccion>=360){
                direccion = direccion - 360;
        }
 }

//-------------------------------------------------

 void Lapiz::turnTo(double dir)
 {
        direccion = dir;
 }

//-------------------------------------------------

 void Lapiz::avanzar(double distancia, bool traza)
 {
        //Operamos en radiones
        double incrX = distancia * cos((direccion*3.1415926535)/180.0);
        double incrY = distancia * sin((direccion*3.1415926535)/180.0);
        PuntoV2F* punto = new PuntoV2F(posicion->getX()+incrX,
                posicion->getY()+incrY);

        if (traza){
                lineTo(punto);
        }else{
                moveTo(punto);
        }
 }

//---------------------------------------------------------------------------

 #pragma package(smart_init)
