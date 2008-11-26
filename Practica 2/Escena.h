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
        double xRight,xLeft,yTop,yBot;
        double wLeft,wRight,wBot,wTop;

    public:
        Escena();
        ~Escena();
        void poliEspiral(PuntoV2F *posInicial,double incrAng,double angInicial,double incrLong,double longInicial,int nPasos);
        void dibuja();
        double damexRight(){return xRight;};
        double damexLeft(){return xLeft;};
        double dameyTop(){return yTop;};
        double dameyBot(){return yBot;};
        void setXRight(double a){xRight=a;};
        void setXLeft(double a){xLeft=a;};
        void setYTop(double a){yTop=a;};
        void setYBot(double a){yBot=a;};
        void inserta(DibujoLineas *dibujo);
        void seleccion(double x,double y);
        void borraDibujo(DibujoLineas *d);
        void enMarca(PuntoV2F* p,PuntoV2F* l);
        bool vacio(){return dibujos->vacia();};
        void borraCortado();
        bool recorte(PuntoV2F *a,PuntoV2F *b);
        bool hayCortado(){return cortado!=NULL;};
        Lista<DibujoLineas>* getDibujos();
        //Borrarlo ya que solo sirver para probar los fractales
        DibujoLineas* damePrueba();
};
//---------------------------------------------------------------------------
#endif
