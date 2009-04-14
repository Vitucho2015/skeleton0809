//---------------------------------------------------------------------------

#ifndef SofaH
#define SofaH

#include "ObjetoCompuesto3D.h"
#include "Tablero.h"
#include "Cilindro.h"

//---------------------------------------------------------------------------

class Sofa : public ObjetoCompuesto3D {

    public:
        Sofa();
        void dibujar();
        ~Sofa();
};

//---------------------------------------------------------------------------

#endif
 