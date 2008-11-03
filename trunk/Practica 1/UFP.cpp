//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <iostream.h>


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
    color1=1;
    color2=1;
    color3=1;
    R=1;
    G=1;
    B=1;
    tamlinea=1;
    tampunto=4;
    listaVertices *listaV1 = new listaVertices[100];
    listaVertices *listaV2 = new listaVertices[100];
    listaVertices *listaV3 = new listaVertices[100];



    /*listaV1[1].x=-180;
    listaV1[1].y=-160;
    listaV1[2].x=0;
    listaV1[2].y=160;

    listaV2[1].x=0;
    listaV2[1].y=160;
    listaV2[2].x=180;
    listaV2[2].y=160;

    listaV3[1].x=180;
    listaV3[1].y=160;
    listaV3[2].x=-180;
    listaV3[2].y=-160;    */

    




    oscurecer=false;
    anidamientoTotal=false;
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
        nFil=(nCol*ClientHeight*(xRight-xLeft))/(ClientWidth*(yTop-yBot));
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
    GLScene();
}

//---------------------------------------------------------------------------

void TGLForm2D::dibujarMotivo()
{
    //Dibujamos el triángulo
    glLineWidth(1.0);
    //Primer vértice del triángulo
    x1=-180;
    y1=-160;
    //Segundo vértice del triángulo
    x2=180;
    y2=-160;
    //Tercer vértice del triángulo
    x3=0;
    y3=160;
    glBegin(GL_LINE_LOOP);
        glColor3f(1,1,1);
        glVertex2i(x1,y1);
        glVertex2i(x2,y2);
        glVertex2i(x3,y3);
    glEnd();

    for(int i=1;i<nTriangulos;i++){
        calculaMedias();
        dibujaTriangulo(i);
    }
}

//---------------------------------------------------------------------------

void TGLForm2D::pintarConBaldosas()
{
    GLfloat ancho = ClientWidth /(GLfloat)nCol;
    GLfloat alto = ClientHeight /(GLfloat)nFil;

    glClear(GL_COLOR_BUFFER_BIT);
    GLint x,y;
    for (int i=0;i<nCol;i++){
        y= (GLint)alto*i;
        for (int j=0;j<nFil;j++){
            x=(GLint)ancho*j;
            glViewport(x,y,(GLint)ancho,(GLint)alto);
            dibujarMotivo();
        }
    }
 }

//---------------------------------------------------------------------------

void TGLForm2D::pintarSinBaldosas()
{
    //Dibujamos el centro del área visible de la escena
        glPointSize(tampunto);
        glBegin(GL_POINTS);
            glColor3f(0,0,1);
            glVertex2i((xLeft+xRight)/2,(yBot+yTop)/2);
        glEnd();

        //Dibujamos el triángulo

        glLineWidth(tamlinea);
        //Primer vértice del triángulo
        x1=-180;
        y1=-160;
        //Segundo vértice del triángulo
        x2=180;
        y2=-160;
        //Tercer vértice del triángulo
        x3=0;
        y3=160;
        glBegin(GL_LINE_LOOP);
            glColor3f(R,G,B);
            glVertex2i(x1,y1);
            glVertex2i(x2,y2);
            glVertex2i(x3,y3);
        glEnd();

        //Dibujamos el centro de gravedad del triángulo
        glPointSize(tampunto);
        glBegin(GL_POINTS);
            glColor3f(1,0,0);
            glVertex2i((GLint)(x1+x2+x3)/3,(GLint)(y1+y2+y3)/3);
        glEnd();
        
        //Parte de anidar nTriangulos
        if (anidamientoTotal==true){
                


        }

        for(int i=1;i<nTriangulos;i++){
            calculaMedias();
            dibujaTriangulo(i);
        }
}

//---------------------------------------------------------------------------

