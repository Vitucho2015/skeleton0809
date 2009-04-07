//---------------------------------------------------------------------------

#ifndef CamaraH
#define CamaraH
#include "PV3D.h"

//---------------------------------------------------------------------------

class Camara {

  private:
    PV3D* eye, * look, * up, * u, * v, * n;
    void setModelViewMatrix();
    void setView(PV3D* ojo, PV3D* direccion, PV3D* arriba);

  public:
    Camara(PV3D* ojo,PV3D* direccion,PV3D* arriba);
    ~Camara();
    void roll(float angulo);
    void yaw(float angulo);
    void pitch(float angulo);
    void desplazar(GLfloat desU, GLfloat desV, GLfloat desN);
    void ortogonal(GLfloat xLeft,GLfloat xRight,GLfloat yBot,GLfloat yTop,GLfloat N,GLfloat F);
    void perspectiva(GLfloat angulo,GLfloat proporcion,GLfloat N,GLfloat F);
    void cambiaPosicion(PV3D* ojo,PV3D* direccion,PV3D* arriba);
    void Oblicua(GLfloat xLeft,GLfloat xRight,GLfloat yBot,GLfloat yTop,GLfloat N,GLfloat F,PV3D* direccion);
    PV3D* getEye();
    PV3D* getLook();
    PV3D* getUp();
};

#endif

//---------------------------------------------------------------------------
