//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UFP.h"
#include "UFTiling.h" //Formulario para el Tiling
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TGLForm2D *GLForm2D;
//---------------------------------------------------------------------------
__fastcall TGLForm2D::TGLForm2D(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TGLForm2D::FormCreate(TObject *Sender)
{
    hdc = GetDC(Handle);
    SetPixelFormatDescriptor();
    hrc = wglCreateContext(hdc);
    if(hrc == NULL)
    	ShowMessage(":-)~ hrc == NULL");
    if(wglMakeCurrent(hdc, hrc) == false)
    	ShowMessage("Could not MakeCurrent");
    //Cor de fondo de la ventana
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    //inicialización del volumen de vista
    xRight=200.0; xLeft=-xRight;
    yTop=xRight; yBot=-yTop;
    //Radio del volumen de vista == 1

    //inicialización del puerto de vista
    //ClientWidth=400;
    //ClientHeight=400;
    RatioViewPort=1.0;

    // inicialización de las variables del programa
    nTriangulos=1;             //Solo tenemos el triángulo inicial
    mEmbaldosado = false;      //Modo embaldosado a falso
    mDesplazar = false;        //Modo desplazar a falso
    nCol = 1;                  //Variable de número columnas para embaldosar a 1
    nFil = 1;                  //Variable de número filas para embaldosar a 1
}
//---------------------------------------------------------------------------
void __fastcall TGLForm2D::SetPixelFormatDescriptor()
{
    PIXELFORMATDESCRIPTOR pfd = {
    	sizeof(PIXELFORMATDESCRIPTOR),
        1,
        PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
        PFD_TYPE_RGBA,
        32,
        0,0,0,0,0,0,
        0,0,
        0,0,0,0,0,
        32,
        0,
        0,
        PFD_MAIN_PLANE,
        0,
        0,0,0
    };
    int PixelFormat = ChoosePixelFormat(hdc, &pfd);
    SetPixelFormat(hdc, PixelFormat, &pfd);
}
//---------------------------------------------------------------------
void __fastcall TGLForm2D::FormResize(TObject *Sender)
{

 //se actualiza puerto de vista y su radio
  if ((ClientWidth<=1)||(ClientHeight<=1)){
     ClientWidth=400;
     ClientHeight=400;
     RatioViewPort=1.0;
     }
  else RatioViewPort= (float)ClientWidth/(float)ClientHeight;

  glViewport(0,0,ClientWidth,ClientHeight);

  // se actualiza el volumen de vista
  // para que su radio coincida con ratioViewPort
  GLfloat RatioVolVista=xRight/yTop;

  if (RatioVolVista>=RatioViewPort){
     //Aumentamos yTop-yBot
     yTop= xRight/RatioViewPort;
     yBot=-yTop;
     }
  else{
     //Aumentamos xRight-xLeft
     xRight=RatioViewPort*yTop;
     xLeft=-xRight;
     }

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(xLeft,xRight, yBot,yTop);


  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  GLScene();

}
//---------------------------------------------------------------------------
void __fastcall TGLForm2D::GLScene()
{
glClear(GL_COLOR_BUFFER_BIT);
// comandos para dibujar la escena
    if(mEmbaldosado){
        pintarConBaldosas();
    }
    else{
        pintarSinBaldosas();
    }

glFlush();
SwapBuffers(hdc);
}

//---------------------------------------------------------------------------
void __fastcall TGLForm2D::FormPaint(TObject *Sender)
{
  GLScene();
}
//---------------------------------------------------------------------------
void __fastcall TGLForm2D::FormDestroy(TObject *Sender)
{
    ReleaseDC(Handle,hdc);
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(hrc);
    // eliminar objetos creados
}
//---------------------------------------------------------------------------
void __fastcall TGLForm2D::Tilling1Click(TObject *Sender)
{
    if (mDesplazar){
        mDesplazar = false;
    }

    if(UFT->pedirNumColumnas(nCol)){
        mEmbaldosado = true;
        GLScene();
    }
}
//---------------------------------------------------------------------------

void __fastcall TGLForm2D::Acercar1Click(TObject *Sender)
{
    if (mEmbaldosado){
        mEmbaldosado = false;
        glViewport(0,0,ClientWidth,ClientHeight);
    }

    if (mDesplazar){
        mDesplazar = false;
    }

    //ZOOM: 110%
    zoom(110);
    GLScene();
}
//---------------------------------------------------------------------------

void __fastcall TGLForm2D::Alejar1Click(TObject *Sender)
{
    if (mEmbaldosado){
        mEmbaldosado = false;
        glViewport(0,0,ClientWidth,ClientHeight);
    }

    if (mDesplazar){
        mDesplazar = false;
    }

    //ZOOM: 90%
    zoom(90);
    GLScene();
}
//---------------------------------------------------------------------------

void __fastcall TGLForm2D::Trasladar1Click(TObject *Sender)
{
    if (mEmbaldosado){
        mEmbaldosado = false;
        glViewport(0,0,ClientWidth,ClientHeight);
    }

    mDesplazar = true;
}
//---------------------------------------------------------------------------

void TGLForm2D::zoom(int porcentaje)
{
    GLfloat f = (GLfloat)porcentaje/100;
    GLfloat xRight_aux = ((xRight+xLeft)/2)+(((xRight-xLeft)/f)/2);
    GLfloat xLeft_aux = ((xRight+xLeft)/2)-(((xRight-xLeft)/f)/2);
    GLfloat yTop_aux= ((yTop+yBot)/2)+(((yTop-yBot)/f)/2);
    GLfloat yBot_aux= ((yTop+yBot)/2)-(((yTop-yBot)/f)/2);
    xRight = xRight_aux;
    xLeft = xLeft_aux;
    yTop = yTop_aux;
    yBot = yBot_aux;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(xLeft,xRight,yBot,yTop);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

//---------------------------------------------------------------------------

void TGLForm2D::zoomProgresivo(GLfloat porcentaje)
{
    if (mEmbaldosado){
        mEmbaldosado = false;
        glViewport(0,0,ClientWidth,ClientHeight);
    }

    if (mDesplazar){
        mDesplazar = false;
    }

    GLint nPasos = 10;         //Número de pasos a ejecutar
    GLfloat f = (GLfloat)porcentaje/100;
    float incF=(f - 1)/(float)nPasos;
    float xL,xR,yT,yB;
    for (int i=0;i<=nPasos;i++){
        f=1+incF*i;
        xL=xLeft*f;
        xR=xRight*f;
        yT=yTop*f;
        yB=yBot*f;
        gluOrtho2D(xL,xR,yT,yB);
        GLScene();
        Sleep(100);
    }
    //Actualizamos las variables globales
    xLeft=xL;xRight=xR;yTop=yT;yBot=yB;
}

//---------------------------------------------------------------------------

void TGLForm2D::dibujarMotivo()
{

}

//---------------------------------------------------------------------------

void TGLForm2D::pintarConBaldosas()
{
    nFil=(nCol*ClientHeight*(xRight-xLeft))/(ClientWidth*(yTop-yBot));
    GLfloat ancho = ClientWidth /(GLfloat)nCol;
    GLfloat alto = ClientHeight /(GLfloat)nFil;

    glClear(GL_COLOR_BUFFER_BIT);

    for (int i=0;i<nCol;i++){
        for (int j=0;j<nFil;j++){
            glViewport((GLint)ancho*j,(GLint)alto*i,(GLint)ancho,(GLint)alto);
            dibujarMotivo();
        }
    }
    glFlush();
    SwapBuffers(hdc);
 }

//---------------------------------------------------------------------------

void TGLForm2D::pintarSinBaldosas()
{
    //Dibujamos el centro del área visible de la escena
        glPointSize(5);
        glBegin(GL_POINTS);
            glColor3f(0,0,1);
            glVertex2i((xLeft+xRight)/2,(yBot+yTop)/2);
        glEnd();

        //Dibujamos el triángulo
        glLineWidth(2.0);
        GLint x1,x2,x3,y1,y2,y3;
        //Primer vértice del triángulo
        x1=(GLint)xLeft*0.9;
        y1=(GLint)yBot*0.9;
        //Segundo vértice del triángulo
        x2=(GLint)xRight*0.9;
        y2=(GLint)yBot*0.9;
        //Tercer vértice del triángulo
        x3=(GLint)(xLeft+xRight)/2;
        y3=(GLint)yTop*0.9;;
        glBegin(GL_LINE_LOOP);
            glColor3f(1,1,1);
            glVertex2i(x1,y1);
            glVertex2i(x2,y2);
            glVertex2i(x3,y3);
        glEnd();

        //Dibujamos el centro de gravedad del triángulo
        glPointSize(5);
        glBegin(GL_POINTS);
            glColor3f(1,0,0);
            glVertex2i((GLint)(x1+x2+x3)/3,(GLint)(y1+y2+y3)/3);
        glEnd();
        //Falta la parte de anidar nTriangulos        
}

//---------------------------------------------------------------------------

void __fastcall TGLForm2D::Centrar1Click(TObject *Sender)
{
    if (mEmbaldosado){
        mEmbaldosado = false;
        glViewport(0,0,ClientWidth,ClientHeight);
    }

    xRight=(xRight-xLeft)/2; xLeft=-xRight;
    yTop=(yBot-yTop)/2; yBot=-yTop;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(xLeft,xRight,yBot,yTop);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    FormResize(this);
    GLScene();
}

//---------------------------------------------------------------------------

void __fastcall TGLForm2D::Anidar1Click(TObject *Sender)
{
    nTriangulos++;
    mEmbaldosado=false;
    glViewport(0,0,ClientWidth,ClientHeight);
    GLScene();
}

//---------------------------------------------------------------------------

void __fastcall TGLForm2D::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
 {
          if (mDesplazar){
 	        switch (Key)                {
                        //Izquierda
   		        case 37:{
                                GLfloat xRight_aux = xRight - (xRight-xLeft)*0.05;
                                GLfloat xLeft_aux = xLeft - (xRight-xLeft)*0.05;
                                xRight = xRight_aux;
                                xLeft = xLeft_aux;
                                break;
                        }
                        //Abajo
   		        case 38:{
                                GLfloat yBot_aux = yBot - (yBot-yTop)*0.05;
                                GLfloat yTop_aux = yTop - (yBot-yTop)*0.05;
                                yBot = yBot_aux;
                                yTop = yTop_aux;
                                break;
                        }
                        //Derecha
   		        case 39:{
                                GLfloat xRight_aux = xRight + (xRight-xLeft)*0.05;
                                GLfloat xLeft_aux = xLeft + (xRight-xLeft)*0.05;
                                xRight = xRight_aux;
                                xLeft = xLeft_aux;
                                break;
                        }
                        //Arriba
   		        case 40:{
                                GLfloat yBot_aux = yBot + (yBot-yTop)*0.05;
                                GLfloat yTop_aux = yTop + (yBot-yTop)*0.05;
                                yBot = yBot_aux;
                                yTop = yTop_aux;
                                break;
                        }
  	        }

                glMatrixMode(GL_PROJECTION);
                glLoadIdentity();
                gluOrtho2D(xLeft,xRight,yBot,yTop);
                glMatrixMode(GL_MODELVIEW);
                glLoadIdentity();
                GLScene();
        }
 }

//---------------------------------------------------------------------------
