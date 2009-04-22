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


     public:
        Suelo(GLfloat l, GLfloat a, GLfloat g, int divL, int divA, int divG);
        ~Suelo();
        float getAncho(){return ancho;}
};

//---------------------------------------------------------------------------

#endif




 