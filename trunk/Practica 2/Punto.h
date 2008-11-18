//---------------------------------------------------------------------------

 #ifndef PuntoH
 #define PuntoH
 #include <math.h>      //Librería funciones matemáticas
 #include <fstream>     //Ficheros
 using namespace std;

 class Punto
 {
        private:
                float x;        //Valor de la coordenada X
                float y;        //Valor de la coordenada Y
        public:
                Punto();    //Constructores
                Punto(float coorX, float coorY);
                Punto(Punto*& p);
                ~Punto();   //Destructor

                //Accesores y mutadores
                float getX();
                void setX(float coorY);
                float getY();
                void setY(float coorY);

                //Operaciones
                void rotaP(Punto* centroRot, float ang);
                void restar(Punto* pv);
                void sumar(Punto* pv);
                void escalar(float valor);
                void normalizar();
                float productoEscalar(Punto* v);
 };

//---------------------------------------------------------------------------

 #endif
