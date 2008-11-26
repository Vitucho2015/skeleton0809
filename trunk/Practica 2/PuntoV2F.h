//---------------------------------------------------------------------------

 #ifndef PuntoV2FH
 #define PuntoV2FH
 #include <math.h>      //Librería funciones matemáticas
 #include <gl\gl.h>
 #include <gl\glu.h>
 using namespace std;

 class PuntoV2F
 {
        private:
                double x;        //Valor de la coordenada X
                double y;        //Valor de la coordenada Y
        public:
                PuntoV2F();    //Constructores
                PuntoV2F(double coorX, double coorY);
                PuntoV2F(PuntoV2F*& p);
                PuntoV2F(PuntoV2F* p1, PuntoV2F* p2);
                ~PuntoV2F();   //Destructor

                //Accesores y mutadores
                double getX();
                void setX(double coorY);
                double getY();
                void setY(double coorY);

                //Operaciones
                void rotaP(PuntoV2F* centroRot, double ang);
                void restar(PuntoV2F* pv);
                void sumar(PuntoV2F* pv);
                void escalar(double valor);
                void normalizar();
                double longitud();
                double productoEscalar(PuntoV2F* v);
                void normalIzq(PuntoV2F *v);
                void dibuja();
 };

//---------------------------------------------------------------------------

 #endif
