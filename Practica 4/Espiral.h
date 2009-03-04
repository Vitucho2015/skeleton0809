//---------------------------------------------------------------------------

#ifndef EspiralH
#define EspiralH
#include "Malla.h"



//---------------------------------------------------------------------------



class Espiral:public Malla
{
        private:
        int numLados;         //Número de lados del polígono
        int numCapas;         //Número de capas del tubo espiral
        double radio;         //Radio del tubo

        public:
        Espiral();    //Constructor
        Espiral(int nVertices, PV3D** v, int nNormales, PV3D** n,
                        int nCaras, Cara** c,int nP, int nQ, double r);
        int getNumLados();
        int getNumCapas();
        double getRadio();
        ~Espiral();   //Destructor

 };


//---------------------------------------------------------------------------
#endif
