//---------------------------------------------------------------------------

#ifndef MallaH
#define MallaH
#include "PV3D.h"
#include "Cara.h"
#include <gl\gl.h>
#include <gl\glu.h>
#include "Objeto3D.h"

//---------------------------------------------------------------------------

class Malla: public Objeto3D {

    //atributos
    protected:
        int numVertices, numNormales, numCaras;
        PV3D** vertices;
        PV3D** normales;
        Cara** caras;

    //métodos
    public:
        Malla();
        Malla(int nVertices, PV3D** v, int nNormales, PV3D** n, int nCaras, Cara** c);
        virtual ~Malla();
        virtual void dibuja();
        void Newell();
        void dibujaNormales();

};
//---------------------------------------------------------------------------
#endif
