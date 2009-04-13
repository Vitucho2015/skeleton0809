//---------------------------------------------------------------------------

#ifndef MueblesH
#define MueblesH
#include "ObjetoCompuesto3D.h"
#include "Mesa.h"
#include "Cilindro.h"
/*#include "Silla.h"
#include "MallaPorSplineYRevolucion.h"
#include "Toro.h"
#include "Disco.h"
*/
//---------------------------------------------------------------------------

class Muebles : ObjetoCompuesto3D {
     private:
          /*Mesa* mesa;
          Silla *silla1, *silla2;
          MallaPorSplineYRevolucion *botella, *copa;
          Toro* donut;
          Disco* plato;
           */
     public:
        Muebles();
        ~Muebles();
        void dibujar();
};

//---------------------------------------------------------------------------

#endif


 