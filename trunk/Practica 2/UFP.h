//---------------------------------------------------------------------------

#ifndef UFPH
#define UFPH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>

#include <gl\gl.h>
#include <gl\glu.h>
#include "UFZoom.h"
#include "UFEspiral.h"
#include "UFPoligono.h"
#include "Escena.h"

//---------------------------------------------------------------------------
typedef enum {linea,poligono,espiral,trasladar,seleccion,cortar,nada} tEstado;
class TGLForm2D : public TForm
{
__published:	// IDE-managed Components
    TMainMenu *MainMenu1;
    TMenuItem *Dibujar1;
    TMenuItem *Lineas1;
    TMenuItem *Poligono1;
    TMenuItem *Espiral1;
    TMenuItem *Editar1;
    TMenuItem *Seleccionar1;
    TMenuItem *Borrar1;
    TMenuItem *Explorar1;
    TMenuItem *Zoom1;
    TMenuItem *Traslacion1;
    TMenuItem *Fractales1;
    TMenuItem *K1;
    TMenuItem *Koch21;
    TMenuItem *Dragon1;
    TMenuItem *Cortar1;
    TMenuItem *Opcional1;
  void __fastcall FormCreate(TObject *Sender);
  void __fastcall FormResize(TObject *Sender);
  void __fastcall FormPaint(TObject *Sender);
  void __fastcall FormDestroy(TObject *Sender);
    void __fastcall Lineas1Click(TObject *Sender);

    void __fastcall Poligono1Click(TObject *Sender);
    void __fastcall Espiral1Click(TObject *Sender);
    void __fastcall Seleccionar1Click(TObject *Sender);
    void __fastcall Borrar1Click(TObject *Sender);
    void __fastcall Zoom1Click(TObject *Sender);
    void __fastcall Traslacion1Click(TObject *Sender);
    void __fastcall K1Click(TObject *Sender);
    void __fastcall Koch21Click(TObject *Sender);
    void __fastcall Dragon1Click(TObject *Sender);
    void __fastcall Cortar1Click(TObject *Sender);
    void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift);
    void __fastcall FormMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
    void __fastcall FormMouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
    void __fastcall FormMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);


private:	// User declarations
 HDC hdc;
 HGLRC hrc;
 //definen el tamaño del volumen de vista
 GLdouble xLeft,xRight,yTop,yBot;
 //guarda el radio del puerto de vista
 GLdouble RatioViewPort;

 //Variables
 Escena* escena;

 tEstado estado;
 int zoom; //Valor del zoom en el zoom progresivo
 int iteraciones; //Numero de iteraciones para el zoom progresivo
 DibujoLineas* selecto; // Para seleccionar y borrar
 int num_iter; //Numero de iteraciones para la espiral
 int lado_ini; //Lado inicial para la espiral
 int incr_lado; //Incremento del lado para la espiral
 int giro; //Angulo de giro para la espiral
 int numLados; // Numero de lados para el poligono
 int longLados; //Longitud del lado para el poligono

 bool esOrigen;
 DibujoLineas* poliLinea;//para pintar poli Lineas
 bool PLCreada;

 PuntoV2F* origen;
 PuntoV2F* origenCorte;
 PuntoV2F* destino;
 PuntoV2F* destinoCorte;
 PuntoV2F* puntoAnt;

 // métodos privados
 void __fastcall SetPixelFormatDescriptor();
 void __fastcall GLScene();
 PuntoV2F* devCoordenada(int x, int y);
 void modoLinea(int X, int Y) ;
 void modoPoligono(int X, int Y);
 void modoEspiral(int X, int Y);
 void modoSeleccion(int X, int Y);
 void fractalizarK1(DibujoLineas* &dibujselec);
 void fractalizarK2(DibujoLineas* &dibujselec);
 void fractalizarDRAGON(DibujoLineas* &dibujselec);
 void desactivarModos();
 public:		// User declarations
   __fastcall TGLForm2D(TComponent* Owner);

};
//---------------------------------------------------------------------------
extern PACKAGE TGLForm2D *GLForm2D;
//---------------------------------------------------------------------------
#endif
