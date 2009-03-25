//---------------------------------------------------------------------------

#ifndef HabitacionesH
#define HabitacionesH
#include "ObjetoCompuesto3D.h"
#include "Tablero.h"

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
