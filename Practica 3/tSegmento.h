//---------------------------------------------------------------------------

#ifndef tSegmentoH
#define tSegmentoH   
#include "tObstaculo.h"

class tSegmento:public tObstaculo
  {
        private:

                //Funciones de implementación interna del recorte
                bool CS(PuntoV2F* p1, PuntoV2F* p2, PuntoV2F* ii, PuntoV2F* sd);
                GLbyte codigoCS(PuntoV2F* punto, PuntoV2F* ii, PuntoV2F* sd);
                void recortarDer(PuntoV2F*& p1, PuntoV2F* p2, PuntoV2F* sd);
                void recortarIzq(PuntoV2F*& p1, PuntoV2F* p2, PuntoV2F* ii);
                void recortarSup(PuntoV2F*& p1, PuntoV2F* p2, PuntoV2F* sd);
                void recortarInf(PuntoV2F*& p1, PuntoV2F* p2, PuntoV2F* ii);

        public:
                tSegmento();
                tSegmento(int nVertices,PuntoV2F** vertices);
                ~tSegmento();
                void draw();
                bool cortaSegmento(PuntoV2F* p1, PuntoV2F* p2, PuntoV2F* p3, PuntoV2F* p4);
                PuntoV2F* inteseccionSegmento(PuntoV2F* p1, PuntoV2F* p2, PuntoV2F* p3, PuntoV2F* p4);

                bool colisionVsPelota(tPelota* pelota, double& tIn, PuntoV2F*& normal);
 };
//---------------------------------------------------------------------------
#endif
