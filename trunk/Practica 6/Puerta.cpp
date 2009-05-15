//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Puerta.h"
#define tope 9

//---------------------------------------------------------------------------

Puerta::Puerta(GLfloat l, GLfloat a, GLfloat g, int divL, int divA, int divG, bool estado,int num){
    //double radioPomo = a/20;
    objetos = new Lista<Objeto3D>();
    //Madero
    Tablero* tablero = new Tablero(l,a,g,divL,divA,divG);
    tablero->setColor(new Color(0.4,0.2,0));
    tablero->setMatriz(new TAfin());
    objetos->inserta((Objeto3D*)tablero);
    /*
    //Situamos los pomos
    PV3D* translacion = new PV3D(0.06,g/2.0,a-0.2,1);
    TAfin* matrizPomo1 = new TAfin();
    matrizPomo1->trasladar(translacion);
    delete translacion;
    translacion = new PV3D(-0.06,g/2.0,a-0.2,1);
    TAfin* matrizPomo2 = new TAfin();
    matrizPomo2->trasladar(translacion);
    delete translacion;
    //Creamos los pomo
    Esfera* pomo1 = new Esfera(radioPomo,20,20);
    pomo1->setColor(new Color(1,1,0));
    pomo1->setMatriz(matrizPomo1);
    objetos->inserta((Objeto3D*)pomo1);
    Esfera* pomo2 = new Esfera(radioPomo,20,20);
    pomo2->setColor(new Color(1,1,0));
    pomo2->setMatriz(matrizPomo2);
    objetos->inserta((Objeto3D*)pomo2);
    */
    abierta = estado;
    numPaso = num;
}

//---------------------------------------------------------------------------

Puerta::~Puerta(){
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

void Puerta::dibujar(){

    glEnable(GL_TEXTURE_2D);
                glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
                glBindTexture(GL_TEXTURE_2D, 4);
                glBegin(GL_QUADS);
                    glTexCoord2f(0.0,0.0);
                    glVertex3f(0.0,0.0,0.0);

                    glTexCoord2f(0.0,1.0);
                    glVertex3f(0.0,1.7,0.0);

                    glTexCoord2f(1.0,1.0);
                    glVertex3f(0.0,1.7,0.9);

                    glTexCoord2f(1.0,0.0);
                    glVertex3f(0.0,0.0,0.9);
                glEnd();
                
                glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
                glBindTexture(GL_TEXTURE_2D, 4);
                glBegin(GL_QUADS);
                    glTexCoord2f(0.0,0.0);
                    glVertex3f(0.05,0.0,0.0);

                    glTexCoord2f(0.0,1.0);
                    glVertex3f(0.05,1.7,0.0);

                    glTexCoord2f(1.0,1.0);
                    glVertex3f(0.05,1.7,0.9);

                    glTexCoord2f(1.0,0.0);
                    glVertex3f(0.05,0.0,0.9);
                glEnd();
                glDisable(GL_TEXTURE_2D);
    glMatrixMode(GL_MODELVIEW);
    objetos->inicia();
    Objeto3D* aux;
    for(int i=0;i<objetos->getLongitud();i++){
        aux = objetos->getActual();
        glPushMatrix();
    	    glMultMatrixd(aux->getM()->getMatriz());
            aux->dibujar();
        glPopMatrix();
        objetos->avanza();
    }           
}

//---------------------------------------------------------------------------

bool Puerta::cambiaPuerta(){
    if(!abierta){
        PV3D* rotacion = new PV3D(0,1,0,1);
        this->getM()->rotar(10, rotacion);
        delete rotacion;
        numPaso++;
        if(numPaso == tope){
            abierta = true;
            numPaso = 0;
            return false;
        }
    }
    else{
        PV3D* rotacion = new PV3D(0,1,0,1);
        this->getM()->rotar(-10, rotacion);
        delete rotacion;
        numPaso++;
        if(numPaso == tope){
            abierta = false;
            numPaso = 0;
            return false;
        }
    }
    return true;
}

//---------------------------------------------------------------------------

#pragma package(smart_init)


