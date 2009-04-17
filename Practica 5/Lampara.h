//---------------------------------------------------------------------------

#ifndef LamparaH
#define LamparaH

#include "ObjetoCuadrico.h"

//---------------------------------------------------------------------------

class Lampara : public ObjetoCuadrico{

    private:
        GLUquadricObj* Lampara;
        GLfloat radioBase;
        GLfloat radioCima;
        GLfloat altura;
        GLint nLados;
        GLint nCapas;
   public:
       Lampara(GLfloat nRadioBase,GLfloat nRadioCima,GLfloat nAltura,GLint nNPlados, GLint nNQCapas);
       ~Lampara();
       void dibujar();

};

//---------------------------------------------------------------------------

#endif


 