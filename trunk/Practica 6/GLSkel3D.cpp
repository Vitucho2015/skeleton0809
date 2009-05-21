//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "GLSkel3D.h"
#include "UFDatos.h"

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
  
  glEnable(GL_COLOR_MATERIAL);
  glMaterialf(GL_FRONT, GL_SHININESS, 0.1);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_NORMALIZE);
  glShadeModel(GL_SMOOTH);   //defecto

  configurarIluminacion();
  texturasActivadas=false;
  cargarTexturas();

  // crearObjetosEscena();
  
  // cámara
  eyeX=2.8,
  eyeY=2.8,
  eyeZ=2.8,
  lookX=0.0,
  lookY=0.0,
  lookZ=0.0,
  upX=0;upY=1;upZ=0;
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(eyeX,eyeY,eyeZ,lookX,lookY,lookZ, upX,upY,upZ);

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

  eye2=new PV3D(eyeX+2.5,eyeY,eyeZ,1);
  look2=new PV3D(2.5,0,0,1);
  up2=new PV3D(upX,upY,upZ,1);

  camara1 = new Camara(eye,look,up);
  camara2 = new Camara(eye2,look2,up2);
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

  if(escenario != NULL)
    GLScene();
}
//---------------------------------------------------------------------------
void __fastcall TGLForm3D::GLScene()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  //glLightfv(GL_LIGHT0,GL_POSITION,PosicionLuz0);
  //glLightfv(GL_LIGHT1,GL_POSITION,PosicionLuz1);
  //glLightfv(GL_LIGHT2,GL_POSITION,PosicionLuz2);

  // Dibujar la escena
  escenario->dibujar();
 // configurarIluminacion();
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

  delete []texturas;
  for(int i=0;i<numTexturas;i++){
    delete listaBmp[i];
  }
  delete []listaBmp;
  
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
if(camara->getEstado() == 0){
	PV3D *eyeAux, *lookAux, *upAux;
	if(nCamara ==1) {
		eyeAux = new PV3D(2.8, 2.8, 2.8, 1);
		lookAux = new PV3D(0,0,0,1);
		upAux = new PV3D(0,1,0,1);
	}
	else{
		eyeAux = new PV3D(5.3, 2.8,2.8 , 1);
		lookAux = new PV3D(2.5,0.0,0.0,1);
		upAux = new PV3D(0,1,0,1);
	}
	camara->cambiaPosicion(eyeAux, lookAux, upAux);
}

camara->ortogonal(xLeft, xRight, yBot, yTop, N, F);
GLScene();
}
//---------------------------------------------------------------------------

void __fastcall TGLForm3D::perspectiva1Click(TObject *Sender)
{

if (camara->getEstado() == 0){
	PV3D *eyeAux, *lookAux, *upAux;
	if(nCamara ==1) {
		eyeAux = new PV3D(2.2, 2.0, 2.0, 1);
		lookAux = new PV3D(0.0, 0.0, 0.0, 1);
		upAux = new PV3D(camara->getUp());
	}
	else{
		eyeAux = new PV3D(4.0, 2.0, 2.0, 1);
		lookAux = new PV3D(2.0,0.0,0.0,1);
		upAux = new PV3D(camara->getUp());
	}
	camara->cambiaPosicion(eyeAux, lookAux, upAux);
}

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
    eyeAux = new PV3D(2.8, 2.8, 2.8, 1);
    lookAux = new PV3D(0,0,0,1);
    upAux = new PV3D(0,1,0,1);
}
else{
    eyeAux = new PV3D(5.3, 2.8,2.8 , 1);
    lookAux = new PV3D(2.5,0.0,0.0,1);
    upAux = new PV3D(0,1,0,1);
}
camara->cambiaPosicion(eyeAux, lookAux, upAux);
camara->setEstado(0);
//camara->ortogonal(xLeft,xRight,yBot,yTop,N,F);
GLScene();
}
//---------------------------------------------------------------------------

