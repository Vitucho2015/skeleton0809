//---------------------------------------------------------------------------

 #ifndef tObstaculoRecubiertoH
 #define tObstaculoRecubiertoH
 #include "tConvexo.h"
 #include "tSegmento.h"
 #include "tObstaculo.h"

  class tObstaculoRecubierto: public tObstaculo
  {
        private:
				tObstaculo*	interior; //Obstaculo que se va a dibujar
				tConvexo*	corteza; //Obstaculo invisible que sirve para la colision
                PuntoV2F** calculaArco(PuntoV2F* centro,double angIni, double angArco, double radio, int nLados);
                double tObstaculoRecubierto::calculoAngulo(PuntoV2F* A, PuntoV2F* B);
                int nLados;// se usa para los arcos, es el numero de puntos
        public:
                tObstaculoRecubierto();
                tObstaculoRecubierto(PuntoV2F* centro,int nVertices,int lado, double radio);
                tObstaculoRecubierto(int nVertices,PuntoV2F** vertices,int tipo, double radio);
                ~tObstaculoRecubierto();
                void draw();
                bool colisionVsPelota(tPelota* pelota, double& tIn, PuntoV2F*& normal);
 };

//---------------------------------------------------------------------------

 #endif
