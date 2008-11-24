//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UFP.h"
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
    //Color de fondo de la ventana
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    //inicialización del volumen de vista
    escena=new Escena();
    esOrigen=false;
    xRight=escena->damexRight();
    xLeft=escena->damexLeft();
    yTop=escena->dameyTop();
    yBot=escena->dameyBot();
    //Radio del volumen de vista == 1

    //inicialización del puerto de vista
    //ClientWidth=400;
    //ClientHeight=400;
    RatioViewPort=1.0;

    // inicialización de las variables del programa

    estado = nada;
    zoom = 0;
    iteraciones = 0;
    listaPuntos = NULL;

    num_iter=0;
    lado_ini=0;
    incr_lado=0;
    giro=0;

    numLados=0;
    longLados=0;

    origen = NULL;
    destino = NULL;
    puntoAnt = NULL;
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
glFlush();
    if(escena != NULL){
        escena->dibuja();
    }
    if(listaPuntos != NULL){
        listaPuntos->inicia();
        for(int i=0;i<listaPuntos->getLongitud();i++){
            PuntoV2F* aux=listaPuntos->getActual();
            aux->dibuja();
            listaPuntos->avanza();
        }
    }
SwapBuffers(hdc);
}

//---------------------------------------------------------------------------
void __fastcall TGLForm2D::FormPaint(TObject *Sender)
{
  GLScene();
}

//---------------------------------------------------------------------------

 PuntoV2F* TGLForm2D::devCoordenada(int X, int Y)
 {
        //Transforma a coordenadas en la escena
        GLfloat xAux = X*((xRight-xLeft)/ClientWidth) + xLeft;
        GLfloat yAux = -Y*((yTop - yBot)/ClientHeight) + yTop;
        PuntoV2F* punto = new PuntoV2F(xAux,yAux);
        return punto;
 }


 void TGLForm2D::desactivarModos(){

        estado=nada;



 }
   //---------------------------------------------------------------------------

 void TGLForm2D::modoEspiral(int X, int Y)  {
        if (puntoAnt!=NULL)
        {
                delete puntoAnt;
        }

        //Transforma a coordenadas en la escena
        puntoAnt = devCoordenada(X,Y);

        //Creamos la espiral
        DibujoLineas* espiral = new DibujoLineas(puntoAnt,num_iter,lado_ini,incr_lado,giro);

        //Añadimos a la lista
        escena->inserta(espiral);
        GLScene();
 }
  //---------------------------------------------------------------------------

 void TGLForm2D::modoPoligono(int X, int Y)  {


        if (puntoAnt!=NULL)
        {
                delete puntoAnt;
        }

        //Transforma a coordenadas en la escena
        puntoAnt = devCoordenada(X,Y);

        //Creamos el poligono
        DibujoLineas*polig = new DibujoLineas(puntoAnt,numLados,longLados);

        //Añadimos el poligono
        escena->inserta(polig);
        GLScene();
 }



 //---------------------------------------------------------------------------

 float TGLForm2D::calculoAngulo(PuntoV2F A, PuntoV2F B)   {

      float hipo = sqrt(pow(B.getX()-A.getX(),2) + pow(B.getY()-A.getY(),2));

      float altura = B.getY()-A.getY();

      float angulo = cosh(altura/hipo);

      if ( (B.getY()>=A.getY()) && (B.getX()>=A.getX()) ) return angulo;
      else if ((B.getY()<A.getY()) && (B.getX()>=A.getX())) return -angulo;
      else if ((B.getY()<A.getY()) && (B.getX()<A.getX())) return angulo+180;
      else if ((B.getY()>=A.getY()) && (B.getX()<A.getX())) return 180-angulo;
 }

 //---------------------------------------------------------------------------

 void TGLForm2D::modoLinea(int X, int Y)
 {
              if (!esOrigen){ //Primer punto de la linea

                if (puntoAnt!=NULL)
                {
                        delete puntoAnt;
                }

                //Transforma a coordenadas en la escena
                puntoAnt = devCoordenada(X,Y);
                esOrigen = true;

        }else{ //No es primer punto de la linea/

                PuntoV2F*or = new PuntoV2F(puntoAnt);
                delete puntoAnt;

                //Transforma a coordenadas en la escena

                PuntoV2F*dest = devCoordenada(X,Y);
                //destino = new PuntoV2F(dest);
                puntoAnt = new PuntoV2F(dest);
                Linea* linea = new Linea(or,dest);

                //Creamos una polilinea si no está creada
                if (!PLCreada){
                        poliLinea = new DibujoLineas();
                        PLCreada = true;
                        escena->inserta(poliLinea);
                }

                //Añadimos la linea
                poliLinea->insertaLinea(linea);
                GLScene();
        }


 }
