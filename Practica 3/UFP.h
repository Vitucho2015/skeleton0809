//---------------------------------------------------------------------------

 #ifndef UFPH
 #define UFPH

//---------------------------------------------------------------------------

 #include <Classes.hpp>
 #include <Controls.hpp>
 #include <StdCtrls.hpp>
 #include <Forms.hpp>
 #include <Menus.hpp>
 #include <ExtCtrls.hpp>
 #include <gl\gl.h>
 #include <gl\glu.h>
 #include "tPelota.h"
 #include "tConvexo.h"
 #include "tSegmento.h"
 #include "tObstaculoRecubierto.h"
 #include <stdlib.h>   //Librería Random

//---------------------------------------------------------------------------

 class TGLForm2D : public TForm
 {
        __published:
                TMainMenu *MMenu;
                TMenuItem *MSalir;
                //Reloj de juego
                TTimer *reloj;
    TMenuItem *Modo1;
    TMenuItem *Tonto1;
    TMenuItem *Listo1;

                void __fastcall FormCreate(TObject *Sender);
                void __fastcall FormResize(TObject *Sender);
                void __fastcall FormPaint(TObject *Sender);
                void __fastcall FormDestroy(TObject *Sender);
                void __fastcall MSalirClick(TObject *Sender);
                void __fastcall relojTimer(TObject *Sender);
    void __fastcall Tonto1Click(TObject *Sender);
    void __fastcall Listo1Click(TObject *Sender);

        private:
                HDC hdc;
                HGLRC hrc;
                //Definen el tamaño del volumen de vista
                GLfloat xLeft,xRight,yTop,yBot;
                //Guarda el radio del puerto de vista
                GLfloat RatioViewPort;

                //variables

                tPelota* pelota;//Pelota
                double radio;//radio de la pelota
                int numRebotes;//Contador del número de rebotes
                Lista<tObstaculo>* obstaculos; //Lista de obstaculos
                PuntoV2F* pSalida; //Punto de salida
                bool modoListo;

                //Métodos privados
                
                void __fastcall SetPixelFormatDescriptor();
                void __fastcall GLScene();

                void crearEscenario();
                void crearParedes(bool modo);
                void crearPelota();
                void crearObstaculos(bool modo);
                void avanzar();

        public:	
                __fastcall TGLForm2D(TComponent* Owner);
 };

//---------------------------------------------------------------------------

 extern PACKAGE TGLForm2D *GLForm2D;
 
//---------------------------------------------------------------------------

 #endif
