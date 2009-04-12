//---------------------------------------------------------------------------

#ifndef TAfinH
#define TAfinH
#include "PV3D.h"

//---------------------------------------------------------------------------

class TAfin {

     private:
          double matriz[16];

     public:
          TAfin();
          void trasladar(PV3D* vector);
          void rotar(GLdouble angulo,PV3D* vector);
          void escalar(PV3D* escalacion);
          GLdouble* getMatriz();
};

//---------------------------------------------------------------------------

#endif


 