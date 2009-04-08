//---------------------------------------------------------------------------

#ifndef EscenaH
#define EscenaH
#include "Habitaciones.h"

//---------------------------------------------------------------------------

class Escena {

    private:
        Habitacion *habitacion1;
        Habitacion *habitacion2;

    public:
        Escena();
        ~Escena();
        void dibujar();
        void setTVEncendida(bool estado, int numHabitacion);
};

#endif

//---------------------------------------------------------------------------
