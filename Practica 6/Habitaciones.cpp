//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Habitaciones.h"

//---------------------------------------------------------------------------

Habitacion::Habitacion(int h) {
    nHabitacion = h;
    PV3D* vector;
    if(nHabitacion == 1){ //habitacion amueblada
        objetos = new Lista<Objeto3D>();
        this->matriz = new TAfin();

        //Estanteria
        Estanteria* estanteria = new Estanteria(4, 0.15, 1, 2);
        estanteria->setMatriz(new TAfin());
        vector = new PV3D(0.0, 1.3, 0.0, 1);
        estanteria->getM()->trasladar(vector);
        delete vector;
        objetos->inserta((Objeto3D*)estanteria);

        //Suelo
        Suelo* suelo = new Suelo(2, 2, 0.01, 1, 1, 1,true);
        suelo->setColor(new Color(0.7, 0.2, 0.3));
        suelo->setMatriz(new TAfin());
        objetos->inserta((Objeto3D*)suelo);
         //Pared Izq
        Tablero* paredIzq = new Tablero(0.05, 2, 2, 1, 1, 1);
        paredIzq->setColor(new Color(0.7, 0.5, 0.5));
        paredIzq->setMatriz(new TAfin());
        objetos->inserta((Objeto3D*)paredIzq);
        //Pared Der1
        Tablero* paredDer1 = new Tablero(0.7, 0.05, 2, 1, 1, 1);
        paredDer1->setColor(new Color(0.7, 0.5, 0.5));
        paredDer1->setMatriz(new TAfin());
        objetos->inserta((Objeto3D*)paredDer1);
        //Pared Der3 (inferior)
        Tablero* paredDer3= new Tablero(0.6, 0.05, 0.7, 10, 2, 10);
        paredDer3->setColor(new Color(0.7, 0.5, 0.5));
        paredDer3->setMatriz(new TAfin());
        vector = new PV3D(0.7,0,0,1);
        paredDer3->getM()->trasladar(vector);
        delete vector;
        objetos->inserta((Objeto3D*)paredDer3);
        //Pared Der4 (superior)
        Tablero* paredDer4 = new Tablero(2, 0.05, 0.7, 10, 2, 10);
        paredDer4->setColor(new Color(0.7, 0.5, 0.5));
        paredDer4->setMatriz(new TAfin());
        vector = new PV3D(0, 1.3,0.0,1);
        paredDer4->getM()->trasladar(vector);
        delete vector;
        objetos->inserta((Objeto3D*)paredDer4);
        //Pared Der2
        Tablero* paredDer2= new Tablero(0.7, 0.05, 2, 1, 1, 1);
        paredDer2->setColor(new Color(0.7, 0.5, 0.5));
        paredDer2->setMatriz(new TAfin());
        vector = new PV3D(1.3, 0.0,0.0,1);
        paredDer2->getM()->trasladar(vector);
        delete vector;
        objetos->inserta((Objeto3D*)paredDer2);

        //Television
        Television* tv = new Television(0.05, 0.8, 0.5, 1, 1, 1,false);
        tv->setMatriz(new TAfin());
        vector = new PV3D(0.05,0.9,0.8,1);
        tv->getM()->trasladar(vector);
        delete vector;
        objetos->inserta((Objeto3D*)tv);

         //Lampara
        Lampara* lampara = new Lampara(0.15,0.05,0.2,20,20);
        lampara->setMatriz(new TAfin());
        lampara->setColor(new Color(1.0, 0, 1.0));
        vector = new PV3D(1.3,1.8,1,1);
        (lampara->getM())->trasladar(vector);
        delete vector;
        vector = new PV3D(1.0,0.0,0.0,1);
        (lampara->getM())->rotar(270, vector);
        delete vector;
        objetos->inserta((Objeto3D*)lampara);

         //Muebles
        Muebles* muebles = new Muebles();
        objetos->inserta((Objeto3D*)muebles);
        
    }
    else {
        this->matriz = new TAfin();
        vector = new PV3D(2, 0.0, 0.0, 1);
        matriz->trasladar(vector);
        delete vector;
        objetos = new Lista<Objeto3D>();

        //Suelo
        Suelo* suelo = new Suelo(2, 2, 0.01, 10, 2, 10,false);
        suelo->setColor(new Color(0, 0.2, 0.3));
        suelo->setMatriz(new TAfin());
        objetos->inserta((Objeto3D*)suelo);
        //Pared Der1
        Tablero* paredDer = new Tablero(0.5, 0.05, 2, 10, 2, 10);
        paredDer->setColor(new Color(0, 0.9, 0.5));
        paredDer->setMatriz(new TAfin());
        objetos->inserta((Objeto3D*)paredDer);
        //Pared Der3 (inferior)
        Tablero* paredDer3 = new Tablero(1, 0.05, 0.9, 10, 2, 10);
        paredDer3->setColor(new Color(0, 0.9, 0.5));
        paredDer3->setMatriz(new TAfin());
        vector = new PV3D(0.5,0,0.0,1);
        paredDer3->getM()->trasladar(vector);
        delete vector;
        objetos->inserta((Objeto3D*)paredDer3);
        //Pared Der4 (superior)
        Tablero* paredDer4= new Tablero(2, 0.05, 0.5, 10, 2, 10);
        paredDer4->setColor(new Color(0, 0.9, 0.5));
        paredDer4->setMatriz(new TAfin());
        vector = new PV3D(0, 1.5,0.0,1);
        paredDer4->getM()->trasladar(vector);
        delete vector;
        objetos->inserta((Objeto3D*)paredDer4);
        //Pared Der2
        Tablero* paredDer2 = new Tablero(0.5, 0.05, 2, 10, 2, 10);
        paredDer2->setColor(new Color(0, 0.9, 0.5));
        paredDer2->setMatriz(new TAfin());
        vector = new PV3D(1.5, 0.0,0.0,1);
        paredDer2->getM()->trasladar(vector);
        delete vector;
        objetos->inserta((Objeto3D*)paredDer2);
        //Pared Izq1
        Tablero* paredIzq1 = new Tablero(0.05, 0.4, 2, 10, 2, 10);
        paredIzq1->setColor(new Color(0, 0.9, 0.5));
        paredIzq1->setMatriz(new TAfin());
        vector = new PV3D(0.0,0.0,1.6,1);
        paredIzq1->getM()->trasladar(vector);
        delete vector;
        objetos->inserta((Objeto3D*)paredIzq1);
        //Pared Izq2
        Tablero* paredIzq2 = new Tablero(0.05, 0.7, 2, 10, 2, 10);
        paredIzq2->setColor(new Color(0, 0.9, 0.5));
        paredIzq2->setMatriz(new TAfin());
        objetos->inserta((Objeto3D*)paredIzq2);
        //Pared Izq3 (superior)
        Tablero* paredIzq3 = new Tablero(0.05, 0.9, 0.3, 10, 2, 10);
        paredIzq3->setColor(new Color(0, 0.9, 0.5));
        paredIzq3->setMatriz(new TAfin());
        vector = new PV3D(0,1.7,0.7,1);
        paredIzq3->getM()->trasladar(vector);
        delete vector;
        objetos->inserta((Objeto3D*)paredIzq3);

        //Puerta
        Puerta* puerta = new Puerta(0.05, 0.9, 1.7, 1, 1, 1,true,0);
        puerta->setMatriz(new TAfin());
        vector = new PV3D(0.0, 0.0, 0.7, 1);
        puerta->getM()->trasladar(vector);
        delete vector;
        vector = new PV3D(0.0, 1.0, 0.0, 1);
        puerta->getM()->rotar(90,vector);
        delete vector;
        objetos->inserta((Objeto3D*)puerta);
    }
}

