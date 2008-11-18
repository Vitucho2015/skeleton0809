//---------------------------------------------------------------------------

 #include <vcl.h>
 #pragma hdrstop
 #include "Lapiz.h"

//---------------------------------------------------------------------------

 Lapiz::Lapiz()
 {
        Punto* punto = new Punto();
        posicion = punto;
        direccion = 0;
 }

//-------------------------------------------------

 Lapiz::Lapiz(Punto* pos)
 {
        posicion = pos;
        direccion = 0;
 }

//-------------------------------------------------

 Lapiz::Lapiz(Punto* pos, float dir)
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

 Punto* Lapiz::getPosicion()
 {
        return posicion;
 }

//-------------------------------------------------

 void Lapiz::lineTo(Punto* punto)
 {
        glBegin(GL_LINES);
                glVertex2f(posicion->getX(),posicion->getY());
                glVertex2f(punto->getX(),punto->getY());
        glEnd();
        delete posicion;
        posicion = punto;
 }

//-------------------------------------------------

 void Lapiz::moveTo(Punto* punto)
 {
        delete posicion;
        posicion = punto;
 }

//-------------------------------------------------

 void Lapiz::moveToRel(float incrX, float incrY)
 {
        posicion->setX(posicion->getX()+incrX);
        posicion->setY(posicion->getY()+incrY);
 }

//-------------------------------------------------

 void Lapiz::turn(float dir)
 {
        direccion = direccion + dir;
        while (direccion>=360){
                direccion = direccion - 360;
        }
 }

//-------------------------------------------------

 void Lapiz::turnTo(float dir)
 {
        direccion = dir;
 }

//-------------------------------------------------

 void Lapiz::avanzar(float distancia, bool traza)
 {
        //Operamos en radiones
        float incrX = distancia * cos((direccion*3.141592)/180);
        float incrY = distancia * sin((direccion*3.141592)/180);
        Punto* punto = new Punto(posicion->getX()+incrX,
                posicion->getY()+incrY);

        if (traza){
                lineTo(punto);
        }else{
                moveTo(punto);
        }
 }

//---------------------------------------------------------------------------

 #pragma package(smart_init)
