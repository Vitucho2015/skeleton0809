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
    selecto = NULL;

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

//---------------------------------------------------------------------------

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

//---------------------------------------------------------------------------

 void TGLForm2D::desactivarModos(){
        estado = nada;
 }

//---------------------------------------------------------------------------

 void TGLForm2D::modoSeleccion(int X, int Y){
    if (puntoAnt != NULL){
        delete puntoAnt;
    }
    //Transforma a coordenadas en la escena
    puntoAnt = devCoordenada(X,Y);
    //selecto = escena->seleccion(puntoAnt->getX(),puntoAnt->getY());
    escena->seleccion(puntoAnt->getX(),puntoAnt->getY());
    GLScene();
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

      return angulo;
 }

//---------------------------------------------------------------------------

 void TGLForm2D::modoLinea(int X, int Y)
 {
              if (!esOrigen){ //Primer punto de la linea

                if (puntoAnt!=NULL){
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
//Dibujar poli_lineas
        desactivarModos();
    estado=linea;
    esOrigen=false;
    PLCreada=false;
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
    estado = seleccion;
}

//---------------------------------------------------------------------------

void __fastcall TGLForm2D::Borrar1Click(TObject *Sender)
{

    {


       bool encontrado = false;
        DibujoLineas* djaux= new DibujoLineas();

        escena->getDibujos()->inicia();

        while (!encontrado&&(escena->getDibujos()->getActual()!=NULL))
        {

             if (escena->getDibujos()->getActual()->getSeleccionado()){
                        encontrado=true;


                        escena->getDibujos()->eliminaActual();

                }
             escena->getDibujos()->avanza();
         }
         if (!encontrado)ShowMessage("Seleccione algo!");

        GLScene();

}




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

void __fastcall TGLForm2D::K1Click(TObject *Sender)
{
//fractal Koch1

       bool encontrado = false;
        DibujoLineas* djaux= new DibujoLineas();

        escena->getDibujos()->inicia();

        while (!encontrado&&(escena->getDibujos()->getActual()!=NULL))
        {

             if (escena->getDibujos()->getActual()->getSeleccionado()){
                        encontrado=true;
                        djaux = new DibujoLineas(escena->getDibujos()->getActual());
                        fractalizarK1(djaux);
                        escena->getDibujos()->eliminaActual();
                        escena->getDibujos()->inserta(djaux);
                }
             escena->getDibujos()->avanza();
         }
         if (!encontrado)ShowMessage("Seleccione algo!");

        GLScene();

}

//---------------------------------------------------------------------------

void __fastcall TGLForm2D::Koch21Click(TObject *Sender)
{
//fractal Koch1

       bool encontrado = false;
        DibujoLineas* djaux= new DibujoLineas();

        escena->getDibujos()->inicia();

        while (!encontrado&&(escena->getDibujos()->getActual()!=NULL))
        {

             if (escena->getDibujos()->getActual()->getSeleccionado()){
                        encontrado=true;
                        djaux = new DibujoLineas(escena->getDibujos()->getActual());
                        fractalizarK2(djaux);
                        escena->getDibujos()->eliminaActual();
                        escena->getDibujos()->inserta(djaux);
                }
             escena->getDibujos()->avanza();
         }
         if (!encontrado)ShowMessage("Seleccione algo!");

        GLScene();

}

//---------------------------------------------------------------------------

void __fastcall TGLForm2D::Dragon1Click(TObject *Sender)
{
//fractal Koch1

       bool encontrado = false;
        DibujoLineas* djaux= new DibujoLineas();

        escena->getDibujos()->inicia();

        while (!encontrado&&(escena->getDibujos()->getActual()!=NULL))
        {

             if (escena->getDibujos()->getActual()->getSeleccionado()){
                        encontrado=true;
                        djaux = new DibujoLineas(escena->getDibujos()->getActual());
                        fractalizarDRAGON(djaux);
                        escena->getDibujos()->eliminaActual();
                        escena->getDibujos()->inserta(djaux);
                }
             escena->getDibujos()->avanza();
         }
         if (!encontrado)ShowMessage("Seleccione algo!");

        GLScene();

}

//---------------------------------------------------------------------------

void __fastcall TGLForm2D::Cortar1Click(TObject *Sender)
{
//Selecionar un area y borrar lo que haya dentro
    desactivarModos();
    estado = cortar;
    esOrigen=false;
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
    if(estado == seleccion){
           modoSeleccion(X,Y);
    }
    if(estado == cortar){
        if(origen != NULL){
            delete origen;
        }
        origenCorte = devCoordenada(X,Y);
    }
    if(estado != seleccion){
        if(selecto != NULL){
            selecto->setSeleccionado(false);
        }
    }
}

//---------------------------------------------------------------------------

void __fastcall TGLForm2D::FormMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
    if(Shift.Contains(ssLeft)){
        if(estado == cortar && origenCorte!=NULL){
             if (destinoCorte != NULL){
                delete destinoCorte;
             }
             //Transforma a coordenadas en la escena
            destinoCorte = devCoordenada(X,Y);
            escena->enMarca(origenCorte,destinoCorte);

            GLScene();
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TGLForm2D::FormMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{

    bool noVacio = true;
    if(estado == cortar){
        estado = nada;

        if ((origenCorte->getX()<destinoCorte->getX())&&(origenCorte->getY()<destinoCorte->getY()))
                {
                        noVacio = escena->recorte(origenCorte,destinoCorte);
                }

                if ((origenCorte->getX()>destinoCorte->getX())&&(origenCorte->getY()>destinoCorte->getY()))
                {
                        noVacio = escena->recorte(destinoCorte,origenCorte);
                }

                if ((origenCorte->getX()>destinoCorte->getX())&&(origenCorte->getY()<destinoCorte->getY()))
                {
                        float y1 = origenCorte->getY();
                        float y2 = destinoCorte->getY();
                        destinoCorte->setY(y1);
                        origenCorte->setY(y2);
                        noVacio = escena->recorte(destinoCorte,origenCorte);
                }

                if ((origenCorte->getX()<destinoCorte->getX())&&(origenCorte->getY()>destinoCorte->getY()))
                {
                        float y1 = origenCorte->getY();
                        float y2 = destinoCorte->getY();
                        destinoCorte->setY(y1);
                        origenCorte->setY(y2);
                        noVacio = escena->recorte(origenCorte,destinoCorte);
                }

                if(!noVacio)
                {
                        ShowMessage("La escena se ha vaciado por completo");
                }
         esOrigen=false;
        glFlush();
        GLScene();
    }
}
//---------------------------------------------------------------------------

void  TGLForm2D::fractalizarK1(DibujoLineas* &dibujselec){

         DibujoLineas*  nuevaLista= new DibujoLineas();

         if(dibujselec != NULL){

                dibujselec->getSegmentos()->inicia();

                for(int i=0;i<dibujselec->getSegmentos()->getLongitud();i++){

                        Linea* Laux=dibujselec->getSegmentos()->getActual();


                        float i = Laux->getOrigen()->getX();

                        Laux->fractalizaK1(nuevaLista);

                        dibujselec->getSegmentos()->avanza();
        }

      dibujselec=nuevaLista;
    }



}
//---------------------------------------------------------------------------

void  TGLForm2D::fractalizarK2(DibujoLineas* &dibujselec){

         DibujoLineas*  nuevaLista= new DibujoLineas();

         if(dibujselec != NULL){

                dibujselec->getSegmentos()->inicia();

                for(int i=0;i<dibujselec->getSegmentos()->getLongitud();i++){

                        Linea* Laux=dibujselec->getSegmentos()->getActual();


                        float i = Laux->getOrigen()->getX();

                        Laux->fractalizaK2(nuevaLista);

                        dibujselec->getSegmentos()->avanza();
        }

      dibujselec=nuevaLista;
    }



}
//---------------------------------------------------------------------------

void  TGLForm2D::fractalizarDRAGON(DibujoLineas* &dibujselec){

         DibujoLineas*  nuevaLista= new DibujoLineas();

         if(dibujselec != NULL){

                dibujselec->getSegmentos()->inicia();

                for(int i=0;i<dibujselec->getSegmentos()->getLongitud();i++){

                        Linea* Laux=dibujselec->getSegmentos()->getActual();


                        float i = Laux->getOrigen()->getX();

                        Laux->fractalizaDRAGON(nuevaLista);

                        dibujselec->getSegmentos()->avanza();
        }

      dibujselec=nuevaLista;
    }
}


