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

    //m�todos
    public:
        Malla();
        Malla(int nVertices, PV3D** v, int nNormales, PV3D** n, int nCaras, Cara** c);
        ~Malla();
        void dibuja(int modo);

};
//---------------------------------------------------------------------------
#endif
