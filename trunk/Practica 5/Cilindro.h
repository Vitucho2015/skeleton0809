//---------------------------------------------------------------------------

#ifndef CilindroH
#define CilindroH
#include "ObjetoCuadrico.h"

//---------------------------------------------------------------------------

class Cilindro : public ObjetoCuadrico{

    private:
        GLUquadricObj* cilindro;
        GLfloat radioBase;
        GLfloat radioCima;
        GLfloat altura;
        GLint nLados;
        GLint nCapas;
   public:
       Cilindro(GLfloat nRadioBase,GLfloat nRadioCima,GLfloat nAltura,GLint nNPlados, GLint nNQCapas);
       ~Cilindro();
       void dibujar();

};

#endif

//---------------------------------------------------------------------------
 