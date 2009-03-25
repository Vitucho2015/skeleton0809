//---------------------------------------------------------------------------

#ifndef ObjetoCompuesto3DH
#define ObjetoCompuesto3DH
#include "Objeto3D.h"
//---------------------------------------------------------------------------

class ObjetoCompuesto3D : public Objeto3D {

     protected:
          int numObjetos;
          Objeto3D** objetos;
     public:
};

#endif

//---------------------------------------------------------------------------
