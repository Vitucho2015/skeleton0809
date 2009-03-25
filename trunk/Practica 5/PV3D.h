//---------------------------------------------------------------------------

#ifndef PV3DH
#define PV3DH
#include <gl\gl.h>
#include <gl\glu.h>
#include <math.h>

//---------------------------------------------------------------------------

class PV3D{

    private:
        GLfloat x;
        GLfloat y;
        GLfloat z;
        GLfloat PoV;

    public:
        PV3D(GLfloat coordX, GLfloat coordY, GLfloat coordZ, int valor);
        PV3D(GLfloat coordX, GLfloat coordY, GLfloat coordZ);
        PV3D();
        PV3D(PV3D* punto);
        GLfloat getX();
        GLfloat getY();
        GLfloat getZ();
        int getValor();
        void setPV3D(GLfloat coordX, GLfloat coordY, GLfloat coordZ, int valor);
        void setPV3D(GLfloat coordX, GLfloat coordY, GLfloat coordZ);
        void setX(GLfloat coordX);
        void setY(GLfloat coordY);
        void setZ(GLfloat coordZ);
        void setValor (int valor);
        GLfloat modulo(); //devuelve el módulo de un vector
        GLfloat distancia(PV3D* punto); //devuelve el módulo entre dos puntos
        GLfloat prodEscalar(PV3D* punto);
        PV3D* prodVectorial(PV3D* punto);
        void  normalizar() ;

};

#endif

//---------------------------------------------------------------------------
