//---------------------------------------------------------------------------

 #ifndef LapizH
 #define LapizH
 #include "PuntoV2F.h"       //Para el tipo PuntoV2F
 #include <math.h>      //Librería funciones matemáticas
 #include <gl\gl.h>     //Librería OPENGL
 #include <gl\glu.h>

 class Lapiz
 {
        private:
                PuntoV2F* posicion;     //PuntoV2F donde se encuentra el lapiz
                double direccion;        //Dirección (ángulo en grados): 0º a 359º
        public:
                Lapiz();    //Constructores
                Lapiz(PuntoV2F* pos);
                Lapiz(PuntoV2F* pos, double dir);
                ~Lapiz();   //Destructor
                //Accesores y mutadores
                PuntoV2F* getPosicion();
                void lineTo(PuntoV2F* punto);
                void moveTo(PuntoV2F* punto);
                void moveToRel(double incrX, double incrY);
                void turn(double dir);
                void turnTo(double dir);
                void avanzar(double distancia, bool traza);
 };

//---------------------------------------------------------------------------

 #endif
