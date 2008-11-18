//---------------------------------------------------------------------------

 #ifndef LapizH
 #define LapizH
 #include "Punto.h"       //Para el tipo Punto
 #include <math.h>      //Librería funciones matemáticas
 #include <gl\gl.h>     //Librería OPENGL
 #include <gl\glu.h>

 class Lapiz
 {
        private:
                Punto* posicion;     //Punto donde se encuentra el lapiz
                float direccion;        //Dirección (ángulo en grados): 0º a 359º
        public:
                Lapiz();    //Constructores
                Lapiz(Punto* pos);
                Lapiz(Punto* pos, float dir);
                ~Lapiz();   //Destructor
                //Accesores y mutadores
                Punto* getPosicion();
                void lineTo(Punto* punto);
                void moveTo(Punto* punto);
                void moveToRel(float incrX, float incrY);
                void turn(float dir);
                void turnTo(float dir);
                void avanzar(float distancia, bool traza);
 };

//---------------------------------------------------------------------------

 #endif
