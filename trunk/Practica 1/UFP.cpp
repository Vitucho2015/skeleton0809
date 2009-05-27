//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UFP.h"
#include <math.h>
#include "UFTiling.h" //Formulario para el Tiling
#include "UFGrosor.h" //Formulario para el Grosor
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
    colorLinea1=1;colorLinea2=1;colorLinea3=1;//Lineas blancas
    colorCentro1=0;colorCentro2=0;colorCentro3=1;//Centro AVE azul
    colorGravedad1=1;colorGravedad2=0;colorGravedad3=0;//Centro Gravedad rojo
    grosorCentro=4;
    grosorGravedad=4;
    grosorLinea=1.0;

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
  else


  RatioViewPort= (float)ClientWidth/(float)ClientHeight;

  glViewport(0,0,ClientWidth,ClientHeight);

  // se actualiza el volumen de vista
  // para que su radio coincida con ratioViewPort
  GLfloat RatioVolVista=(xRight-xLeft)/(yTop-yBot);

  if (RatioViewPort<=RatioVolVista){//hemos hecho la ventana mas alta que ancha
     //Aumentamos yTop-yBot
     GLdouble altoNew= (xRight-xLeft)/RatioViewPort;
     GLdouble yCentro= (yTop+yBot)/2.0;
     yTop= yCentro + altoNew/2.0;
     yBot= yCentro - altoNew/2.0;

     }
  else{                //hemos hecho la ventana mas ancha que alta
     //Aumentamos xRight-xLeft
     GLdouble anchoNew= RatioViewPort*(yTop-yBot);
     GLdouble xCentro= (xRight+xLeft)/2.0;
     xRight= xCentro + anchoNew/2.0;
     xLeft= xCentro - anchoNew/2.0;
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
    if (listaV1!=NULL){
                 delete [] listaV1;
                 listaV1=NULL;
    }
    if (listaV2!=NULL){
                 delete [] listaV2;
                 listaV2=NULL;
    }
    if (listaV3!=NULL){
                  delete [] listaV3;
                  listaV3=NULL;
    }
}
//---------------------------------------------------------------------------
void __fastcall TGLForm2D::Tiling1Click(TObject *Sender)
{
    if (mDesplazar){
        mDesplazar = false;
    }

    if(UFT->pedirNumColumnas(nCol)){
        mEmbaldosado = true;
        nFil=((nCol+1)*ClientHeight*(xRight-xLeft))/(ClientWidth*(yTop-yBot));
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
    glLineWidth(grosorLinea);
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
        glColor3f(colorLinea1,colorLinea2,colorLinea3);
        glVertex2f(x1,y1);
        glVertex2f(x2,y2);
        glVertex2f(x3,y3);
    glEnd();

    if (anidamientoTotal){
			//calculaMedios();
                                int n =  pow (2,(nTriangulos-1));
                                float i = float(180 / float(n)) ;
                                 float j= float(320 / float(n));
                                 float k= float(360 / float(n));

                                 listaV1 = new listaVertices[2*n];
                                 listaV2 = new listaVertices[2*n];
                                 listaV3 = new listaVertices[2*n];

                                 listaV1[1].x=-180;
                                listaV1[1].y=-160;

                                listaV2[1].x=0;
                                listaV2[1].y=160;

                                 listaV3[1].x=180;
                                 listaV3[1].y=-160;

                                  for (int a = 2;a<=n;a++){
	                                listaV1[a].x=(listaV1[a-1].x)+i;
                                        listaV1[a].y=(listaV1[a-1].y)+j;

                                        listaV2[a].x=(listaV2[a-1].x)+i;
                                        listaV2[a].y=(listaV2[a-1].y)-j;

                                        listaV3[a].x=(listaV3[a-1].x)-k;
                                        listaV3[a].y=-160;
                                }

			//int n =  pow (2,(nTriangulos-1));

			for (int a = 2;a<=n;a++){
				glBegin(GL_LINE_LOOP);
					glColor3f(colorLinea1,colorLinea2,colorLinea3);
					glVertex2f(listaV1[a].x,listaV1[a].y);
					glVertex2f(listaV2[n-a+2].x,listaV2[n-a+2].y);
				glEnd();

				glBegin(GL_LINE_LOOP);
					glColor3f(colorLinea1,colorLinea2,colorLinea3);
					glVertex2f(listaV1[a].x,listaV1[a].y);
					glVertex2f(listaV3[n-a+2].x,listaV3[n-a+2].y);
				glEnd();

                                glBegin(GL_LINE_LOOP);
		                        glColor3f(colorLinea1,colorLinea2,colorLinea3);
		                        glVertex2f(listaV3[a].x,listaV3[a].y);
		                        glVertex2f(listaV2[n-a+2].x,listaV2[n-a+2].y);
		                glEnd();

			}
            if (listaV1!=NULL){
                delete [] listaV1;
                listaV1=NULL;
            }
            if (listaV2!=NULL){
                delete [] listaV2;
                listaV2=NULL;
            }
            if (listaV3!=NULL){
                delete [] listaV3;
                listaV3=NULL;
            }                         
        }
        else{
			for(int i=1;i<nTriangulos;i++){
				calculaMedias();
				dibujaTriangulo(i);
			}
		}
}

//---------------------------------------------------------------------------

void TGLForm2D::pintarConBaldosas()
{
    GLfloat ancho = ClientWidth /(GLfloat)nCol;
    GLfloat alto = ClientHeight /(GLfloat)nFil;

    glClear(GL_COLOR_BUFFER_BIT);
    GLfloat x,y;
    for (int i=0;i<nCol;i++){
        y= alto*i;
        for (int j=0;j<nFil;j++){
            x=ancho*j;
            glViewport(x,y,ancho,alto);
            dibujarMotivo();
        }
    }
 }

//---------------------------------------------------------------------------

void TGLForm2D::pintarSinBaldosas()
{
    //Dibujamos el centro del área visible de la escena
        glPointSize(grosorCentro);
        glBegin(GL_POINTS);
            glColor3f(colorCentro1,colorCentro2,colorCentro3);
            glVertex2f((xLeft+xRight)/2.0,(yBot+yTop)/2.0);
        glEnd();

        //Dibujamos el triángulo
        glLineWidth(grosorLinea);
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
            glColor3f(colorLinea1,colorLinea2,colorLinea3);
            glVertex2f(x1,y1);
            glVertex2f(x2,y2);
            glVertex2f(x3,y3);
        glEnd();

        //Dibujamos el centro de gravedad del triángulo
        glPointSize(grosorGravedad);
        glBegin(GL_POINTS);
            glColor3f(colorGravedad1,colorGravedad2,colorGravedad3);
            glVertex2f((x1+x2+x3)/3.0,(y1+y2+y3)/3.0);
        glEnd();

        //Parte de anidar nTriangulos
        if (anidamientoTotal){
			//calculaMedios();
                                int n =  pow (2,(nTriangulos-1));
                                float i = float(180 / float(n)) ;
                                 float j= float(320 / float(n));
                                 float k= float(360 / float(n));

                                 listaV1 = new listaVertices[2*n];
                                 listaV2 = new listaVertices[2*n];
                                 listaV3 = new listaVertices[2*n];

                                 listaV1[1].x=-180;
                                listaV1[1].y=-160;

                                listaV2[1].x=0;
                                listaV2[1].y=160;

                                 listaV3[1].x=180;
                                 listaV3[1].y=-160;

                                  for (int a = 2;a<=n;a++){
	                                listaV1[a].x=(listaV1[a-1].x)+i;
                                        listaV1[a].y=(listaV1[a-1].y)+j;

                                        listaV2[a].x=(listaV2[a-1].x)+i;
                                        listaV2[a].y=(listaV2[a-1].y)-j;

                                        listaV3[a].x=(listaV3[a-1].x)-k;
                                        listaV3[a].y=-160;
                                }

			//int n =  pow (2,(nTriangulos-1));

			for (int a = 2;a<=n;a++){
				glBegin(GL_LINE_LOOP);
					glColor3f(colorLinea1,colorLinea2,colorLinea3);
					glVertex2f(listaV1[a].x,listaV1[a].y);
					glVertex2f(listaV2[n-a+2].x,listaV2[n-a+2].y);
				glEnd();

				glBegin(GL_LINE_LOOP);
					glColor3f(colorLinea1,colorLinea2,colorLinea3);
					glVertex2f(listaV1[a].x,listaV1[a].y);
					glVertex2f(listaV3[n-a+2].x,listaV3[n-a+2].y);
				glEnd();

                                glBegin(GL_LINE_LOOP);
		                        glColor3f(colorLinea1,colorLinea2,colorLinea3);
		                        glVertex2f(listaV3[a].x,listaV3[a].y);
		                        glVertex2f(listaV2[n-a+2].x,listaV2[n-a+2].y);
		                glEnd();

			}
            if (listaV1!=NULL){
                delete [] listaV1;
                listaV1=NULL;
            }
            if (listaV2!=NULL){
                delete [] listaV2;
                listaV2=NULL;
            }
            if (listaV3!=NULL){
                delete [] listaV3;
                listaV3=NULL;
            }                         
        }
        else{
			for(int i=1;i<nTriangulos;i++){
				calculaMedias();
				dibujaTriangulo(i);
			}
		}
}

//---------------------------------------------------------------------------

void __fastcall TGLForm2D::Centrar1Click(TObject *Sender)
{
    if (mEmbaldosado){
        mEmbaldosado = false;
        glViewport(0,0,ClientWidth,ClientHeight);
    }
    GLfloat xR,yT;
    xR=((xLeft+xRight)/2.0)-((x1+x2+x3)/3.0);
    xRight=xRight-xR;
    xLeft=xLeft-xR;
    yT=((yBot+yTop)/2.0)-((y1+y2+y3)/3.0);
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
 	    switch (Key){        //Izquierda
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
    if (oscurecer){
        glBegin(GL_LINE_LOOP);
            float j = (float(i)/20);
            GLfloat r,g,b;
            r=colorLinea1-j;
            if((r)<0){
                r=0;
            }
            g=colorLinea2-j;
            if((g)<0){
                g=0;
            }
            b=colorLinea3-j;
            if((b)<0){
                b=0;
            }
            glColor3f(r,g,b);
            glVertex2f(x1,y1);
            glVertex2f(x2,y2);
            glVertex2f(x3,y3);
        glEnd();
    }
    else{
        glBegin(GL_LINE_LOOP);
            glColor3f(colorLinea1,colorLinea2,colorLinea3);
            glVertex2f(x1,y1);
            glVertex2f(x2,y2);
            glVertex2f(x3,y3);
        glEnd();
    }
}

//---------------------------------------------------------------------------

void TGLForm2D::calculaMedias()
{
GLfloat x1_aux,x2_aux,x3_aux,y1_aux,y2_aux,y3_aux;
    x1_aux=(GLfloat)(x1+x2)/(GLfloat)2;
    x2_aux=(GLfloat)(x2+x3)/(GLfloat)2;
    x3_aux=(GLfloat)(x1+x3)/(GLfloat)2;
    y1_aux=(GLfloat)(y1+y2)/(GLfloat)2;
    y2_aux=(GLfloat)(y2+y3)/(GLfloat)2;
    y3_aux=(GLfloat)(y1+y3)/(GLfloat)2;
    x1=x1_aux;
    x2=x2_aux;
    x3=x3_aux;
    y1=y1_aux;
    y2=y2_aux;
    y3=y3_aux;
}

//---------------------------------------------------------------------------

void __fastcall TGLForm2D::AnidamientoTotal1Click(TObject *Sender)
{
    if (anidamientoTotal){
        anidamientoTotal = false;
    }
    else{
        anidamientoTotal= true;
    }
}
//---------------------------------------------------------------------------

void __fastcall TGLForm2D::Activar1Click(TObject *Sender)
{
    
    oscurecer=true;
    anidamientoTotal = false;
    GLScene();
}
//---------------------------------------------------------------------------

void __fastcall TGLForm2D::CentroAVE1Click(TObject *Sender)
{
    if(ColorDialog1->Execute()){
        TColor c = ColorDialog1->Color;
        colorCentro1 = (GLfloat)GetRValue(ColorToRGB(c))/255;
        colorCentro2 = (GLfloat)GetGValue(ColorToRGB(c))/255;
        colorCentro3 = (GLfloat)GetBValue(ColorToRGB(c))/255;
        GLScene();
    }
}
//---------------------------------------------------------------------------

void __fastcall TGLForm2D::CentroGravedad1Click(TObject *Sender)
{
    if(ColorDialog1->Execute()){
        TColor c = ColorDialog1->Color;
        colorGravedad1 = (GLfloat)GetRValue(ColorToRGB(c))/255;
        colorGravedad2 = (GLfloat)GetGValue(ColorToRGB(c))/255;
        colorGravedad3 = (GLfloat)GetBValue(ColorToRGB(c))/255;
        GLScene();
    }
}
//---------------------------------------------------------------------------

void __fastcall TGLForm2D::Triangulos1Click(TObject *Sender)
{
    if(ColorDialog1->Execute()){
        TColor c = ColorDialog1->Color;
        colorLinea1 = (GLfloat)GetRValue(ColorToRGB(c))/255;
        colorLinea2 = (GLfloat)GetGValue(ColorToRGB(c))/255;
        colorLinea3 = (GLfloat)GetBValue(ColorToRGB(c))/255;
        GLScene();
    }
}
//---------------------------------------------------------------------------

void __fastcall TGLForm2D::Reiniciar1Click(TObject *Sender)
{
    colorLinea1=1;colorLinea2=1;colorLinea3=1;//Lineas blancas
    colorCentro1=0;colorCentro2=0;colorCentro3=1;//Centro AVE azul
    colorGravedad1=1;colorGravedad2=0;colorGravedad3=0;//Centro Gravedad rojo
    GLScene();
}
//---------------------------------------------------------------------------

void __fastcall TGLForm2D::CentroAVE2Click(TObject *Sender)
{
  //Elegir el grosor del centro AVE
    if(UFG->pedirGrosor(grosorCentro)){
        GLScene();
    }

}
//---------------------------------------------------------------------------

void __fastcall TGLForm2D::CentroGravedad2Click(TObject *Sender)
{
  //Elegir el grosor del centro Gravedad
    if(UFG->pedirGrosor(grosorGravedad)){
        GLScene();
    }
}
//---------------------------------------------------------------------------

void __fastcall TGLForm2D::Triangulos2Click(TObject *Sender)
{
  //Elegir el grosor de las lineas del triangulo
    if(UFG->pedirGrosor(grosorLinea)){
        GLScene();
    }
}
//---------------------------------------------------------------------------

void __fastcall TGLForm2D::Reiniciar2Click(TObject *Sender)
{
    grosorCentro=4;
    grosorGravedad=4;
    grosorLinea=1.0;
    GLScene();
}
//---------------------------------------------------------------------------

void __fastcall TGLForm2D::Desactivar1Click(TObject *Sender)
{
    oscurecer=false;
    anidamientoTotal = false;
    GLScene();
}
//---------------------------------------------------------------------------

void TGLForm2D::calculaMedios()
{
    int n =  pow (2,(nTriangulos-1));
    float i = float(180 / float(n)) ;
    float j= float(320 / float(n));
    float k= float(360 / float(n));
	  
    listaV1 = new listaVertices[2*n];
    listaV2 = new listaVertices[2*n];
    listaV3 = new listaVertices[2*n];

    listaV1[1].x=-180;
    listaV1[1].y=-160;

    listaV2[1].x=0;
    listaV2[1].y=160;

    listaV3[1].x=180;
    listaV3[1].y=-160;

    for (int a = 2;a<=n;a++){
	listaV1[a].x=(listaV1[a-1].x)+i;
        listaV1[a].y=(listaV1[a-1].y)+j;

        listaV2[a].x=(listaV2[a-1].x)+i;
        listaV2[a].y=(listaV2[a-1].y)-j;

        listaV3[a].x=(listaV3[a-1].x)-k;
        listaV3[a].y=-160;
    }
}
//---------------------------------------------------------------------------

void __fastcall TGLForm2D::Activar2Click(TObject *Sender)
{
    oscurecer=false;
    anidamientoTotal = true;
    GLScene();
}
//---------------------------------------------------------------------------

void __fastcall TGLForm2D::Desactivar2Click(TObject *Sender)
{
    oscurecer=false;
    anidamientoTotal = false;
    GLScene();
}
//---------------------------------------------------------------------------

