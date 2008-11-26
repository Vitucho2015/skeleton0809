//---------------------------------------------------------------------------

 #ifndef DibujoLineasH
 #define DibujoLineasH
 #include "Linea.h"
 #include "Lista.h"

 class DibujoLineas
 {
        private:
                Lista<Linea>* segmentos;      //Lista con lineas (segmentos)
                bool seleccionado;             //Indica si está seleccionado

        public:
                DibujoLineas();
                DibujoLineas(DibujoLineas* dL);
                //Para crear espirales
                DibujoLineas(PuntoV2F* p, int numIteraciones,int longIni,int incrLado,int incrAng);
                //Para crear poligonos regulares
                DibujoLineas(PuntoV2F* c,int nlados,int lado);
                ~DibujoLineas();
                void insertaLinea(Linea* linea);
                void draw();
                bool recorte(PuntoV2F* puntoA, PuntoV2F* puntoB);
                void recorte(float wLeft,float wRight,float wTop,float wBot);
                bool seleccionar(PuntoV2F* punto);
                bool getSeleccionado();
                void setSeleccionado(bool selec);
                bool estaPuntoV2FDentro(PuntoV2F* punto);
                Lista<Linea>* getSegmentos();
                void girarConCentro(PuntoV2F* centro, float ang);
                void mover(PuntoV2F* desplazamiento);
                bool vacia();
                void dibujaCortado();
 };

//---------------------------------------------------------------------------

 #endif
