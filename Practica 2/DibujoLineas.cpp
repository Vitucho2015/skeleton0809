//---------------------------------------------------------------------------

 #include <vcl.h>
 #pragma hdrstop
 #include "DibujoLineas.h"

//---------------------------------------------------------------------------

 DibujoLineas::DibujoLineas()
 {
        segmentos = new Lista<Linea>;
        seleccionado = false;
 }

//---------------------------------------------------------------------------

 DibujoLineas::DibujoLineas(DibujoLineas* dL)
 {
        segmentos = new Lista<Linea>;
        dL->segmentos->inicia();
        for (int i=0;i<dL->segmentos->getLongitud();i++)
        {
                Linea* linea = new Linea(dL->segmentos->getActual());
                segmentos->inserta(linea);
                dL->segmentos->avanza();
        }
        seleccionado = false;
 }



//-------------------------------------------------

 DibujoLineas::DibujoLineas(Punto* p, int numIteraciones,int longIni,int incrLado,int incrAng)
 {
        segmentos = new Lista<Linea>;
        Punto* pun = new Punto(p);
        Lapiz* lapiz = new Lapiz(pun, 0);
        for(int i=1;i<=numIteraciones;i++){
                Punto* z = lapiz->getPosicion();
                Punto* a = new Punto(z);
                lapiz->avanzar(longIni,false);
                z = lapiz->getPosicion();
                Punto* b = new Punto(z);
                lapiz->turn(incrAng);
                longIni+=incrLado;
                Linea* linea = new Linea(a,b);
                segmentos->inserta(linea);
        }
        delete lapiz;
        seleccionado = false;
 }

//-------------------------------------------------

 DibujoLineas::DibujoLineas(Punto* centro,int nLados,int lado)
 {
        segmentos = new Lista<Linea>;
        float alfa = 360/nLados;
        float radio = lado / sin((alfa*3.141592)/180);

        Punto* origen = new Punto(centro->getX()+radio,centro->getY());
        Lapiz* lapiz = new Lapiz(origen,0);

        for (int i=1;i<=nLados;i++){
                Punto* z = lapiz->getPosicion();
                Punto* a = new Punto(z);
                //Calculamos el punto
                Punto* punto = new Punto(
                  centro->getX()+radio*cos((i*alfa*3.141592)/180),
                  centro->getY()+radio*sin((i*alfa*3.141592)/180));
                //Trazamos linea hasta punto
                lapiz->lineTo(punto);
                z = lapiz->getPosicion();
                Punto* b = new Punto(z);
                Linea* linea = new Linea(a,b);
                insertaLinea(linea);
        }
        delete lapiz;
        seleccionado = false;
 }

//-------------------------------------------------

 DibujoLineas::DibujoLineas(Punto* centro,float angIni, float angArco, float radio, int nLados)
 {
        segmentos = new Lista<Linea>;
        seleccionado = false;

        float incrAng = angArco / float (nLados);

        float x = centro->getX() + radio*cos((angIni*3.1416)/180);
        float y = centro->getY() + radio*sin((angIni*3.1416)/180);
        
        for (int i=1;i<=nLados;i++)
        {
		Punto* a = new Punto(x,y);
                x = centro->getX() + radio*cos((((angIni+i*incrAng)*3.1416)/180));
                y = centro->getY() + radio*sin((((angIni+i*incrAng)*3.1416)/180));
                Punto* b = new Punto(x,y);
                Linea* linea = new Linea(a,b);
                segmentos->inserta(linea);
        }
 }

//-------------------------------------------------

 DibujoLineas::~DibujoLineas()
 {
        if (segmentos!=NULL){
                delete segmentos;
        }
 }

//-------------------------------------------------

 void DibujoLineas::insertaLinea(Linea* linea)
 {
         segmentos->inserta(linea);
 }

//-------------------------------------------------

 void DibujoLineas::draw()
 {
        segmentos->inicia();
        for (int i=0;i<segmentos->getLongitud();i++){
                Linea* linea = segmentos->getActual();
                linea->draw();
                segmentos->avanza();
        }
 }

//-------------------------------------------------

 bool DibujoLineas::recorte(Punto* puntoA, Punto* puntoB)
 {
        bool borrado = true;
        segmentos->inicia();
        int longitud = segmentos->getLongitud();
        for (int i=0;i<longitud;i++){
                Linea* linea = segmentos->getActual();
                if(!linea->recorte(puntoA, puntoB))
                {
                        segmentos->eliminaActual();
                }else{
                        segmentos->avanza();
                }
        }
        if (segmentos->getLongitud()==0){
                borrado = false;
        }
        return borrado;
 }

//-------------------------------------------------

 bool DibujoLineas::seleccionar(Punto* punto)
 {
        segmentos->inicia();
        int i = 0;
        bool encontrado = false;
        seleccionado = false;
        while ((i<segmentos->getLongitud())&&(!encontrado)){
                Linea* linea = segmentos->getActual();
                if(linea->estaPuntoVertices(punto))
                {
                        encontrado = true;
                        seleccionado = true;
                }

                segmentos->avanza();
                i++;
        }
        return encontrado;
 }

//-------------------------------------------------

 bool DibujoLineas::getSeleccionado()
 {
        return seleccionado;
 }

//-------------------------------------------------

 void DibujoLineas::setSeleccionado(bool selec)
 {
        seleccionado = selec;
 }

//-------------------------------------------------

 bool DibujoLineas::estaPuntoDentro(Punto* punto)
 {
        segmentos->inicia();
        int i = 0;
        bool dentro = true;
        while ((i<segmentos->getLongitud())&&(dentro)){
                Linea* linea = segmentos->getActual();
                if(!linea->estaPuntoIzq(punto))
                {
                        dentro = false;
                }

                segmentos->avanza();
                i++;
        }
        return dentro;
 }

//-------------------------------------------------

 Lista<Linea>* DibujoLineas::getSegmentos()
 {
        return segmentos;
 }



//-------------------------------------------------

 void DibujoLineas::girarConCentro(Punto* centro,float ang)
 {
        Lista<Linea>* seg = getSegmentos();
        seg->inicia();
        for (int i=0;i<seg->getLongitud();i++){
                Linea* linea = seg->getActual();
                linea->girar(centro,ang);
                seg->avanza();
        }
 }

//-------------------------------------------------

 void DibujoLineas::mover(Punto* desplazamiento)
 {
        segmentos->inicia();
        for (int i=0;i<segmentos->getLongitud();i++){
                Linea* linea = segmentos->getActual();
                linea->mover(desplazamiento);
                segmentos->avanza();
        }
 }

//-------------------------------------------------

 void DibujoLineas::buscarInfIzqYSupDer(Punto*& sd,Punto*& ii)
 {
        Lista<Linea>* seg = getSegmentos();
        seg->inicia();
        for (int i=0;i<seg->getLongitud();i++){
                Linea* linea = seg->getActual();
                linea->buscarInfIzqYSupDer(sd,ii);
                seg->avanza();
        }
 }

//---------------------------------------------------------------------------

 #pragma package(smart_init)