//---------------------------------------------------------------------------

void Habitacion::dibujar() {
    glMatrixMode(GL_MODELVIEW);
    objetos->inicia();
    Objeto3D* aux;
    for(int i=0;i<objetos->getLongitud();i++){
        aux = objetos->getActual();
        if( typeid(*aux) == typeid(Suelo)){
            if(((Suelo*)aux)->getLado()){// Es el suelo de la izquierda
                glEnable(GL_TEXTURE_2D);
                glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
                glBindTexture(GL_TEXTURE_2D, 0);
                glBegin(GL_QUADS);
                    glTexCoord2f(0.0,0.0);
                    glVertex3f(0.0,0.01,2.0);

                    glTexCoord2f(0.0,1.0);
                    glVertex3f(0.0,0.01,0.0);

                    glTexCoord2f(1.0,1.0);
                    glVertex3f(2.0,0.01,0.0);

                    glTexCoord2f(1.0,0.0);
                    glVertex3f(2.0,0.01,2.0);
                glEnd();
                glDisable(GL_TEXTURE_2D);
            }
            else{ // Es el suelo de la derecha
                glEnable(GL_TEXTURE_2D);
                glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
                glBindTexture(GL_TEXTURE_2D, 1);
                glBegin(GL_QUADS);
                    glTexCoord2f(0.0,0.0);
                    glVertex3f(0.0,0.01,2.0);

                    glTexCoord2f(0.0,1.0);
                    glVertex3f(0.0,0.01,0.0);

                    glTexCoord2f(1.0,1.0);
                    glVertex3f(2.0,0.01,0.0);

                    glTexCoord2f(1.0,0.0);
                    glVertex3f(2.0,0.01,2.0);
                glEnd();
                glDisable(GL_TEXTURE_2D);
            }
        }
        if( typeid(*aux) == typeid(Television)){
            if(((Television*)aux)->getEncendida()){ // televisión encendida
                glEnable(GL_TEXTURE_2D);
                glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
                glBindTexture(GL_TEXTURE_2D, 2);
                glBegin(GL_QUADS);
                    glTexCoord2f(0.0,0.0);
                    glVertex3f(0.13,1.0,1.6);

                    glTexCoord2f(0.0,1.0);
                    glVertex3f(0.13,1.39,1.6);

                    glTexCoord2f(1.0,1.0);
                    glVertex3f(0.13,1.39,0.85);

                    glTexCoord2f(1.0,0.0);
                    glVertex3f(0.13,1.0,0.85);
                glEnd();
                glDisable(GL_TEXTURE_2D);
            }
            else{// televisión apagada
                glEnable(GL_TEXTURE_2D);
                glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
                glBindTexture(GL_TEXTURE_2D, 3);
                glBegin(GL_QUADS);
                    glTexCoord2f(0.0,0.0);
                    glVertex3f(0.13,1.0,1.6);

                    glTexCoord2f(0.0,1.0);
                    glVertex3f(0.13,1.39,1.6);

                    glTexCoord2f(1.0,1.0);
                    glVertex3f(0.13,1.39,0.85);

                    glTexCoord2f(1.0,0.0);
                    glVertex3f(0.13,1.0,0.85);
                glEnd();
                glDisable(GL_TEXTURE_2D);
            }
        }
        glPushMatrix();
    	    glMultMatrixd(aux->getM()->getMatriz());
            aux->dibujar();
        glPopMatrix();
        objetos->avanza();
    }
}

