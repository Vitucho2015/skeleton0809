//---------------------------------------------------------------------------

#ifndef MallaPorSplineYRevolucionH
#define MallaPorSplineYRevolucionH
#include "Malla.h"

//---------------------------------------------------------------------------

class MallaPorSplineYRevolucion : public Malla {

  public:
      MallaPorSplineYRevolucion(PV3D** perfil, int numPuntos, int numLados, int nCaras);
      ~MallaPorSplineYRevolucion();
};

//---------------------------------------------------------------------------

#endif


