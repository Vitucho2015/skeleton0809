//---------------------------------------------------------------------------

#ifndef SueloH
#define SueloH
#include <gl\gl.h>
#include <gl\glu.h>
#include "Malla.h"

//---------------------------------------------------------------------------

class Suelo : public Malla {

     private:
          GLfloat largo, ancho, grueso;
          int divLargo, divAncho, divGrueso;
          bool lado;

     public:
        Suelo(GLfloat l, GLfloat a, GLfloat g, int divL, int divA, int divG,bool b);
        ~Suelo();
        float getAncho(){return ancho;}
        bool getLado(){return lado;}
};

//---------------------------------------------------------------------------

#endif




 