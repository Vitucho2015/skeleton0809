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
#include "Estanteria.h"
#include "Lampara.h"


//---------------------------------------------------------------------------

class Habitacion : public ObjetoCompuesto3D {
     private:
         int nHabitacion;

     public:
        Habitacion(int h);
        ~Habitacion();
        void dibujar();
        void cambiaTV();
        bool cambiaPuerta();
        void escalar(PV3D* v,int n);
        void rotar(PV3D* v,int grados,int n);
        void trasladar(PV3D* v,int n);
};

//---------------------------------------------------------------------------

#endif


