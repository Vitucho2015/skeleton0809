//---------------------------------------------------------------------------

#ifndef EscenaH
#define EscenaH
#include "Habitaciones.h"

//---------------------------------------------------------------------------

class Escena : public ObjetoCompuesto3D{

    private:
        
    public:
        Escena();
        ~Escena();
        void dibujar();
        void cambiaTV(int numHabitacion);
        bool cambiaPuerta(int numHabitacion);
        void escalar(PV3D* v,int n);
        void rotar(PV3D* v,int grados,int n);
        void trasladar(PV3D* v,int n);
};

//---------------------------------------------------------------------------

#endif