//---------------------------------------------------------------------------

Habitacion::~Habitacion() {
    if(objetos != NULL){
        objetos->inicia();
        for(int i=0;i<objetos->getLongitud();i++){
            objetos->eliminaActual();
            objetos->avanza();
        }
        delete objetos;
        objetos = NULL;
        delete matriz;
    }
}

//---------------------------------------------------------------------------

void Habitacion::cambiaTV(){
     if(objetos != NULL){
        objetos->inicia();
        Objeto3D* aux;
        for(int i=0;i<objetos->getLongitud();i++){
            aux = objetos->getActual();
            if( typeid(*aux) == typeid(Television)){
                ((Television*)aux)->cambiaTV();
            }
            objetos->avanza();
        }
     }
}

//---------------------------------------------------------------------------

bool Habitacion::cambiaPuerta(){
     if(objetos != NULL){
        objetos->inicia();
        Objeto3D* aux;
        for(int i=0;i<objetos->getLongitud();i++){
            aux = objetos->getActual();
            if( typeid(*aux) == typeid(Puerta)){
                return (((Puerta*)aux)->cambiaPuerta());
            }
            objetos->avanza();
        }
     }
    return false;
}

//---------------------------------------------------------------------------

void Habitacion::escalarLampara(PV3D* v) {

if(objetos != NULL){
	objetos->inicia();
	Objeto3D* aux;
	for(int i=0;i<objetos->getLongitud();i++){
		aux = objetos->getActual();
		if( typeid(*aux) == typeid(Lampara)){
			aux->getM()->escalar(v);
		}
		objetos->avanza();
	}
}
          
}

