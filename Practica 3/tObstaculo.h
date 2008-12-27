//---------------------------------------------------------------------------

 #ifndef tObstaculoH
 #define tObstaculoH
 #include <gl\gl.h>     //Librería OPENGL
 #include <gl\glu.h>
 #include "tPelota.h"
 #include "PuntoV2F.h"

 class tObstaculo
 {
        private:
                int numVertices;
                PuntoV2F** vertices;
                PuntoV2F** normales;

        public:
                tObstaculo();
                tObstaculo(int nVertices,PuntoV2F** vVertices);
                virtual ~tObstaculo();
                int getNumVertices();
                void setNumVertices(int num);
                virtual void draw();
                virtual bool colisionVsPelota(tPelota* pelota, double& tIn, PuntoV2F*& normal);
                void setVertices(int nVertices, PuntoV2F** vVertices);
                PuntoV2F* getVertice(int i);
                PuntoV2F* getNormal(int i);

 };

//---------------------------------------------------------------------------

 #endif
 