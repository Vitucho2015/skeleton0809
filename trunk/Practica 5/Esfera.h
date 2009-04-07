//---------------------------------------------------------------------------

#ifndef EsferaH
#define EsferaH
#include "ObjetoCuadrico.h"

//---------------------------------------------------------------------------

class Esfera : public ObjetoCuadrico {

    private:
        GLUquadricObj* esfera;
        GLfloat radio;
        GLint Meridianos;
        GLint Paralelos;

    public:
        Esfera(GLfloat radio,GLint nMeridianos, GLint nParalelos);
        ~Esfera();
        void dibujar();
};

#endif

//---------------------------------------------------------------------------
 