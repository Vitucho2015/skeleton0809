//---------------------------------------------------------------------------

 #ifndef LapizH
 #define LapizH
 #include "PuntoV2F.h"       //Para el tipo PuntoV2F
 #include <math.h>      //Librer�a funciones matem�ticas
 #include <gl\gl.h>     //Librer�a OPENGL
 #include <gl\glu.h>

 class Lapiz
 {
        private:
                PuntoV2F* posicion;     //PuntoV2F donde se encuentra el lapiz
                float direccion;        //Direcci�n (�ngulo en grados): 0� a 359�
        public:
                Lapiz();    //Constructores
                Lapiz(PuntoV2F* pos);
                Lapiz(PuntoV2F* pos, float dir);
                ~Lapiz();   //Destructor
                //Accesores y mutadores
                PuntoV2F* getPosicion();
                void lineTo(PuntoV2F* punto);
                void moveTo(PuntoV2F* punto);
                void moveToRel(float incrX, float incrY);
                void turn(float dir);
                void turnTo(float dir);
                void avanzar(float distancia, bool traza);
 };

//---------------------------------------------------------------------------

 #endif
