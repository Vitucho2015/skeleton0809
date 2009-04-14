//---------------------------------------------------------------------------

#ifndef SillaH
#define SillaH

#include "ObjetoCompuesto3D.h"
#include "Tablero.h"
#include "Cilindro.h"

//---------------------------------------------------------------------------

class Silla : public ObjetoCompuesto3D {

    public:
        Silla();
        void dibujar();
        ~Silla();
};

//---------------------------------------------------------------------------

#endif
 