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
 #include "tCirculo.h"
 #include "tConvexo.h"
 #include <stdlib.h>   //Librería Random

//---------------------------------------------------------------------------

 class TGLForm2D : public TForm
 {
        __published:
                TMainMenu *MMenu;     
                TMenuItem *MInicio;
                TMenuItem *MSalir;
                //Reloj de juego
                TTimer *reloj;

                void __fastcall FormCreate(TObject *Sender);
                void __fastcall FormResize(TObject *Sender);
                void __fastcall FormPaint(TObject *Sender);
                void __fastcall FormDestroy(TObject *Sender);
                void __fastcall MSalirClick(TObject *Sender);
                void __fastcall MInicioClick(TObject *Sender);
                void __fastcall relojTimer(TObject *Sender);

        private:
                HDC hdc;
                HGLRC hrc;
                //Definen el tamaño del volumen de vista
                GLfloat xLeft,xRight,yTop,yBot;
                //Guarda el radio del puerto de vista
                GLfloat RatioViewPort;

                //variables

                tPelota* pelota;//Pelota
                int numRebotes;//Contador del número de rebotes
                Lista<tObstaculo>* obstaculos; //Lista de obstaculos
                PuntoV2F* pSalida; //Punto de salida

                //Métodos privados
                
                void __fastcall SetPixelFormatDescriptor();
                void __fastcall GLScene();

                void crearEscenario();
                void crearParedes();
                void crearPelota();
                void crearObstaculos();
                void avanzar();

        public:	
                __fastcall TGLForm2D(TComponent* Owner);
 };

//---------------------------------------------------------------------------

 extern PACKAGE TGLForm2D *GLForm2D;
 
//---------------------------------------------------------------------------

 #endif
