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
#include "Camara.h"
#include "Escena.h"
#include "BMPRGB.h"

//---------------------------------------------------------------------------
class TGLForm3D : public TForm
{
__published:	// IDE-managed Components
    TMainMenu *MainMenu1;
  TMenuItem *Camara1;
  TMenuItem *roll1;
  TMenuItem *yaw1;
  TMenuItem *pitch1;
  TMenuItem *desplazar1;
  TMenuItem *esquina1;
  TMenuItem *lateral1;
  TMenuItem *frontal1;
  TMenuItem *cenital1;
  TMenuItem *ortogonal1;
  TMenuItem *perspectiva1;
  TMenuItem *oblicua1;
  TLabel *Label1;
    TMenuItem *Cambiardecmara1;
    TMenuItem *Television1;
    TMenuItem *Encender1;
    TMenuItem *Puerta1;
    TMenuItem *AbrirCerrar1;
    TMenuItem *Luces1;
    TMenuItem *ApagarEncenderLmpara1;
    TMenuItem *ApagarEncederVentana1;
    TMenuItem *ActivarDesactivarNiebla1;
    TMenuItem *ApagarEncenderAmbiente1;
    void __fastcall FormResize(TObject *Sender);
    void __fastcall FormPaint(TObject *Sender);
    void __fastcall FormDestroy(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
  void __fastcall roll1Click(TObject *Sender);
  void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
  void __fastcall yaw1Click(TObject *Sender);
  void __fastcall pitch1Click(TObject *Sender);
  void __fastcall desplazar1Click(TObject *Sender);
  void __fastcall ortogonal1Click(TObject *Sender);
  void __fastcall perspectiva1Click(TObject *Sender);
    void __fastcall Cambiardecmara1Click(TObject *Sender);
    void __fastcall esquina1Click(TObject *Sender);
    void __fastcall frontal1Click(TObject *Sender);
    void __fastcall cenital1Click(TObject *Sender);
    void __fastcall lateral1Click(TObject *Sender);
    void __fastcall oblicua1Click(TObject *Sender);
    void __fastcall AbrirCerrar1Click(TObject *Sender);
    void __fastcall Encender1Click(TObject *Sender);
    void __fastcall Escena1Click(TObject *Sender);
    void __fastcall Lampara1Click(TObject *Sender);
    void __fastcall Muebles1Click(TObject *Sender);
    void __fastcall Escena2Click(TObject *Sender);
    void __fastcall Lampara2Click(TObject *Sender);
    void __fastcall Muebles2Click(TObject *Sender);
    void __fastcall Escena3Click(TObject *Sender);
    void __fastcall Lampara3Click(TObject *Sender);
    void __fastcall Muebles3Click(TObject *Sender);
    void __fastcall ApagarEncenderLmpara1Click(TObject *Sender);
    void __fastcall ApagarEncederVentana1Click(TObject *Sender);
    void __fastcall ActivarDesactivarNiebla1Click(TObject *Sender);
    void __fastcall ApagarEncenderAmbiente1Click(TObject *Sender);

private:        // User declarations
    HDC hdc;
    HGLRC hrc;
    GLfloat eyeX,eyeY,eyeZ, lookX,lookY,lookZ, upX,upY,upZ; // cámara
    GLdouble RatioViewPort, xLeft,xRight, yBot,yTop, N,F;  // volumen de vista
    GLfloat PosicionLuz0[4];  // luz0
    GLfloat PosicionLuz1[4];
    GLfloat PosicionLuz2[4];

    bool luzVentana,niebla;
    float anguloLuz;
    int numTexturas;

    ColorRGB** texturas;
    BMPRGB** listaBmp;

    void __fastcall SetPixelFormatDescriptor();
    void __fastcall GLScene();
    //void crearObjetosEscena();
    //void liberarObjetosEscena();
    void cargarTexturas();
    void configurarIluminacion();

    bool luzAmbiente,luzLampara;

public:		// User declarations
    __fastcall TGLForm3D(TComponent* Owner);

    Escena* escenario;

    //camara
    PV3D* eye, * up, * look;
    PV3D* eye2, * up2, * look2;
    Camara *camara, *camara1, *camara2;
    int opcion, nCamara;

    
};
//---------------------------------------------------------------------------
extern PACKAGE TGLForm3D *GLForm3D;
//---------------------------------------------------------------------------
#endif

