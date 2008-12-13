//---------------------------------------------------------------------------

 #ifndef tCirculoH
 #define tCirculoH
 #include "tObstaculo.h"

  class tCirculo:public tObstaculo
  {
        private:
                double radio;
                PuntoV2F* centro;
        public:
                tCirculo();
                tCirculo(double r, PuntoV2F* c);
                ~tCirculo();
                PuntoV2F* getCentro();
                double getRadio();
                void rotar(PuntoV2F* c, double angulo);
                void draw();
                bool colisionVsPelota(tPelota* pelota, double& tIn, PuntoV2F*& normal);
 };

//---------------------------------------------------------------------------

 #endif
