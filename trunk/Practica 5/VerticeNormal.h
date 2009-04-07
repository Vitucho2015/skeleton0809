//---------------------------------------------------------------------------

#ifndef VerticeNormalH
#define VerticeNormalH
#include <gl\gl.h>
#include <gl\glu.h>

//---------------------------------------------------------------------------

class VerticeNormal{
    private:
        int vertice;
        int normal;

    public:
        VerticeNormal();
        VerticeNormal(int v, int n);
        ~VerticeNormal();
        int getVertice();
        int getNormal();
};

#endif

//---------------------------------------------------------------------------
