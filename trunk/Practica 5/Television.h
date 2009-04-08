//---------------------------------------------------------------------------

#ifndef TelevisionH
#define TelevisionH

#include "ObjetoCompuesto3D.h"
#include "Tablero.h"
//---------------------------------------------------------------------------

class Television : public ObjetoCompuesto3D {
    private:
        bool encendida;
        Tablero* pantalla;
    public:
        Television(GLfloat l, GLfloat a, GLfloat g, int divL, int divA, int divG,bool estado);
        ~Television();
        void dibujar();
        void setEncendida(bool estado);
};

//---------------------------------------------------------------------------
#endif
