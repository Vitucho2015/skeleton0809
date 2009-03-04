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

  //Luz0
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
  glShadeModel(GL_SMOOTH);   //Defecto

  crearObjetosEscena();


  //Inicialmente ninguna tecla pulsada
        qPulsada = false;
        wPulsada = false;
        tPulsada = false;


  //Inicializamos la variable de tiempo
        tiempo = 0;
  //Inicializamos el valor para los giros
        giroPanel = 0;
        giro = 0;
  //C�mara
  eyeX=100.0,
  eyeY=100.0,
  eyeZ=100.0,
  lookX=0.0,
  lookY=0.0,
  lookZ=0.0,
  upX=0;
  upY=1;
  upZ=0;
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(eyeX,eyeY,eyeZ, lookX,lookY,lookZ, upX,upY,upZ);

  //Volumen de vista
  N=1; F=1000;
  xRight=10; xLeft=-xRight;
  yTop=10; yBot=-yTop;
  //Ratio del volumen de vista =1
  //ClientWidth=400;
  //ClientHeight=400;
  RatioViewPort=1.0;
  version = 10;// No pinta nada
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
  //Se actualiza puerto de vista y ratio
  if ((ClientHeight<=1.0) || (ClientHeight<=1.0)) {
        ClientWidth=400;
        ClientHeight=400;
        RatioViewPort=1.0;
  }
  else RatioViewPort=(GLfloat)ClientWidth/(GLfloat)ClientHeight;

  glViewport(0,0,ClientWidth,ClientHeight);

  //Se actualiza el volumen de vista
  //para que su ratio coincida con RatioViewPort
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

  GLScene();
}
//---------------------------------------------------------------------------
void __fastcall TGLForm3D::GLScene()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLightfv(GL_LIGHT0,GL_POSITION,PosicionLuz0);

  glMatrixMode(GL_MODELVIEW);

  //Incremento de tiempo en cada movimiento
        double incrTiempo = 0.03;

  //Incremento del �ngulo de giro en cada movimiento

        double incrGiro = 5;

        glPushMatrix(); //guardamos una copia de la matriz superior en la pila

  switch(version){

   case 0: //Se pinta la copa
      pintaCopa();
      break;

   case 1: //Se pinta la espiral
      pintaEjes();
      pintaEspiral();
      break;

   case 2: //Se pinta la espiral con la esfera
      if (qPulsada)
        {
        tiempo = tiempo + incrTiempo;
        giro = giro + incrGiro;
        giroPanel = giroPanel+incrGiro;
        qPulsada = false;
        }

      if (wPulsada)
        {
        tiempo = tiempo - incrTiempo;
        giro = giro - incrGiro;
        giroPanel = giroPanel - incrGiro;
        wPulsada = false;
        }

        //Movemos seg�n �rbita
        glTranslatef(cos(tiempo)+tiempo*sin(tiempo),0,sin(tiempo)-tiempo*cos(tiempo));
        glRotatef(giro,0,1,0);

        glPopMatrix();

        //Dibujar trayectoria

        if ((trayectoria!=NULL)&&(tPulsada))
        {
        //Color: verde
        glColor3f(0,1,0);
        trayectoria->dibuja();
        }
      pintaEjes();
      pintaEspiral();
      pintaEsfera();
      break;

   default:;
  }
  glFlush();
  SwapBuffers(hdc);
}
//---------------------------------------------------------------------------
void __fastcall TGLForm3D::FormPaint(TObject *Sender)
{
  GLScene();
}
//---------------------------------------------------------------------------
void TGLForm3D::pintaEjes(){
   glBegin(GL_LINES);
      glColor4f(1.0,0.0,0.0,1.0);
      glVertex3d(0,0,0);
      glVertex3d(10,0,0);

      glColor4f(0.0,1.0,0.0,1.0);
      glVertex3d(0,0,0);
      glVertex3d(0,10,0);

      glColor4f(0.0,0.0,1.0,1.0);
      glVertex3d(0,0,0);
      glVertex3d(0,0,10);
   glEnd();
}
//---------------------------------------------------------------------------
void TGLForm3D::pintaEspiral(){

}
//---------------------------------------------------------------------------
void TGLForm3D::pintaEsfera(){
   glPushMatrix();
        if (bola != NULL){
         //Situamos bola
         glRotatef(90,1,0,0);
         //Color azul
         glColor3f(0,0,1);
         //Modo lineas
         gluQuadricDrawStyle(bola,GLU_LINE);
         gluSphere(bola,2,30,30);
   }
}
//---------------------------------------------------------------------------
void TGLForm3D::pintaCopa(){

}
//---------------------------------------------------------------------------
void __fastcall TGLForm3D::FormDestroy(TObject *Sender)
{
  //liberarObjetosEscena();
  ReleaseDC(Handle,hdc);
  wglMakeCurrent(NULL,NULL);
  wglDeleteContext(hrc);
}
//---------------------------------------------------------------------------
void TGLForm3D::crearObjetosEscena()
{
           bola = gluNewQuadric();
           //Configuraci�n de la trayectoria
        GLfloat nPT = 20;
        GLfloat nQT = 110;
        GLfloat radioT = 2;
        PV3D* origenCoor = new PV3D();
        //Creamos la trayectoria
        crearMallaTrayectoria(origenCoor,nPT,nQT,radioT,trayectoria);

}
//---------------------------------------------------------------------------
void TGLForm3D::liberarObjetosEscena()
{


}




