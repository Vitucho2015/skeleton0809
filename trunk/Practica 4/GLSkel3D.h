//---------------------------------------------------------------------------
#ifndef GLSkel3DH
#define GLSkel3DH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <gl\gl.h>
#include <gl\glu.h>
#include "Espiral.h"

//---------------------------------------------------------------------------
class TGLForm3D : public TForm
{
__published:	// IDE-managed Components
   TMainMenu *MainMenu1;
   TMenuItem *Version1;
   TMenuItem *Parte11;
   TMenuItem *Parte21;
   TMenuItem *Parte31;
    TMenuItem *Modo1;
    TMenuItem *Lineas1;
    TMenuItem *Relleno1;
    void __fastcall FormResize(TObject *Sender);
    void __fastcall FormPaint(TObject *Sender);
    void __fastcall FormDestroy(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall FormKeyDown(TObject *Sender, WORD &Key,TShiftState Shift);
   void __fastcall Parte11Click(TObject *Sender);
   void __fastcall Parte21Click(TObject *Sender);
   void __fastcall Parte31Click(TObject *Sender);
    void __fastcall Lineas1Click(TObject *Sender);
    void __fastcall Relleno1Click(TObject *Sender);


private:        // User declarations
    HDC hdc;
    HGLRC hrc;
    GLfloat eyeX,eyeY,eyeZ, lookX,lookY,lookZ, upX,upY,upZ; // Cámara
    GLdouble RatioViewPort, xLeft,xRight, yBot,yTop, N,F;  // Volumen de vista
    GLfloat PosicionLuz0[4];  // luz0
    void __fastcall SetPixelFormatDescriptor();
    void __fastcall GLScene();
    void crearObjetosEscena();
    void liberarObjetosEscena();

    int version;// sirve para saber que version tiene que pintar
    int modo;//indica como tiene que pintar los objetos
    GLUquadricObj* bola;
    Espiral* trayectoria;//por donde va a ir la bola
    Malla* copa;// malla que tiene definida una copa
    //Tecla Q pulsada
    bool qPulsada;
    //Tecla W pulsada
    bool wPulsada;
    //Tiempo
    double tiempo;
    //Angulo giro paneles
    double giroPanel;
    double giro;
    PV3D* origenCoor;
    void pintaEjes();
    void pintaEsfera();
    void crearMallaTrayectoria(PV3D* origenCoor, int nLados, int nCapas, double radio, Espiral*& malla);
    void crearMallaCopa(PV3D* origenCoor,int nP,int nQ,double radio, Malla*& malla);
public:		// User declarations
    __fastcall TGLForm3D(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TGLForm3D *GLForm3D;
//---------------------------------------------------------------------------
#endif
