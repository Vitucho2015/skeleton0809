//---------------------------------------------------------------------------

#ifndef TableroH
#define TableroH
#include <gl\gl.h>
#include <gl\glu.h>
#include "Malla.h"

//---------------------------------------------------------------------------

class Tablero : public Malla {

     private:
          GLfloat largo, ancho, grueso;
          int divLargo, divAncho, divGrueso;

     public:
        Tablero(GLfloat l, GLfloat a, GLfloat g, int divL, int divA, int divG);
};

#endif

//---------------------------------------------------------------------------