//---------------------------------------------------------------------------

void Habitacion::escalarMuebles(PV3D* v) {

if(objetos != NULL){
	objetos->inicia();
	Objeto3D* aux;
	for(int i=0;i<objetos->getLongitud();i++){
		aux = objetos->getActual();
		if( typeid(*aux) == typeid(Muebles)){
			aux->getM()->escalar(v);
		}
		objetos->avanza();
	}
}
          
}

//---------------------------------------------------------------------------

void Habitacion::trasladarLampara(PV3D* v) {

if(objetos != NULL){
	objetos->inicia();
	Objeto3D* aux;
	for(int i=0;i<objetos->getLongitud();i++){
		aux = objetos->getActual();
		if( typeid(*aux) == typeid(Lampara)){
			aux->getM()->trasladar(v);
		}
		objetos->avanza();
	}
}
          
}

//---------------------------------------------------------------------------

void Habitacion::trasladarMuebles(PV3D* v) {

if(objetos != NULL){
	objetos->inicia();
	Objeto3D* aux;
	for(int i=0;i<objetos->getLongitud();i++){
		aux = objetos->getActual();
		if( typeid(*aux) == typeid(Muebles)){
			aux->getM()->trasladar(v);
		}
		objetos->avanza();
	}
}
          
}

//---------------------------------------------------------------------------

void Habitacion::rotarLampara(PV3D* v,int grados) {

if(objetos != NULL){
	objetos->inicia();
	Objeto3D* aux;
	for(int i=0;i<objetos->getLongitud();i++){
		aux = objetos->getActual();
		if( typeid(*aux) == typeid(Lampara)){
			aux->getM()->rotar(grados,v);
		}
		objetos->avanza();
	}
}

}

//---------------------------------------------------------------------------

void Habitacion::rotarMuebles(PV3D* v,int grados) {

if(objetos != NULL){
	objetos->inicia();
	Objeto3D* aux;
	for(int i=0;i<objetos->getLongitud();i++){
		aux = objetos->getActual();
		if( typeid(*aux) == typeid(Muebles)){
			aux->getM()->rotar(grados,v);
		}
		objetos->avanza();
	}
}

}

//---------------------------------------------------------------------------

float Habitacion::getAncho(){
        if(objetos != NULL){
                    objetos->inicia();
                    Objeto3D* aux;
                    for(int i=0;i<objetos->getLongitud();i++){
                        aux = objetos->getActual();
                        if( typeid(*aux) == typeid(Suelo)){
                            return ((Suelo*)aux)->getAncho();
                        }
                        objetos->avanza();
                    }
                }
        return -1;
}

//---------------------------------------------------------------------------

#pragma package(smart_init)



