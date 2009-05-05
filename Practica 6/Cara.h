//---------------------------------------------------------------------------

#ifndef CaraH
#define CaraH

#include "VerticeNormal.h"

//---------------------------------------------------------------------------

class Cara {

    private:
        VerticeNormal** tabla;
        int numVertices;

    public:
        Cara();
        Cara(int numV, int n[], int numNormal);
        ~Cara();
        int getIndiceVertice(int n);
        int getIndiceNormal(int n);
        int getNumVertices();

};

//---------------------------------------------------------------------------

#endif


