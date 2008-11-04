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
float x;
float y;
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
    TColorDialog *ColorDialog1;
    TMenuItem *Opcional1;
    TMenuItem *ColorAnidamiento1;
    TMenuItem *ElegirColores1;
    TMenuItem *AnidamientoTotal1;
    TMenuItem *Puntos1;
    TMenuItem *CentroAVE1;
    TMenuItem *CentroGravedad1;
    TMenuItem *Lineas1;
    TMenuItem *Triangulos1;
    TMenuItem *CentroAVE2;
    TMenuItem *CentroGravedad2;
    TMenuItem *Triangulos2;
    TMenuItem *Reiniciar1;
    TMenuItem *Reiniciar2;
    TMenuItem *Activar1;
    TMenuItem *Desactivar1;
    TMenuItem *Activar2;
    TMenuItem *Desactivar2;
  void __fastcall FormCreate(TObject *Sender);
  void __fastcall FormResize(TObject *Sender);
  void __fastcall FormPaint(TObject *Sender);
  void __fastcall FormDestroy(TObject *Sender);
    void __fastcall Tiling1Click(TObject *Sender);
    void __fastcall Acercar1Click(TObject *Sender);
    void __fastcall Alejar1Click(TObject *Sender);
    void __fastcall Trasladar1Click(TObject *Sender);
    void __fastcall Centrar1Click(TObject *Sender);
    void __fastcall Anidar1Click(TObject *Sender);
    void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift);
        void __fastcall AnidamientoTotal1Click(TObject *Sender);
    void __fastcall CentroAVE1Click(TObject *Sender);
    void __fastcall CentroGravedad1Click(TObject *Sender);
    void __fastcall Triangulos1Click(TObject *Sender);
    void __fastcall Reiniciar1Click(TObject *Sender);
    void __fastcall CentroAVE2Click(TObject *Sender);
    void __fastcall CentroGravedad2Click(TObject *Sender);
    void __fastcall Triangulos2Click(TObject *Sender);
    void __fastcall Reiniciar2Click(TObject *Sender);
    void __fastcall Activar1Click(TObject *Sender);
    void __fastcall Desactivar1Click(TObject *Sender);
    void __fastcall Activar2Click(TObject *Sender);
    void __fastcall Desactivar2Click(TObject *Sender);

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
    bool anidamientoTotal; //Indica si hay que anidar todo o no
    bool oscurecer;     //Indica si se oscurecen los triangulos
    bool mDesplazar;   //Indica si está en modo desplazar
    int nCol;          //Número de columnas para el embaldosado
    int nFil;          //Número de filas para el embaldosado
    GLint x1,x2,x3,y1,y2,y3;    //Coordenadas de los vértices del último triangulo
                                //dibujado
    float colorGravedad1,colorGravedad2,colorGravedad3; //Colores para el centro de gravedad
    float colorCentro1,colorCentro2,colorCentro3; //Colores para el centro del AVE
    float colorLinea1,colorLinea2,colorLinea3; //Colores para las lineas del triangulo
    float grosorGravedad,grosorCentro,grosorLinea;//Grosores para el centro de gravedad, del AVE y las lineas del triangulo

    listaVertices * listaV1;
    listaVertices * listaV2;
    listaVertices * listaV3;
 //Funciones
    void dibujarMotivo();
    void pintarConBaldosas();
    void pintarSinBaldosas();
    void zoom(int porcentaje);
    void calculaMedias();
	void calculaMedios();
    void dibujaTriangulo(int i);

 public:		// User declarations
   __fastcall TGLForm2D(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TGLForm2D *GLForm2D;
//---------------------------------------------------------------------------
#endif