//---------------------------------------------------------------------------
void __fastcall TGLForm2D::FormDestroy(TObject *Sender)
{
    ReleaseDC(Handle,hdc);
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(hrc);
    // eliminar objetos creados
    if(escena != NULL){
        delete escena;
        escena = NULL;
    }
    if(puntoAnt != NULL){
        delete puntoAnt;
        puntoAnt = NULL;
    }
    if(origen != NULL){
        delete origen;
        origen = NULL;
    }
    if(destino != NULL){
        delete destino;
        destino = NULL;
    }
}
//---------------------------------------------------------------------------

void __fastcall TGLForm2D::Lineas1Click(TObject *Sender)
{

      estado=linea;
      esOrigen=false;



/*//Dibujar poli_lineas
    if(estado == linea){
        if(puntoAnt != NULL){
            delete puntoAnt;
            puntoAnt = NULL;
            escena->insertaPoliLinea();
        }
    }
    estado=linea; */
}
//---------------------------------------------------------------------------

void __fastcall TGLForm2D::Poligono1Click(TObject *Sender)
{
//Dibujar Poligonos
    if (FormPoligono->pedirPoligono(numLados,longLados)){
        ShowMessage("Selecciona el centro");
        estado = poligono;
    }  
}
//---------------------------------------------------------------------------

void __fastcall TGLForm2D::Espiral1Click(TObject *Sender)
{
//Dibujar espiral
    if (FormEspiral->pedirEspiral(num_iter,lado_ini,incr_lado,giro)){
        ShowMessage("Selecciona el centro");
        estado = espiral;
    }
}
//---------------------------------------------------------------------------

void __fastcall TGLForm2D::Seleccionar1Click(TObject *Sender)
{
//Seleccionar poli_linea
}
//---------------------------------------------------------------------------

void __fastcall TGLForm2D::Borrar1Click(TObject *Sender)
{
// Borrar poli_linea    
}
//---------------------------------------------------------------------------

void __fastcall TGLForm2D::Zoom1Click(TObject *Sender)
{
//Zoom progresivo
    if(FormZoom->pedirZoom(zoom,iteraciones)){
        float der,izq,arriba,abajo;
        der=xRight;
        izq=xLeft;
        arriba=yTop;
        abajo=yBot;
        GLdouble cx=(der+izq)/2.0;
        GLdouble cy=(arriba+abajo)/2.0;
        GLdouble incF=(((GLdouble)zoom/100)-1)/(GLdouble)iteraciones;
        glMatrixMode(GL_PROJECTION);
        for(GLint i=0;i<iteraciones;i++){
            xRight= cx+0.5*(1/(i*incF+1))*(der-izq);
            xLeft= cx+0.5*(1/(i*incF+1))*(izq-der);
            yTop= cy+0.5*(1/(i*incF+1))*(arriba-abajo);
            yBot= cy+0.5*(1/(i*incF+1))*(abajo-arriba);

            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            gluOrtho2D(xLeft,xRight,yBot,yTop);

            escena->setXRight(xRight);
            escena->setXLeft(xLeft);
            escena->setYTop(yTop);
            escena->setYBot(yBot);

            GLScene();
            Sleep(100);
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TGLForm2D::Traslacion1Click(TObject *Sender)
{
//Trasladar el AVE
    estado = trasladar; 
}


//---------------------------------------------------------------------------

void  TGLForm2D::fractalizarK1(DibujoLineas* dibujselec){

         DibujoLineas*  nuevaLista= new DibujoLineas();

         if(dibujselec != NULL){
                dibujselec->getSegmentos()->inicia();
                for(int i=0;i<dibujselec->getSegmentos()->getLongitud();i++){
                        Linea* Laux=dibujselec->getSegmentos()->getActual();
                        Laux->fractalizaK1(nuevaLista);
                        dibujselec->getSegmentos()->avanza();
        }
    }



}


//---------------------------------------------------------------------------

void __fastcall TGLForm2D::K1Click(TObject *Sender)
{
       // if (seleccionado) {
        //           selecto





       // }



//fractal Koch1
}
//---------------------------------------------------------------------------

void __fastcall TGLForm2D::Koch21Click(TObject *Sender)
{
// Fractal Koch2    
}
//---------------------------------------------------------------------------

void __fastcall TGLForm2D::Dragon1Click(TObject *Sender)
{
//Fractal dragon    
}
//---------------------------------------------------------------------------

void __fastcall TGLForm2D::Cortar1Click(TObject *Sender)
{
//Selecionar un area y borrar lo que haya dentro    
}
//---------------------------------------------------------------------------

void __fastcall TGLForm2D::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
 if (estado == trasladar){
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
//--------------------------------------------------------------------------

void __fastcall TGLForm2D::FormMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{

    if(estado == poligono){
           modoPoligono(X,Y);
    }
    if(estado == linea){
           modoLinea(X,Y);
    }
    if(estado == espiral){
           modoEspiral(X,Y);
    }

}
//---------------------------------------------------------------------------