void TGLForm3D::crearMallaTrayectoria(PV3D* origenCoor, int nP, int nQ, double radio, Espiral*& malla)
 {
        //Elementos de la malla
        int nVertices = nP*(nQ+1);
        int nNormales = nP*nQ;
        int nCaras = nP*nQ;
        PV3D** vertices = new PV3D*[nVertices];
        PV3D** normales = new PV3D*[nNormales];
        Cara** caras = new Cara*[nCaras];

        //Calculamos los v�rtices iniciales del pol�gono
        double alfa = 360/nP;
        PV3D* origen = new PV3D(origenCoor->getX()+radio,origenCoor->getY(),origenCoor->getZ());
        vertices[0] = origen;
        for (int i=1;i<nP;i++){
                //Calculamos vertice
                PV3D* v = new PV3D(
                  origenCoor->getX()+radio*cos((i*alfa*3.141592)/180),
                  origenCoor->getY()+radio*sin((i*alfa*3.141592)/180),
                  origenCoor->getZ());
                vertices[i] = v;
        }

        //Calculamos siguientes v�rtices por extrusi�n (Marco de Frenet)
        //moviendo el pol�gono inicial
        double t = 0;
        for (int i=1;i<=nQ;i++)
        {
                for (int j=0;j<nP;j++)
                {
                        PV3D* vBase = vertices[j];
                        //Extruir vBase obteniendo vExt
                        double x = vBase->getX();
                        double y = vBase->getY();
                        double z = vBase->getZ();
                        PV3D* vExt = new PV3D((sin(t))*(t-x)+cos(t)*((z+1)),y,(sin(t))*(z+1)+cos(t)*((x-t)));
                        vertices[nP*i+j] = vExt;
                }
                t = t + 0.2;
        }

        //Calculamos las caras
        for (int i=1;i<=nQ;i++)
        {
                for (int j=0;j<nP;j++)
                {
                        //Calculamos los vertices de la cara
                        VerticeNormal** vN = new VerticeNormal*[4];
                        vN[0]=new VerticeNormal(nP*(i-1)+j,nP*(i-1)+j);
                        vN[1]=new VerticeNormal(nP*(i-1)+((j+1)%nP),nP*(i-1)+j);
                        vN[2]=new VerticeNormal(nP*(i)+((j+1)%nP),nP*(i-1)+j);
                        vN[3]=new VerticeNormal(nP*(i)+j,nP*(i-1)+j);
                        Cara* cara=new Cara(4,vN);
                        caras[nP*(i-1)+j]=cara;

                        //Calculamos la normal de la cara
                        double nx = 0;
                        double ny = 0;
                        double nz = 0;
 		        for (int k=0;k<4;k++)
 		        {
			        PV3D* v1 = vertices[vN[k]->getVertice()];
			        PV3D* v2 = vertices[vN[(k+1)%4]->getVertice()];
 			        nx = nx + (v1->getY()-v2->getY())*(v1->getZ()+v2->getZ());
			        ny = ny + (v1->getZ()-v2->getZ())*(v1->getX()+v2->getX());
			        nz = nz + (v1->getX()-v2->getX())*(v1->getY()+v2->getY());
 		        }
		        PV3D* n = new PV3D(nx,ny,nz);
		        n->normalizar();
		        normales[nP*(i-1)+j]=n;
                }
        }

        malla = new Espiral(nVertices, vertices, nNormales, normales, nCaras, caras, nP, nQ, radio);
 }



void __fastcall TGLForm3D::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

 {
        switch (Key)
        {
        //Q
        case 81:{
        qPulsada = true;
        GLScene();
        break;
        }
        //W
        case 87:{
        wPulsada = true;
        GLScene();
        break;
        }
        //T
        case 84:{
        if (tPulsada)
        tPulsada = false;
        else
        tPulsada = true;
        GLScene();
        break;
        }

}

 }
//---------------------------------------------------------------------------
void __fastcall TGLForm3D::Parte11Click(TObject *Sender)
{
   version = 0;
}
//---------------------------------------------------------------------------

void __fastcall TGLForm3D::Parte21Click(TObject *Sender)
{
   version = 1;
}
//---------------------------------------------------------------------------

void __fastcall TGLForm3D::Parte31Click(TObject *Sender)
{
   version = 2;
}
//---------------------------------------------------------------------------
