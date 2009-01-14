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

	//Inicialización del volumen de vista
	xRight=250.0; xLeft=-xRight;
	yTop=xRight; yBot=-yTop;
	//Radio del volumen de vista == 1

	//Inicialización del puerto de vista
	ClientWidth=500;
	ClientHeight=500;
	RatioViewPort=1.0;

	//Iniciamos el sistema en modo Tonto
    //modoListo = false;
    modoListo = true;
    //Radio de la pelota;
    radio = 10;

    /*
    PuntoV2F* p1 = new PuntoV2F(1,1);
    PuntoV2F* p2 = new PuntoV2F(2,1);
    PuntoV2F* p3 = new PuntoV2F(2,2);
    PuntoV2F* p4 = new PuntoV2F(3,2);

    bool ttt;
    tSegmento* tg = new tSegmento();

    PuntoV2F* ccc = new PuntoV2F();

    ccc = tg->inteseccionSegmento(p1,p2,p3,p4);
    ttt = tg->cortaSegmento(p1,p2,p3,p4);
           */

	//Inicialmente el reloj desactivado
	reloj->Enabled = false;
	//Creamos la lista de obstaculos
	obstaculos = new Lista<tObstaculo>();
	//Creamos y colocamos los obstaculos
	crearEscenario();
	//Creamos punto de salida
	pSalida = new PuntoV2F(-150,150);
	//Inicializamos el sistema aleatorio
	randomize();
 }

//---------------------------------------------------------------------------

 void __fastcall TGLForm2D::SetPixelFormatDescriptor()
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
			0,0,0
	};
	int PixelFormat = ChoosePixelFormat(hdc, &pfd);
	SetPixelFormat(hdc, PixelFormat, &pfd);
 }

