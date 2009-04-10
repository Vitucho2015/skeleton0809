//---------------------------------------------------------------------------

#ifndef MesaH
#define MesaH
#include "ObjetoCompuesto3D.h"
#include "Copa.h"
#include "Tablero.h"

//---------------------------------------------------------------------------

class Mesa : public ObjetoCompuesto3D {

    public:
        Mesa(GLfloat l, GLfloat a, GLfloat g, int divL, int divA, int divG,PV3D** perfil,int numPuntos, int numLados, int nCaras);
        void dibujar();
        ~Mesa();
        void setColor(Color* color);


};

//---------------------------------------------------------------------------

#endif

//---------------------------------------------------------------------------
