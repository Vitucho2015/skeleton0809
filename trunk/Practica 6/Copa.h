//---------------------------------------------------------------------------

#ifndef CopaH
#define CopaH

#include "ObjetoCompuesto3D.h"
#include "MallaPorRevolucion.h"

//---------------------------------------------------------------------------

class Copa : public ObjetoCompuesto3D{

    public:
        Copa(PV3D** perfil,int numPuntos, int numLados, int nCaras);
        ~Copa();
        void dibujar();
        void setColor(Color* c);
};

//---------------------------------------------------------------------------

#endif

