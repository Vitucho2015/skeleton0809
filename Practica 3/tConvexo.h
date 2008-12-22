//---------------------------------------------------------------------------

 #ifndef tConvexoH
 #define tConvexoH
 #include "tObstaculo.h"

  class tConvexo:public tObstaculo
  {
        private:

        public:
                tConvexo();
                tConvexo(PuntoV2F* centro,int nVertices,int lado);
                tConvexo(int nVertices,PuntoV2F** vertices);
                ~tConvexo();
                void draw();
                bool colisionVsPelota(tPelota* pelota, double& tIn, PuntoV2F*& normal);
 };

//---------------------------------------------------------------------------

 #endif
