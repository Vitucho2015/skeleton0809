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
        void cambiaTV(int numHabitacion);
        bool cambiaPuerta(int numHabitacion);
};

//---------------------------------------------------------------------------

#endif

