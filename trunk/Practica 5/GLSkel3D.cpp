//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "GLSkel3D.h"


//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TGLForm3D *GLForm3D;
//---------------------------------------------------------------------------
__fastcall TGLForm3D::TGLForm3D(TComponent* Owner): TForm(Owner)
{
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TGLForm3D::FormCreate(TObject *Sender)
{
  hdc=GetDC(Handle);
  SetPixelFormatDescriptor();
  hrc=wglCreateContext(hdc);
  if(hrc==NULL) ShowMessage("Error CreateContex");
  if(wglMakeCurrent(hdc, hrc)==false) ShowMessage("Error MakeCurrent");

  glClearColor(0.6,0.7,0.8,1.0);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
   // luz0
  glEnable(GL_LIGHT0);
  GLfloat LuzDifusa[]={1.0,1.0,1.0,1.0};
  glLightfv(GL_LIGHT0,GL_DIFFUSE,LuzDifusa);
  GLfloat LuzAmbiente[]={0.3,0.3,0.3,1.0};
  glLightfv(GL_LIGHT0,GL_AMBIENT,LuzAmbiente);
  PosicionLuz0[0]=25.0; PosicionLuz0[1]=25.0;
  PosicionLuz0[2]=0.0; PosicionLuz0[3]=1.0;
  glLightfv(GL_LIGHT0, GL_POSITION, PosicionLuz0);

  glEnable(GL_COLOR_MATERIAL);
  glMaterialf(GL_FRONT, GL_SHININESS, 0.1);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_NORMALIZE);
  glShadeModel(GL_SMOOTH);   //defecto

  // crearObjetosEscena();

  // cámara
  eyeX=20.0,
  eyeY=20.0,
  eyeZ=20.0,
  lookX=0.0,
  lookY=0.0,
  lookZ=0.0,
  upX=0;upY=1;upZ=0;
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(eyeX,eyeY,eyeZ, lookX,lookY,lookZ, upX,upY,upZ);

  // volumen de vista
  N=1; F=1000;
  xRight=2; xLeft=-xRight;
  yTop=xRight; yBot=-yTop;
  //Radio del Volumen de Vista =1
  //ClientWidth=400;
  //ClientHeight=400;
  RatioViewPort=1.0;

  eye=new PV3D(eyeX,eyeY,eyeZ,1);
  look=new PV3D(lookX,lookY,lookZ,1);
  up=new PV3D(upX,upY,upZ,1);

  eye2=new PV3D(eyeX,eyeY,eyeZ,1);
  look2=new PV3D(2.5,0,0,1);
  up2=new PV3D(upX,upY,upZ,1);

  camara1 = new Camara(eye,look,up);
  camara2 = new Camara(eye2, look2, up2);
  camara = camara1;
  camara->ortogonal(xLeft,xRight,yBot,yTop,N,F);
  nCamara = 1;
  opcion = 0;
  escenario=new Escena();
  GLScene();
}
//---------------------------------------------------------------------------
void __fastcall TGLForm3D::SetPixelFormatDescriptor()
{
  PIXELFORMATDESCRIPTOR pfd = {
    	sizeof(PIXELFORMATDESCRIPTOR),
        1,
        PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
        PFD_TYPE_RGBA,
        24,
        0,0,0,0,0,0,
        0,0,
        0,0,0,0,0,
        32,
        0,
        0,
        PFD_MAIN_PLANE,
        0,
        0,0,0 };
  int PixelFormat=ChoosePixelFormat(hdc,&pfd);
  SetPixelFormat(hdc,PixelFormat,&pfd);
}
//---------------------------------------------------------------------------
void __fastcall TGLForm3D::FormResize(TObject *Sender)
{
  //se actualiza puerto de vista y el radio
  if ((ClientHeight<=1.0) || (ClientHeight<=1.0)) {
        ClientWidth=400;
        ClientHeight=400;
        RatioViewPort=1.0;
  }
  else RatioViewPort=(GLfloat)ClientWidth/(GLfloat)ClientHeight;

  glViewport(0,0,ClientWidth,ClientHeight);

  // se actualiza el volumen de vista
  // para que su radio coincida con RatioViewPort
  GLfloat RatioVolVista=xRight/yTop;

  if (RatioVolVista>=RatioViewPort) {
     //Aumentamos yTop-yBot
     yTop= xRight/RatioViewPort;
     yBot=-yTop;
     }
  else {
     //Aumentamos xRight-xLeft
     xRight=RatioViewPort*yTop;
     xLeft=-xRight;
     }

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(xLeft,xRight, yBot,yTop, N,F);

  if(escenario != NULL){
    GLScene();
  }
}
//---------------------------------------------------------------------------
void __fastcall TGLForm3D::GLScene()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLightfv(GL_LIGHT0,GL_POSITION,PosicionLuz0);

  // Dibujar la escena
    escenario->dibujar();
  //glFlush();
  SwapBuffers(hdc);
}
//---------------------------------------------------------------------------
void __fastcall TGLForm3D::FormPaint(TObject *Sender)
{
  GLScene();
}
//---------------------------------------------------------------------------
void __fastcall TGLForm3D::FormDestroy(TObject *Sender)
{
  //liberarObjetosEscena();
  ReleaseDC(Handle,hdc);
  wglMakeCurrent(NULL,NULL);
  wglDeleteContext(hrc);

  delete camara1;
  delete camara2;

  delete escenario;
  escenario = NULL;
}
//--------------------------------------------------------------------------

void __fastcall TGLForm3D::roll1Click(TObject *Sender)
{
opcion = 1;  
}
//---------------------------------------------------------------------------

