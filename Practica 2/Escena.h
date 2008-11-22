//---------------------------------------------------------------------------

#ifndef EscenaH
#define EscenaH
#include "DibujoLineas.h"
#include "Lapiz.h"

//---------------------------------------------------------------------------

class Escena{

    private:
        Lista<DibujoLineas>* dibujos; //guarda los dibujos de la escena
        DibujoLineas* cortado;
        DibujoLineas* poliLineas;
        float xRight,xLeft,yTop,yBot;
        bool modificada;
        String *nombre;
        float wLeft,wRight,wBot,wTop;

    public:
        Escena();
        ~Escena();
        void poliEspiral(PuntoV2F *posInicial,float incrAng,float angInicial,float incrLong,float longInicial,int nPasos);
        void dibuja();
        float damexRight(){return xRight;};
        float damexLeft(){return xLeft;};
        float dameyTop(){return yTop;};
        float dameyBot(){return yBot;};
        void setXRight(float a){xRight=a;};
        void setXLeft(float a){xLeft=a;};
        void setYTop(float a){yTop=a;};
        void setYBot(float a){yBot=a;};
        void lineas(PuntoV2F *ant,PuntoV2F *sig);
        void inserta(DibujoLineas *dibujo); // ver si este sobra
        void insertaPoliLinea();
        DibujoLineas* seleccion(float x,float y);
        void borraDibujo(DibujoLineas *d);
        void dameCentro(PuntoV2F* p1,PuntoV2F*p2,PuntoV2F*p3,GLdouble& x,GLdouble& y);
        bool dameAngulos(PuntoV2F* centro,PuntoV2F* p1,PuntoV2F* p2,GLdouble& ang,GLdouble& angIni);
        void enMarca(PuntoV2F* p,PuntoV2F* l);  //Ver para que vale
        bool vacio(){return dibujos->vacia();};
        bool vacioPoli(){return poliLineas->vacia();};
        void borraCortado();
        void recorte();
        bool hayCortado(){return cortado!=NULL;};
};
//---------------------------------------------------------------------------
#endif
