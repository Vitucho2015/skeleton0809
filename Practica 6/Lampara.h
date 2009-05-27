//---------------------------------------------------------------------------

#ifndef LamparaH
#define LamparaH

#include "Cilindro.h"
#include "ObjetoCompuesto3D.h"

//---------------------------------------------------------------------------

class Lampara : public ObjetoCompuesto3D{

    private:

    public:
       Lampara(GLfloat nRadioBase,GLfloat nRadioCima,GLfloat nAltura,GLint nNPlados, GLint nNQCapas);
       ~Lampara();
       void dibujar();

};

//---------------------------------------------------------------------------

#endif


 