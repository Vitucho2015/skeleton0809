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
                DibujoLineas(Punto* p, int numIteraciones,int longIni,int incrLado,int incrAng);
                //Para crear poligonos regulares
                DibujoLineas(Punto* c,int nlados,int lado);
                //Para crear arcos
                DibujoLineas(Punto* centro,float angIni, float angArco, float radio, int nLados);
                ~DibujoLineas();
                void insertaLinea(Linea* linea);
                void draw();
                bool recorte(Punto* puntoA, Punto* puntoB);
                bool seleccionar(Punto* punto);
                bool getSeleccionado();
                void setSeleccionado(bool selec);
                bool estaPuntoDentro(Punto* punto);
                Lista<Linea>* getSegmentos();
                void girarConCentro(Punto* centro, float ang);
                void mover(Punto* desplazamiento);
                void buscarInfIzqYSupDer(Punto*& sd,Punto*& ii);
 };

//---------------------------------------------------------------------------

 #endif
