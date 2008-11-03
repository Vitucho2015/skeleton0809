//---------------------------------------------------------------------------

#ifndef UFPH
#define UFPH
//---------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <ComCtrls.hpp>
#include <Buttons.hpp>
#include <Dialogs.hpp>

#include <gl\gl.h>
#include <gl\glu.h>

//---------------------------------------------------------------------------
class listaVertices {
public:
int x;
int y;
};

class TGLForm2D : public TForm
{
__published:	// IDE-managed Components
        TMainMenu *MainMenu1;
        TMenuItem *Anidar1;
        TMenuItem *Acercar1;
        TMenuItem *Alejar1;
        TMenuItem *Trasladar1;
        TMenuItem *Centrar1;
        TMenuItem *Tilling1;
    TMenuItem *Opcional1;
    TMenuItem *ColorAnidamiento1;
    TMenuItem *ElegirColores1;
    TMenuItem *AnidamientoTotal1;
        TColorDialog *ColorDialog1;
        TMenuItem *Tamaolnea1;
        TMenuItem *Tamaopunto1;
        TMenuItem *N1punto1;
        TMenuItem *N2puntos1;
        TMenuItem *N3puntos1;
        TMenuItem *N4puntos1;
        TMenuItem *N2puntos2;
        TMenuItem *N4puntos2;
        TMenuItem *N6puntos1;
        TMenuItem *N8puntos1;
  void __fastcall FormCreate(TObject *Sender);
  void __fastcall FormResize(TObject *Sender);
  void __fastcall FormPaint(TObject *Sender);
  void __fastcall FormDestroy(TObject *Sender);
    void __fastcall Tilling1Click(TObject *Sender);
    void __fastcall Acercar1Click(TObject *Sender);
    void __fastcall Alejar1Click(TObject *Sender);
    void __fastcall Trasladar1Click(TObject *Sender);
    void __fastcall Centrar1Click(TObject *Sender);
    void __fastcall Anidar1Click(TObject *Sender);
    void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift);
        void __fastcall AnidamientoTotal1Click(TObject *Sender);
        void __fastcall ColorAnidamiento1Click(TObject *Sender);
        void __fastcall ElegirColores1Click(TObject *Sender);
        void __fastcall N1punto1Click(TObject *Sender);
        void __fastcall N2puntos1Click(TObject *Sender);
        void __fastcall N3puntos1Click(TObject *Sender);
        void __fastcall N4puntos1Click(TObject *Sender);
        void __fastcall N2puntos2Click(TObject *Sender);
        void __fastcall N4puntos2Click(TObject *Sender);
        void __fastcall N6puntos1Click(TObject *Sender);
        void __fastcall N8puntos1Click(TObject *Sender);

private:	// User declarations
 HDC hdc;
 HGLRC hrc;
 //definen el tamaño del volumen de vista
 GLfloat xLeft,xRight,yTop,yBot;
 //guarda el radio del puerto de vista
 GLfloat RatioViewPort;
 // métodos privados
 void __fastcall SetPixelFormatDescriptor();
 void __fastcall GLScene();
 //Variables globales
    int nTriangulos;   //Número de triángulos
    bool mEmbaldosado; //Indica si está en modo embaldosado
    bool anidamientoTotal; //indica si hay que anidar todo o no
    bool oscurecer;
    bool mDesplazar;   //Indica si está en modo desplazar
    int nCol;          //Número de columnas para el embaldosado
    int nFil;          //Número de filas para el embaldosado
    GLint x1,x2,x3,y1,y2,y3;    //Coordenadas de los vértices del último triangulo
                                //dibujado
    float color1, color2, color3;
    float R, G, B;
    int tampunto,tamlinea;



 //Funciones
    void dibujarMotivo();
    void pintarConBaldosas();
    void pintarSinBaldosas();
    void zoom(int porcentaje);  
    void calculaMedias();
    void calculaMedios()   ;
    void dibujaTriangulo(int i);

 public:		// User declarations
   __fastcall TGLForm2D(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TGLForm2D *GLForm2D;
//---------------------------------------------------------------------------
#endif
