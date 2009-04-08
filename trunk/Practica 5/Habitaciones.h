//---------------------------------------------------------------------------

#ifndef HabitacionesH
#define HabitacionesH
#include <typeinfo>
#include "ObjetoCompuesto3D.h"
#include "Muebles.h"
#include "Cilindro.h"
#include "Tablero.h"
#include "Television.h"
#include "Puerta.h"
//#include "Estanteria.h"
//#include "Silla.h"


//---------------------------------------------------------------------------

class Habitacion : public ObjetoCompuesto3D {
     private:
         int nHabitacion;

     public:
        Habitacion(int h);
        ~Habitacion();
        void dibujar();
        void setTVEncendida(bool estado);
};

#endif

//---------------------------------------------------------------------------
