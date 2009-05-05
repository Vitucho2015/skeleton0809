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
#include "Suelo.h"


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
        float getAncho();
        void escalarLampara(PV3D* v);
        void escalarMuebles(PV3D* v);
        void trasladarLampara(PV3D* v);
        void trasladarMuebles(PV3D* v);
        void rotarLampara(PV3D* v,int grados);
        void rotarMuebles(PV3D* v,int grados);
};

//---------------------------------------------------------------------------

#endif


