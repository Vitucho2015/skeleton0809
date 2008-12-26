//---------------------------------------------------------------------------

 #ifndef tObstaculoRecubiertoH
 #define tObstaculoRecubiertoH
 #include "tConvexo.h"
 #include "tSegmento.h"

  class tObstaculoRecubierto
  {
        private:
				tObstaculo*	interior; //Obstaculo que se va a dibujar
				tConvexo*	corteza; //Obstaculo invisible que sirve para la colision
        public:
                tObstaculoRecubierto();
                tObstaculoRecubierto(PuntoV2F* centro,int nVertices,int lado);
                tObstaculoRecubierto(int nVertices,PuntoV2F** vertices,int tipo);
                ~tObstaculoRecubierto();
                void draw();
                bool colisionVsPelota(tPelota* pelota, double& tIn, PuntoV2F*& normal);
 };

//---------------------------------------------------------------------------

 #endif
