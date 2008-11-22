//---------------------------------------------------------------------------

 #ifndef PuntoV2FH
 #define PuntoV2FH
 #include <math.h>      //Librería funciones matemáticas
 #include <fstream>     //Ficheros
 using namespace std;

 class PuntoV2F
 {
        private:
                float x;        //Valor de la coordenada X
                float y;        //Valor de la coordenada Y
        public:
                PuntoV2F();    //Constructores
                PuntoV2F(float coorX, float coorY);
                PuntoV2F(PuntoV2F*& p);
                PuntoV2F(PuntoV2F* p1, PuntoV2F* p2);
                ~PuntoV2F();   //Destructor

                //Accesores y mutadores
                float getX();
                void setX(float coorY);
                float getY();
                void setY(float coorY);

                //Operaciones
                void rotaP(PuntoV2F* centroRot, float ang);
                void restar(PuntoV2F* pv);
                void sumar(PuntoV2F* pv);
                void escalar(float valor);
                void normalizar();
                float longitud();
                float productoEscalar(PuntoV2F* v);
                void normalIzq(PuntoV2F *v);
 };

//---------------------------------------------------------------------------

 #endif
