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
        int numVertices, numNormales, numCaras, lados, vertLado;
        PV3D** vertices;
        PV3D** normales;
        Cara** caras;

    //métodos
    public:
        Malla();
        Malla(int numV, int numC);
        virtual ~Malla();
        virtual void dibujar();
        void dibujaNormales();
        void Newell();
        void defineMalla();
};

#endif

//---------------------------------------------------------------------------
