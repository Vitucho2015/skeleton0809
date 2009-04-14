//---------------------------------------------------------------------------

#ifndef MueblesH
#define MueblesH

#include "ObjetoCompuesto3D.h"
#include "Mesa.h"
#include "Cilindro.h"
#include "Toro.h"
#include "Silla.h"
#include "Copa.h"
#include "Sofa.h"

//---------------------------------------------------------------------------

class Muebles : public ObjetoCompuesto3D {
     private:

     public:
        Muebles();
        ~Muebles();
        void dibujar();
};

//---------------------------------------------------------------------------

#endif


 