void __fastcall TGLForm3D::frontal1Click(TObject *Sender)
{
PV3D *eyeAux, *lookAux, *upAux;
if(nCamara == 1){
    eyeAux = new PV3D(1.0, 1.0, 3.0, 1);
    lookAux = new PV3D(1,1,0,1);
    upAux = new PV3D(0,1,0,1);
}
else{
    eyeAux = new PV3D(3.5, 1.0, 3.0, 1);
    lookAux = new PV3D(3.5,1,0,1);
    upAux = new PV3D(0,1,0,1);
}
camara->cambiaPosicion(eyeAux, lookAux, upAux);
camara->setEstado(2);
//camara->ortogonal(xLeft,xRight,yBot,yTop,N,F);
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
camara->setEstado(3);
//camara->ortogonal(xLeft,xRight,yBot,yTop,N,F);
GLScene();
}
//---------------------------------------------------------------------------

void __fastcall TGLForm3D::lateral1Click(TObject *Sender)
{
PV3D *eyeAux, *lookAux, *upAux;
if(nCamara ==1) {
    eyeAux = new PV3D(-0.9, 1.0, 1.0, 1);
    lookAux = new PV3D(1.0, 1.0, 1.0, 1);
    upAux = new PV3D(camara->getUp());
}
else{
    eyeAux = new PV3D(5.0, 1.0, 1.0, 1);
    lookAux = new PV3D(1.0,1.0,1.0,1);
    upAux = new PV3D(camara->getUp());
}
camara->cambiaPosicion(eyeAux, lookAux, upAux);
camara->setEstado(1);
//camara->ortogonal(xLeft,xRight,yBot,yTop,N,F);
GLScene();
}
//---------------------------------------------------------------------------

void __fastcall TGLForm3D::oblicua1Click(TObject *Sender)
{
//double coorX,coorY,coorZ;
//if(FDatos->pedirDatos(coorX,coorY,coorZ)){
    //

    //tPV* direccion = new tPV(0.7,0.7,1);
if(camara->getEstado() == 0){
	PV3D *eyeAux, *lookAux, *upAux;
	if(nCamara ==1) {
		eyeAux = new PV3D(2.8, 2.8, 2.8, 1);
		lookAux = new PV3D(0,0,0,1);
		upAux = new PV3D(0,1,0,1);
	}
	else{
		eyeAux = new PV3D(5.3, 2.8,2.8 , 1);
		lookAux = new PV3D(2.5,0.0,0.0,1);
		upAux = new PV3D(0,1,0,1);
	}
	camara->cambiaPosicion(eyeAux, lookAux, upAux);
}
        PV3D* d = new PV3D(0.5,2,5,1);
        camara->Oblicua(xLeft, xRight, yBot, yTop, N, F, d);
        GLScene();

//}
}

//---------------------------------------------------------------------------

void __fastcall TGLForm3D::Encender1Click(TObject *Sender)
{
    if(escenario != NULL){
        escenario->cambiaTV(1);
        GLScene();
    }
}

//---------------------------------------------------------------------------

void __fastcall TGLForm3D::AbrirCerrar1Click(TObject *Sender)
{
    if(escenario != NULL){
        while(escenario->cambiaPuerta(2)){
            GLScene();
        }
        GLScene();
    }
}

//---------------------------------------------------------------------------

void __fastcall TGLForm3D::Escena1Click(TObject *Sender)
{
    double coorX,coorY,coorZ;
    if(FDatos->pedirDatos(coorX,coorY,coorZ)){
        PV3D* v = new PV3D(coorX,coorY,coorZ,1);
        escenario->escalar(v,1);
        delete v;
        GLScene();
    }
}

//---------------------------------------------------------------------------

