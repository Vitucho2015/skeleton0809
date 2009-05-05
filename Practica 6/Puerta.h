//---------------------------------------------------------------------------

#ifndef PuertaH
#define PuertaH

#include "ObjetoCompuesto3D.h"
#include "Tablero.h"
#include "Esfera.h"

//---------------------------------------------------------------------------

class Puerta: public ObjetoCompuesto3D{

    private:
        bool abierta;
        int numPaso;
    public:
        Puerta(GLfloat l, GLfloat a, GLfloat g, int divL, int divA, int divG, bool estado, int num);
        ~Puerta();
        void dibujar();
        bool cambiaPuerta();
};

//---------------------------------------------------------------------------

#endif


