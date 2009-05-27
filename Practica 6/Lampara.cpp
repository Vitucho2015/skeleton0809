//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Lampara.h"

//---------------------------------------------------------------------------

Lampara::Lampara(GLfloat nRadioBase,GLfloat nRadioCima,GLfloat nAltura,GLint nNPlados, GLint nNQCapas){

    objetos = new Lista<Objeto3D>();

    Cilindro* c = new Cilindro(nRadioBase,nRadioCima,nAltura,nNPlados,nNQCapas);
    c->setColor(new Color(1.0, 0, 1.0));
    c->setMatriz(new TAfin());
    objetos->inserta((Objeto3D*)c);




}

//---------------------------------------------------------------------------

Lampara::~Lampara(){
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

void Lampara::dibujar(){
    glMatrixMode(GL_MODELVIEW);
    objetos->inicia();
    Objeto3D* aux;
    for(int i=0;i<objetos->getLongitud();i++){
        aux = objetos->getActual();
        glPushMatrix();
    	    glMultMatrixd(aux->getM()->getMatriz());

            GLfloat p [] = {0.0 , 0.0 , 0.0, 1.0};
            glLightfv(GL_LIGHT1, GL_POSITION, p);
            GLfloat d [] = {0.0, 0.0,-1.0};
            glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, d);

            aux->dibujar();
        glPopMatrix();
        objetos->avanza();
    }
}

//---------------------------------------------------------------------------

#pragma package(smart_init)
