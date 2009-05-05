//---------------------------------------------------------------------------

#ifndef EsferaH
#define EsferaH
#include "ObjetoCuadrico.h"

//---------------------------------------------------------------------------

class Esfera : public ObjetoCuadrico {

    private:
        GLUquadricObj* esfera;
        GLfloat radio;
        GLint meridianos;
        GLint paralelos;

    public:
        Esfera(GLfloat r,GLint nMeridianos, GLint nParalelos);
        ~Esfera();
        void dibujar();
};

//---------------------------------------------------------------------------

#endif


 