//---------------------------------------------------------------------

 void __fastcall TGLForm2D::FormResize(TObject *Sender)
 {
	//Se actualiza puerto de vista y su radio
	if ((ClientWidth<=1)||(ClientHeight<=1)){
			ClientWidth=500;
			ClientHeight=500;
			RatioViewPort=1.0;
	}else RatioViewPort= (float)ClientWidth/(float)ClientHeight;

	glViewport(0,0,ClientWidth,ClientHeight);

	//Se actualiza el volumen de vista
	//para que su radio coincida con ratioViewPort
	GLfloat RatioVolVista=xRight/yTop;

	if (RatioVolVista>=RatioViewPort){
		//Aumentamos yTop-yBot
		GLfloat yTop_aux= (yTop+yBot+(xRight-xLeft)/RatioViewPort)/2.0;
		GLfloat yBot_aux=(yTop+yBot-(xRight-xLeft)/RatioViewPort)/2.0;
		yTop = yTop_aux;
		yBot = yBot_aux;
	}else{
		//Aumentamos xRight-xLeft
		GLfloat xRight_aux =(xRight+xLeft+RatioViewPort*(yTop-yBot))/2.0;
		GLfloat xLeft_aux =(xRight+xLeft-RatioViewPort*(yTop-yBot))/2.0;
		xRight = xRight_aux;
		xLeft = xLeft_aux;
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

	//Dibujamos el punto de partida del objeto móvil
	if(pSalida != NULL){
		glPointSize(4);
		glBegin(GL_POINTS);
			glColor3f(0,0,1);
			glVertex2i(pSalida->getX(),pSalida->getY());
		glEnd();
	}

	//Dibujamos escenario
	if(obstaculos != NULL){
		obstaculos->inicia();
		for (int i=0;i<obstaculos->getLongitud();i++){
			tObstaculo* obstaculo = obstaculos->getActual();
			obstaculo->draw();
			obstaculos->avanza();
		}
	}

	//Dibujamos pelota
	if (pelota != NULL){
		pelota->draw();
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

	//Eliminamos los objetos creados
	
	if (pelota != NULL){
		delete pelota;
		pelota = NULL;
	}

	if (obstaculos != NULL){
		delete obstaculos;
		obstaculos = NULL;
	}

	if(pSalida != NULL){
		delete pSalida;
		pSalida = NULL;
	}
 }

//---------------------------------------------------------------------------

 void __fastcall TGLForm2D::MSalirClick(TObject *Sender)
 {
    Close();
 }
 
//---------------------------------------------------------------------------


 void TGLForm2D::crearEscenario()
 {
    if(obstaculos != NULL){
        delete obstaculos;
    }
    
    obstaculos = new Lista<tObstaculo>();
	//Creamos las paredes
   	crearParedes(modoListo);

	//Creamos los obstaculos
	crearObstaculos(modoListo);
 }

//---------------------------------------------------------------------------

 void TGLForm2D::crearParedes(bool modo)
 {
	//Creamos paredes
	if(modo == false){ // Modo penetracion
		//Izquierda
		PuntoV2F** verIzq = new PuntoV2F*[4];
	    verIzq[0] = new PuntoV2F(-250,-250);
	    verIzq[1] = new PuntoV2F(-250,250);
	    verIzq[2] = new PuntoV2F(-260,250);
	    verIzq[3] = new PuntoV2F(-260,-250);
		tConvexo* paredIzq = new tConvexo(4,verIzq);
		obstaculos->inserta(paredIzq);

		//Superior
		PuntoV2F** verSup = new PuntoV2F*[4];
		verSup[0] = new PuntoV2F(-250,250);
		verSup[1] = new PuntoV2F(250,250);
		verSup[2] = new PuntoV2F(250,260);
		verSup[3] = new PuntoV2F(-250,260);

		tConvexo* paredSup = new tConvexo(4,verSup);
		obstaculos->inserta(paredSup);

		//Inferior
		PuntoV2F** verInf = new PuntoV2F*[4];
		verInf[0] = new PuntoV2F(-250,-260);
		verInf[1] = new PuntoV2F(250,-260);
		verInf[2] = new PuntoV2F(250,-250);
		verInf[3] = new PuntoV2F(-250,-250);

		tConvexo* paredInf = new tConvexo(4,verInf);
		obstaculos->inserta(paredInf);

		//Derecha
		PuntoV2F** verDer = new PuntoV2F*[4];
		verDer[0] = new PuntoV2F(260,-250);
		verDer[1] = new PuntoV2F(260,250);
		verDer[2] = new PuntoV2F(250,250);
		verDer[3] = new PuntoV2F(250,-250);
		tConvexo* paredDer = new tConvexo(4,verDer);
		obstaculos->inserta(paredDer);
	}
	else{ // Modo no penetracion
        //Izquierda
		PuntoV2F** verIzq = new PuntoV2F*[4];
	    verIzq[0] = new PuntoV2F(-250,-250);
	    verIzq[1] = new PuntoV2F(-250,250);
	    verIzq[2] = new PuntoV2F(-260,250);
	    verIzq[3] = new PuntoV2F(-260,-250);
		tObstaculoRecubierto* paredIzq = new tObstaculoRecubierto(4,verIzq,0,radio);
		obstaculos->inserta(paredIzq);

		//Superior
		PuntoV2F** verSup = new PuntoV2F*[4];
		verSup[0] = new PuntoV2F(-250,250);
		verSup[1] = new PuntoV2F(250,250);
		verSup[2] = new PuntoV2F(250,260);
		verSup[3] = new PuntoV2F(-250,260);

		tObstaculoRecubierto* paredSup = new tObstaculoRecubierto(4,verSup,0,radio);
		obstaculos->inserta(paredSup);

		//Inferior
		PuntoV2F** verInf = new PuntoV2F*[4];
		verInf[0] = new PuntoV2F(-250,-260);
		verInf[1] = new PuntoV2F(250,-260);
		verInf[2] = new PuntoV2F(250,-250);
		verInf[3] = new PuntoV2F(-250,-250);

		tObstaculoRecubierto* paredInf = new tObstaculoRecubierto(4,verInf,0,radio);
		obstaculos->inserta(paredInf);

		//Derecha
		PuntoV2F** verDer = new PuntoV2F*[4];
		verDer[0] = new PuntoV2F(260,-250);
		verDer[1] = new PuntoV2F(260,250);
		verDer[2] = new PuntoV2F(250,250);
		verDer[3] = new PuntoV2F(250,-250);
		tObstaculoRecubierto* paredDer = new tObstaculoRecubierto(4,verDer,0,radio);
		obstaculos->inserta(paredDer);

	}
 }

//---------------------------------------------------------------------------

 void TGLForm2D::crearPelota()
 {
	if (pelota != NULL){
		delete pelota;
		pelota = NULL;
	}

	//Indicamos posicion inicial
	PuntoV2F* posicion = new PuntoV2F(pSalida);

	//Sentido inicial de la pelota aleatorio
	//(valores con rango entre [-10,10])
	int x = random(21)-10;
	int y = random(21)-10;
    
	PuntoV2F* sentido = new PuntoV2F(x,y);

	pelota = new tPelota(radio, posicion, sentido);
 }

//---------------------------------------------------------------------------

 void __fastcall TGLForm2D::relojTimer(TObject *Sender)
 {
	reloj->Enabled=false;
	avanzar();
	GLScene();
	Caption=" Rebotes Num: "+IntToStr(numRebotes);
	reloj->Enabled=true;
 }

//---------------------------------------------------------------------------

 void TGLForm2D::avanzar()
 {
    bool corte = false;
	double tIn;
	PuntoV2F* normal;

	//Vemos si ha chocado con algún obstaculo
	obstaculos->inicia();
	int i = 0;
    while((!corte)&&(i<obstaculos->getLongitud())){
		tObstaculo* obstaculo = obstaculos->getActual();
		corte = obstaculo->colisionVsPelota(pelota,tIn,normal);
		obstaculos->avanza();
		i++;
	}

	//Procesamos los obstaculos restantes por si se produce una colision a la vez
   	/*int j = i;
	bool otroCorte = false;
	double tIn2;
	PuntoV2F* normal2;
	while(((corte)&&(!otroCorte))&&(j<obstaculos->getLongitud())){
		tObstaculo* obstaculo2 = obstaculos->getActual();
		otroCorte = obstaculo2->colisionVsPelota(pelota,tIn2,normal2);
		obstaculos->avanza();
		j++;
	} */
	if(!corte){ //No hay colisión
		pelota->avanza();
	}
	else{
		/*if ((corte)&&(otroCorte)){ //Doble colision
			normal2->restar(normal);
			normal2->escalar(0.5);
			pelota->avanzaYRebota(tIn2,normal2);
			delete normal;
		}
		else{ //Colision simple */
        	pelota->avanzaYRebota(tIn,normal);
		//}
		numRebotes++;
	}
 }

//---------------------------------------------------------------------------

 void TGLForm2D::crearObstaculos(bool modo)
 {
    if(modo == false){ //Modo penetración
		PuntoV2F* centro;

		//Triangulo
		centro = new PuntoV2F(130,130);
		tConvexo* poligono1 = new tConvexo(centro,3,45);
		obstaculos->inserta(poligono1);
		delete centro;

		//Triangulo
		centro = new PuntoV2F(-250,100);
		tConvexo* poligono2 = new tConvexo(centro,3,40);
		obstaculos->inserta(poligono2);
		delete centro;

		//Rectangulo
		PuntoV2F** vertices = new PuntoV2F*[4];
		PuntoV2F* p1 = new PuntoV2F(-160,-160);
		PuntoV2F* p2 = new PuntoV2F(-100,-160);
		PuntoV2F* p3 = new PuntoV2F(-100,-130);
		PuntoV2F* p4 = new PuntoV2F(-160,-130);
		vertices[0]=p1;
		vertices[1]=p2;
		vertices[2]=p3;
		vertices[3]=p4;
		tConvexo* poligono3 = new tConvexo(4,vertices);
		obstaculos->inserta(poligono3);

		//Cuadrado
		centro = new PuntoV2F(0,250);
		tConvexo* poligono4 = new tConvexo(centro,4,50);
		obstaculos->inserta(poligono4);
		delete centro;

		//Hexagono
		centro = new PuntoV2F(250,250);
		tConvexo* poligono5 = new tConvexo(centro,6,50);
		obstaculos->inserta(poligono5);
		delete centro;

		//Cuadrado
		centro = new PuntoV2F(-250,-250);
		tConvexo* poligono6 = new tConvexo(centro,4,50);
		obstaculos->inserta(poligono6);
		delete centro;
        
        //Segmento
        PuntoV2F** verticesAux = new PuntoV2F*[2];
			PuntoV2F* p1Aux = new PuntoV2F(0,-160);
		PuntoV2F* p2Aux = new PuntoV2F(100,-150);
        //PuntoV2F* p1Aux = new PuntoV2F(100,0);
		//PuntoV2F* p2Aux = new PuntoV2F(100,-160);
        verticesAux[0] = p1Aux;
        verticesAux[1] = p2Aux;
        tSegmento* segmento1 = new tSegmento(2,verticesAux);
        obstaculos->inserta(segmento1);

        //Segmento
        verticesAux = new PuntoV2F*[2];
        p1Aux = new PuntoV2F(100,40);
		p2Aux = new PuntoV2F(150,-100);
        verticesAux[0] = p1Aux;
        verticesAux[1] = p2Aux;
        tSegmento* segmento2 = new tSegmento(2,verticesAux);
        obstaculos->inserta(segmento2);    
	}
	else{//Modo no penetracion
		//ShowMessage("Aun en construcción");
        //Rectangulo
	   	/*PuntoV2F** vertices = new PuntoV2F*[4];
		PuntoV2F* p1 = new PuntoV2F(-160,-160);
		PuntoV2F* p2 = new PuntoV2F(-100,-160);
		PuntoV2F* p3 = new PuntoV2F(-100,-130);
		PuntoV2F* p4 = new PuntoV2F(-160,-130);
		vertices[0]=p1;
		vertices[1]=p2;
		vertices[2]=p3;
		vertices[3]=p4;
		tObstaculoRecubierto* poligono3 = new tObstaculoRecubierto(4,vertices, 0,radio);
		obstaculos->inserta(poligono3);
        //ShowMessage(poligono3->getNumVertices());
        */
        PuntoV2F* centro;

		//Triangulo
		centro = new PuntoV2F(130,130);
		tObstaculoRecubierto* poligono1 = new tObstaculoRecubierto(centro,3,45,radio);
		obstaculos->inserta(poligono1);
		delete centro;

		//Triangulo
		centro = new PuntoV2F(-250,100);
		tObstaculoRecubierto* poligono2 = new tObstaculoRecubierto(centro,3,40,radio);
		obstaculos->inserta(poligono2);
		delete centro;

		//Rectangulo
		PuntoV2F** vertices = new PuntoV2F*[4];
		PuntoV2F* p1 = new PuntoV2F(-160,-160);
		PuntoV2F* p2 = new PuntoV2F(-100,-160);
		PuntoV2F* p3 = new PuntoV2F(-100,-130);
		PuntoV2F* p4 = new PuntoV2F(-160,-130);
		vertices[0]=p1;
		vertices[1]=p2;
		vertices[2]=p3;
		vertices[3]=p4;
		tObstaculoRecubierto* poligono3 = new tObstaculoRecubierto(4,vertices,0,radio);
		obstaculos->inserta(poligono3);

		//Cuadrado
		centro = new PuntoV2F(0,250);
		tObstaculoRecubierto* poligono4 = new tObstaculoRecubierto(centro,4,50,radio);
		obstaculos->inserta(poligono4);
		delete centro;

   		//Cuadrado
		centro = new PuntoV2F(250,250);
		tObstaculoRecubierto* poligono5 = new tObstaculoRecubierto(centro,6,50,radio);
		obstaculos->inserta(poligono5);
		delete centro;
   
		//Cuadrado
		centro = new PuntoV2F(-250,-250);
		tObstaculoRecubierto* poligono6 = new tObstaculoRecubierto(centro,4,50,radio);
		obstaculos->inserta(poligono6);
		delete centro;

        //Segmento
        PuntoV2F** verticesAux = new PuntoV2F*[2];
		PuntoV2F* p1Aux = new PuntoV2F(0,-160);
		PuntoV2F* p2Aux = new PuntoV2F(100,-150);
        verticesAux[0] = p1Aux;
        verticesAux[1] = p2Aux;
        tObstaculoRecubierto* segmento1 = new tObstaculoRecubierto(2,verticesAux, 1,radio);
        obstaculos->inserta(segmento1);

        //Segmento
        verticesAux = new PuntoV2F*[2];
		p1Aux = new PuntoV2F(100,40);
		p2Aux = new PuntoV2F(150,-100);
        verticesAux[0] = p1Aux;
        verticesAux[1] = p2Aux;
        tObstaculoRecubierto* segmento2 = new tObstaculoRecubierto(2,verticesAux, 2,radio);
        obstaculos->inserta(segmento2);
	}

 }

//---------------------------------------------------------------------------

void __fastcall TGLForm2D::Tonto1Click(TObject *Sender)
{
    modoListo = false;
	//Creamos la pelota
	crearPelota();
	//Creamos el escenario
	crearEscenario();
	//Iniciamos contador y lo mostramos
	numRebotes = 0;
	Caption=" Rebotes Num: "+numRebotes;
	//Activamos el reloj
	reloj->Enabled = true;
	//Repintamos
	GLScene();
}
//---------------------------------------------------------------------------

void __fastcall TGLForm2D::Listo1Click(TObject *Sender)
{
    modoListo = true;  
	//Creamos la pelota
	crearPelota();
	//Creamos el escenario
	crearEscenario();
	//Iniciamos contador y lo mostramos
	numRebotes = 0;
	Caption=" Rebotes Num: "+numRebotes;
	//Activamos el reloj
	reloj->Enabled = true;
	//Repintamos
	GLScene();	
}
//---------------------------------------------------------------------------


