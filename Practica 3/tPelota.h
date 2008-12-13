//---------------------------------------------------------------------------

 #ifndef tPelotaH
 #define tPelotaH
 #include <gl\gl.h>     //Librería OPENGL
 #include <gl\glu.h>
 #include "Lista.h"
 #include "PuntoV2F.h"

 class tPelota
 {
        private:
                PuntoV2F* posicion;
                Lista<PuntoV2F>* circulo;
                PuntoV2F* sentido;
                double radio;

        public:
                tPelota();
                tPelota(double r, PuntoV2F* pos, PuntoV2F* paso);
                ~tPelota();
                void avanza();
                void draw();
                void avanzaYRebota(double tIn, PuntoV2F* normal);
                double getRadio();
                PuntoV2F* getSentido();
                PuntoV2F* getPosicion();
                void setSentido(PuntoV2F* s);
 };

//---------------------------------------------------------------------------

 #endif
