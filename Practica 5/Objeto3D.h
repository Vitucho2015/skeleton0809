//---------------------------------------------------------------------------

#ifndef Objeto3DH
#define Objeto3DH
#include "Color.h"
#include "TAfin.h"

//---------------------------------------------------------------------------

class Objeto3D {

     protected:
          TAfin* matriz;
          Color* color;

     public:
        virtual void dibujar(){};
        virtual ~Objeto3D(){};
        virtual void setColor(Color* color);
        virtual void setMatriz(TAfin* m);
        TAfin* getM();
        Color* getColor();

};

#endif

//---------------------------------------------------------------------------
 