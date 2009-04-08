//---------------------------------------------------------------------------

#ifndef PuertaH
#define PuertaH

#include "ObjetoCompuesto3D.h"
#include "Tablero.h"
#include "Esfera.h"

//---------------------------------------------------------------------------

class Puerta: public ObjetoCompuesto3D{

    private:

    public:
        Puerta(GLfloat l, GLfloat a, GLfloat g, int divL, int divA, int divG);
        ~Puerta();
        void dibujar();
};

#endif

//---------------------------------------------------------------------------
