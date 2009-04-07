//---------------------------------------------------------------------------

#ifndef ObjetoCompuesto3DH
#define ObjetoCompuesto3DH
#include "Objeto3D.h"
#include "Lista.h"

//---------------------------------------------------------------------------

class ObjetoCompuesto3D : public Objeto3D {

     protected:
          Lista<Objeto3D> *objetos;

     public:
};

#endif

//---------------------------------------------------------------------------
 