void __fastcall TGLForm3D::Lampara1Click(TObject *Sender)
{
    double coorX,coorY,coorZ;
    if(FDatos->pedirDatos(coorX,coorY,coorZ)){
        PV3D* v = new PV3D(coorX,coorY,coorZ,1);
        anguloLuz = anguloLuz * coorY;
        glLightf(GL_LIGHT1,GL_SPOT_CUTOFF,anguloLuz);
        escenario->escalar(v,2);
        delete v;
        GLScene();
    }
}

//---------------------------------------------------------------------------

void __fastcall TGLForm3D::Muebles1Click(TObject *Sender)
{
    double coorX,coorY,coorZ;
    if(FDatos->pedirDatos(coorX,coorY,coorZ)){
        PV3D* v = new PV3D(coorX,coorY,coorZ,1);
        escenario->escalar(v,3);
        delete v;
        GLScene();
    }
}

//---------------------------------------------------------------------------

void __fastcall TGLForm3D::Escena2Click(TObject *Sender)
{
    double coorX,coorY,coorZ;
    int grados;
    if(FDatos->pedirDatos(coorX,coorY,coorZ,grados)){
        PV3D* v = new PV3D(coorX,coorY,coorZ,1);
        escenario->rotar(v,grados,1);
        delete v;
        GLScene();
    }
}

//---------------------------------------------------------------------------

void __fastcall TGLForm3D::Lampara2Click(TObject *Sender)
{
    double coorX,coorY,coorZ;
    int grados;
    if(FDatos->pedirDatos(coorX,coorY,coorZ,grados)){
        PV3D* v = new PV3D(coorX,coorY,coorZ,1);
        escenario->rotar(v,grados,2);
        delete v;
        GLScene();
    }
}

//---------------------------------------------------------------------------

void __fastcall TGLForm3D::Muebles2Click(TObject *Sender)
{
    double coorX,coorY,coorZ;
    int grados;
    if(FDatos->pedirDatos(coorX,coorY,coorZ,grados)){
        PV3D* v = new PV3D(coorX,coorY,coorZ,1);
        escenario->rotar(v,grados,3);
        delete v;
        GLScene();
    }
}

//---------------------------------------------------------------------------

void __fastcall TGLForm3D::Escena3Click(TObject *Sender)
{
    double coorX,coorY,coorZ;
    if(FDatos->pedirDatos(coorX,coorY,coorZ)){
        PV3D* v = new PV3D(coorX,coorY,coorZ,1);
        escenario->trasladar(v,1);
        delete v;
        GLScene();
    }
}

//---------------------------------------------------------------------------

void __fastcall TGLForm3D::Lampara3Click(TObject *Sender)
{
    double coorX,coorY,coorZ;
    if(FDatos->pedirDatos(coorX,coorY,coorZ)){
        PV3D* v = new PV3D(coorX,coorY,coorZ,1);
        PosicionLuz1[0] = PosicionLuz1[0] + coorX;
        PosicionLuz1[1] = PosicionLuz1[1] + coorY;
        PosicionLuz1[2] = PosicionLuz1[2] + coorZ;
        PosicionLuz1[3] = 1.0;
        glLightfv(GL_LIGHT1, GL_POSITION, PosicionLuz1);
        escenario->trasladar(v,2);
        delete v;
        GLScene();
    }
}

//---------------------------------------------------------------------------

void __fastcall TGLForm3D::Muebles3Click(TObject *Sender)
{
    double coorX,coorY,coorZ;
    if(FDatos->pedirDatos(coorX,coorY,coorZ)){
        PV3D* v = new PV3D(coorX,coorY,coorZ,1);
        escenario->trasladar(v,3);
        delete v;
        GLScene();
    }
}

//---------------------------------------------------------------------------

void __fastcall TGLForm3D::ApagarEncenderLmpara1Click(TObject *Sender)
{
//Cambia de estado la luz de la lámpara
if(luzLampara) {
    luzLampara = false;
    glDisable(GL_LIGHT1);
}
else {
    luzLampara = true;
    glEnable(GL_LIGHT1);
}
GLScene();
}
//---------------------------------------------------------------------------

