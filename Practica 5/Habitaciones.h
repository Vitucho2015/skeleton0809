//---------------------------------------------------------------------------

#ifndef HabitacionesH
#define HabitacionesH
#include "ObjetoCompuesto3D.h"
#include "Muebles.h"
#include "Cilindro.h"
#include "Tablero.h"
//#include "Estanteria.h"
//#include "Silla.h"
//#include "Puerta.h"

//---------------------------------------------------------------------------

class Habitacion : public ObjetoCompuesto3D {
     private:
         int nHabitacion;

     public:
        Habitacion(int h);
        ~Habitacion();
        void dibujar();
};

#endif

//---------------------------------------------------------------------------