void __fastcall TGLForm3D::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
if(opcion == 1) {
  if(Key == 37)
    camara->roll(-5);
  if(Key == 39)
    camara->roll(5);
}
if(opcion == 2) {
  if(Key == 37)
    camara->yaw(1);
  if(Key == 39)
    camara->yaw(-1);
}
if(opcion == 3) {
  if(Key == 37)
    camara->pitch(-1);
  if(Key == 39)
    camara->pitch(1);
}
if(opcion == 4) {
  if(Key == 81) //q
      camara->desplazar(-0.1,0.0,0.0);
  else if(Key ==87)//w
      camara->desplazar(0.1,0.0,0.0);
  else if(Key == 69)//e
      camara->desplazar(0.0,-0.1,0.0);
  else if(Key == 82)//r
      camara->desplazar(0.0,0.1,0.0);
  else if(Key == 84) //t
      camara->desplazar(0.0,0.0,-0.1);
  else if(Key == 89) //y
      camara->desplazar(0.0,0.0,0.1);
}
GLScene();
}
//---------------------------------------------------------------------------

void __fastcall TGLForm3D::yaw1Click(TObject *Sender)
{
opcion = 2;
}
//---------------------------------------------------------------------------

void __fastcall TGLForm3D::pitch1Click(TObject *Sender)
{
opcion = 3;
}
//---------------------------------------------------------------------------

void __fastcall TGLForm3D::desplazar1Click(TObject *Sender)
{
opcion = 4;
}
//---------------------------------------------------------------------------

void __fastcall TGLForm3D::ortogonal1Click(TObject *Sender)
{
camara->ortogonal(xLeft, xRight, yBot, yTop, N, F);
GLScene();
}
//---------------------------------------------------------------------------

void __fastcall TGLForm3D::perspectiva1Click(TObject *Sender)
{
camara->perspectiva(90, 1, N,F);
GLScene();
}
//---------------------------------------------------------------------------

void __fastcall TGLForm3D::Cambiardecmara1Click(TObject *Sender)
{
if(nCamara == 1){
    camara = camara2;
    nCamara = 2;
}
else{
    camara = camara1;
    nCamara = 1;
}
camara->ortogonal(xLeft,xRight,yBot,yTop,N,F);
GLScene();

}
//---------------------------------------------------------------------------

void __fastcall TGLForm3D::esquina1Click(TObject *Sender)
{
PV3D *eyeAux, *lookAux, *upAux;
if(nCamara ==1) {
    eyeAux = new PV3D(4.0, 4.0, 3.0, 1);
    lookAux = new PV3D(0,0,0,1);
    upAux = new PV3D(0,1,0,1);
}
else{
    eyeAux = new PV3D(4.0, 4.0, 3.0, 1);
    lookAux = new PV3D(2.5,0,0,1);
    upAux = new PV3D(0,1,0,1);
}
camara->cambiaPosicion(eyeAux, lookAux, upAux);
camara->ortogonal(xLeft,xRight,yBot,yTop,N,F);
GLScene();
}
//---------------------------------------------------------------------------

void __fastcall TGLForm3D::frontal1Click(TObject *Sender)
{
PV3D *eyeAux, *lookAux, *upAux;
if(nCamara == 1){
    eyeAux = new PV3D(1.0, 1.0, 2.0, 1);
    lookAux = new PV3D(1,1,0,1);
    upAux = new PV3D(0,1,0,1);
}
else{
    eyeAux = new PV3D(3.5, 1.0, 2.0, 1);
    lookAux = new PV3D(3.5,1,0,1);
    upAux = new PV3D(0,1,0,1);
}
camara->cambiaPosicion(eyeAux, lookAux, upAux);
camara->ortogonal(xLeft,xRight,yBot,yTop,N,F);
GLScene();

}
//---------------------------------------------------------------------------

void __fastcall TGLForm3D::cenital1Click(TObject *Sender)
{
PV3D *eyeAux, *lookAux, *upAux;

if(nCamara == 1){
    eyeAux = new PV3D(1.0, 3.5, 2.0, 1);
    lookAux = new PV3D(1,0,1,1);
    upAux = new PV3D(0,1,0,1);
}
else{
    eyeAux = new PV3D(3.5, 3.5, 2.0, 1);
    lookAux = new PV3D(3.5,0,1,1);
    upAux = new PV3D(0,1,0,1);
}
camara->cambiaPosicion(eyeAux, lookAux, upAux);
camara->ortogonal(xLeft,xRight,yBot,yTop,N,F);
GLScene();
}
//---------------------------------------------------------------------------

void __fastcall TGLForm3D::lateral1Click(TObject *Sender)
{
PV3D *eyeAux, *lookAux, *upAux;
if(nCamara ==1) {
    eyeAux = new PV3D(0.0, 1.0, 1.0, 1);
    lookAux = new PV3D(1.0, 1.0, 1.0, 1);
    upAux = new PV3D(camara->getUp());
}
else{
    eyeAux = new PV3D(5.0, 1.0, 1.0, 1);
    lookAux = new PV3D(1.0,1.0,1.0,1);
    upAux = new PV3D(camara->getUp());
}
camara->cambiaPosicion(eyeAux, lookAux, upAux);
camara->ortogonal(xLeft,xRight,yBot,yTop,N,F);
GLScene();
}
//---------------------------------------------------------------------------

void __fastcall TGLForm3D::oblicua1Click(TObject *Sender)
{
PV3D* d = new PV3D(0.7,0.7,1,1);
camara->Oblicua(xLeft, xRight, yBot, yTop, N, F, d);
camara->ortogonal(xLeft, xRight, yBot, yTop, N, F);
GLScene();
}
//---------------------------------------------------------------------------