void __fastcall TGLForm3D::ApagarEncederVentana1Click(TObject *Sender)
{
//Cambia de estado la luz de las ventanas
if(luzVentana) {
    luzVentana = false;
    glDisable(GL_LIGHT2);
    glDisable(GL_LIGHT3);
}
else {
    luzVentana = true;
    glEnable(GL_LIGHT2);
    glEnable(GL_LIGHT3);
}
GLScene();
}
//---------------------------------------------------------------------------

void __fastcall TGLForm3D::ActivarDesactivarNiebla1Click(TObject *Sender)
{
//Cambia de estado la niebla
if(niebla) {
    niebla = false;
    glDisable(GL_FOG);
}
else {
    niebla = true;
    GLfloat density = 0.5;
    GLfloat fogColor[4] = {0.5, 0.5, 0.5, 1.0};   
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_FOG);
    glFogi(GL_FOG_MODE, GL_EXP);
    glFogfv(GL_FOG_COLOR, fogColor);
    glFogf(GL_FOG_DENSITY, density);
    glHint(GL_FOG_HINT, GL_NICEST);
}
GLScene();
}

//---------------------------------------------------------------------------

void TGLForm3D::cargarTexturas(){


    if (texturasActivadas){
        numTexturas = 5;
    texturas = new ColorRGB*[numTexturas];
    listaBmp = new BMPRGB*[numTexturas];

    BMPRGB* bmp1 = new BMPRGB();
    bmp1->cargarBMP("./Texturas/moqueta.bmp");
    texturas[0] = bmp1->getBMP();
    listaBmp[0] = bmp1;
    BMPRGB* bmp2 = new BMPRGB();
    bmp2->cargarBMP("./Texturas/parquet.bmp");
    texturas[1] = bmp2->getBMP();
    listaBmp[1] = bmp2;
    BMPRGB* bmp3 = new BMPRGB();
    bmp3->cargarBMP("./Texturas/homer.bmp");
    texturas[2] = bmp3->getBMP();
    listaBmp[2] = bmp3;
    BMPRGB* bmp4 = new BMPRGB();
    bmp4->cargarBMP("./Texturas/ruido.bmp");
    texturas[3] = bmp4->getBMP();
    listaBmp[3] = bmp4;
    BMPRGB* bmp5 = new BMPRGB();
    bmp5->cargarBMP("./Texturas/puerta.bmp");
    texturas[4] = bmp5->getBMP();
    listaBmp[4] = bmp5;
    for(int i=0; i<numTexturas; i++){
        glBindTexture(GL_TEXTURE_2D,i);
        glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);//Hay que ponerlo después de cada glBindText
        glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB,listaBmp[i]->getCols(),listaBmp[i]->getRows(),
                     0,GL_RGB,GL_UNSIGNED_BYTE,texturas[i]);
        glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    }}
}

//---------------------------------------------------------------------------