void __fastcall TGLForm2D::Centrar1Click(TObject *Sender)
{
    if (mEmbaldosado){
        mEmbaldosado = false;
        glViewport(0,0,ClientWidth,ClientHeight);
    }
    GLint xR,yT;
    xR=((GLint)(xLeft+xRight)/2)-((GLint)(x1+x2+x3)/3);
    xRight=xRight-xR;
    xLeft=xLeft-xR;
    yT=((GLint)(yBot+yTop)/2)-((GLint)(y1+y2+y3)/3);
    yTop=yTop-yT;
    yBot=yBot-yT;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(xLeft,xRight,yBot,yTop);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
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

void TGLForm2D::dibujaTriangulo(int i)
{
        glLineWidth(tamlinea);
    if (oscurecer==true){

    glBegin(GL_LINE_LOOP);
        float j = (float(i)/10);
        glColor3f(1-j,1-j,1-j);
        glVertex2i(x1,y1);
        glVertex2i(x2,y2);
        glVertex2i(x3,y3);
    glEnd();
    }

    else{

    glBegin(GL_LINE_LOOP);
        glColor3f(R,G,B);
        glVertex2i(x1,y1);
        glVertex2i(x2,y2);
        glVertex2i(x3,y3);
    glEnd();
    }
}

//---------------------------------------------------------------------------

void TGLForm2D::calculaMedias()
{
GLint x1_aux,x2_aux,x3_aux,y1_aux,y2_aux,y3_aux;
    x1_aux=(GLint)(x1+x2)/2;
    x2_aux=(GLint)(x2+x3)/2;
    x3_aux=(GLint)(x1+x3)/2;
    y1_aux=(GLint)(y1+y2)/2;
    y2_aux=(GLint)(y2+y3)/2;
    y3_aux=(GLint)(y1+y3)/2;
    x1=x1_aux;
    x2=x2_aux;
    x3=x3_aux;
    y1=y1_aux;
    y2=y2_aux;
    y3=y3_aux;
}

//---------------------------------------------------------------------------

void TGLForm2D::calculaMedios()
{
      int n = 2^(nTriangulos-1);
      float i = 180 / n ;
      float j= 320 / n;

      for (int a = 1;a<2^(nTriangulos-1);a=a+i){
         listaV1
      }



}

//---------------------------------------------------------------------------






void __fastcall TGLForm2D::AnidamientoTotal1Click(TObject *Sender)
{
if (anidamientoTotal == true)  {anidamientoTotal = false; AnidamientoTotal1->Checked=false;}
else {anidamientoTotal= true; AnidamientoTotal1->Checked=true;}
;

GLScene();
}
//---------------------------------------------------------------------------

void __fastcall TGLForm2D::ColorAnidamiento1Click(TObject *Sender)
{
if (oscurecer ==true) {oscurecer =false; ColorAnidamiento1->Checked = false;}

else {oscurecer = true;
      ColorAnidamiento1->Checked = true;}

      GLScene();


}
//---------------------------------------------------------------------------



void __fastcall TGLForm2D::ElegirColores1Click(TObject *Sender)
{
ColorDialog1->Execute();

TColor micolor = ColorDialog1-> Color;

 R = (float)(GetRValue(micolor))/255;
 G = (float)(GetGValue(micolor))/255;
 B = (float)(GetBValue(micolor))/255;
 GLScene();

}
//---------------------------------------------------------------------------

void __fastcall TGLForm2D::N1punto1Click(TObject *Sender)
{
tamlinea=1;
GLScene();
}
//---------------------------------------------------------------------------

void __fastcall TGLForm2D::N2puntos1Click(TObject *Sender)
{
tamlinea=2;
GLScene();
}
//---------------------------------------------------------------------------

void __fastcall TGLForm2D::N3puntos1Click(TObject *Sender)
{
tamlinea=3;
GLScene();
}
//---------------------------------------------------------------------------

void __fastcall TGLForm2D::N4puntos1Click(TObject *Sender)
{
tamlinea=4;
GLScene();
}
//---------------------------------------------------------------------------

void __fastcall TGLForm2D::N2puntos2Click(TObject *Sender)
{
tampunto=2;
GLScene();
}
//---------------------------------------------------------------------------

void __fastcall TGLForm2D::N4puntos2Click(TObject *Sender)
{
tampunto=4;
GLScene();
}
//---------------------------------------------------------------------------

void __fastcall TGLForm2D::N6puntos1Click(TObject *Sender)
{
tampunto=6;
GLScene();
}
//---------------------------------------------------------------------------

void __fastcall TGLForm2D::N8puntos1Click(TObject *Sender)
{
tampunto=8;
GLScene();
}
//---------------------------------------------------------------------------

