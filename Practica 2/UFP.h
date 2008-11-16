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

//---------------------------------------------------------------------------
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

private:	// User declarations
 HDC hdc;
 HGLRC hrc;
 //definen el tamaño del volumen de vista
 GLfloat xLeft,xRight,yTop,yBot;
 //guarda el radio del puerto de vista
 GLfloat RatioViewPort;

 //Variables

 bool mDesplazar; //indica si estamos en el modo Desplazar



 // métodos privados
 void __fastcall SetPixelFormatDescriptor();
 void __fastcall GLScene();

 public:		// User declarations
   __fastcall TGLForm2D(TComponent* Owner);

   void procesarCoor(int X, int Y);
};
//---------------------------------------------------------------------------
extern PACKAGE TGLForm2D *GLForm2D;
//---------------------------------------------------------------------------
#endif
