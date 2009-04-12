//---------------------------------------------------------------------------

#ifndef EstanteriaH
#define EstanteriaH
#include "ObjetoCompuesto3D.h"
#include "Tablero.h"

//---------------------------------------------------------------------------

class Estanteria : public ObjetoCompuesto3D {

  public:
    Estanteria(int numLibros, GLfloat a, int divA, int divL);
    void dibujar();
    ~Estanteria();
};

//---------------------------------------------------------------------------

#endif


