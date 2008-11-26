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
        float xRight,xLeft,yTop,yBot;
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
        void inserta(DibujoLineas *dibujo);
        void seleccion(float x,float y);
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
