//---------------------------------------------------------------------------

#ifndef MallaPorYRevolucionH
#define MallaPorYRevolucionH

#include "Malla.h"

//---------------------------------------------------------------------------

class MallaPorRevolucion : public Malla {

  public:
      MallaPorRevolucion(PV3D** perfil, int numPuntos, int numLados, int nCaras);
      ~MallaPorRevolucion();
};

//---------------------------------------------------------------------------

#endif