void TGLForm3D::configurarIluminacion(){



    glEnable(GL_LIGHTING);

    //Luz ambiente

    glDisable(GL_LIGHT0);

    GLfloat LuzDifusa[] = {0.2,0.2,0.2,1.0};

    GLfloat LuzAmbiente[] = {0.5,0.5,0.5,1};

    PosicionLuz0[0]= 0.0;
    PosicionLuz0[1]= 0.0;
    PosicionLuz0[2]= 25.0;
    PosicionLuz0[3]= 0.0;

    glLightfv(GL_LIGHT0,GL_DIFFUSE,LuzDifusa);
    glLightfv(GL_LIGHT0,GL_AMBIENT,LuzAmbiente);
    glLightfv(GL_LIGHT0, GL_POSITION, PosicionLuz0);

    luzAmbiente = false;

    //Luz lampara
    glDisable(GL_LIGHT1);

    anguloLuz = 45.0;
    GLfloat LuzDifusa1[] = {1.0,1.0,1.0,1.0};
    //PosicionLuz1[0] = 1.3;
    //PosicionLuz1[1] = 1.8;
    //PosicionLuz1[2] = 1.0;
    //PosicionLuz1[3] = 1.0;
    PosicionLuz1[0] = 1.3;
    PosicionLuz1[1] = 1.8;
    PosicionLuz1[2] = 1;
    PosicionLuz1[3] = 1.0;


    GLfloat d1[] = {0,-1,0};

   // glLightfv(GL_LIGHT1,GL_AMBIENT,LuzAmbiente);
    glLightfv(GL_LIGHT1,GL_DIFFUSE,LuzDifusa1);
    glLightfv(GL_LIGHT1,GL_POSITION,PosicionLuz1);
    glLightfv(GL_LIGHT1,GL_SPOT_DIRECTION,d1);
    glLightf(GL_LIGHT1,GL_SPOT_CUTOFF,anguloLuz);
    //glLightf(GL_LIGHT1,GL_SPOT_EXPONENT,0.0);

    luzLampara = false;

    //Luz Ventanas

    anguloVentana = 45.0;

    //ventana Habitacion Izquierda

    glDisable(GL_LIGHT2);

    GLfloat LuzDifusa2[] = {1.0,1.0,1.0,1.0};
    GLfloat LuzAmbiente2[] = {0.3,0.3,0.3,1.0};
    PosicionLuz2[0] = 1.0;
    PosicionLuz2[1] = 1.5;
    PosicionLuz2[2] = 0.0;
    PosicionLuz2[3] = 1.0;
    GLfloat d2[] = {0.0,-1.0,-1.0,1.0};

    glLightfv(GL_LIGHT2,GL_DIFFUSE,LuzDifusa2);
    glLightfv(GL_LIGHT2,GL_POSITION,PosicionLuz2);
    glLightfv(GL_LIGHT2,GL_AMBIENT,LuzAmbiente2);
    glLightfv(GL_LIGHT2,GL_SPOT_DIRECTION,d2);
    glLightf(GL_LIGHT2,GL_SPOT_CUTOFF,anguloVentana);

    //ventana Habitacion Derecha
    glDisable(GL_LIGHT3);

    GLfloat LuzDifusa3[] = {1.0,1.0,1.0,1.0};
    GLfloat LuzAmbiente3[] = {0.3,0.3,0.3,1.0};
    PosicionLuz3[0] = 3.0;PosicionLuz3[1] = 1.5;
    PosicionLuz3[2] = 0.0;PosicionLuz3[3] = 1.0;
    GLfloat d3[] = {0.0,-1.0,-1.0,0.0};

    glLightfv(GL_LIGHT3, GL_POSITION,PosicionLuz3);
    glLightfv(GL_LIGHT3,GL_DIFFUSE,LuzDifusa3);
    glLightfv(GL_LIGHT3,GL_AMBIENT,LuzAmbiente3);
    glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, d3);
    glLightf(GL_LIGHT3,GL_SPOT_CUTOFF,anguloVentana);

    luzVentana = false;

    //Niebla

    niebla = false;

    glPopMatrix();
}

//---------------------------------------------------------------------------

void __fastcall TGLForm3D::ApagarEncenderAmbiente1Click(TObject *Sender)
{
    if(!luzAmbiente){
        glEnable(GL_LIGHT0);
        luzAmbiente = true;
    }
    else{
        glDisable(GL_LIGHT0);
        luzAmbiente = false;
    }
    GLScene();
}
//---------------------------------------------------------------------------


void __fastcall TGLForm3D::Activardesactivar1Click(TObject *Sender)
{
    if (texturasActivadas==true) texturasActivadas=false;
         else texturasActivadas=true;
         cargarTexturas();
         GLScene();
}
//---------------------------------------------------------------------------

