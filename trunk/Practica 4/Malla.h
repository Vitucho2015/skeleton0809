//---------------------------------------------------------------------------

#ifndef MallaH
#define MallaH
#include "PV3D.h"
#include "Cara.h"
#include <gl\gl.h>
#include <gl\glu.h>
//---------------------------------------------------------------------------

class Malla {

    //atributos
    private:
        int numVertices, numNormales, numCaras;
        PV3D** vertices;
        PV3D** normales;
        Cara** caras;

    //métodos
    public:
        Malla();
        ~Malla();
        void dibuja();
};

#endif
