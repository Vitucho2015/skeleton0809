//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Habitaciones.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

//---------------------------------------------------------------------------

Habitacion::Habitacion(int h) {
    nHabitacion = h;
    PV3D* vector;
    if(nHabitacion == 1){ //habitacion amueblada
        objetos = new Lista<Objeto3D>();
        //
        Muebles* muebles = new Muebles();
        objetos->inserta((Objeto3D*)muebles);
        //
        Cilindro* lampara = new Cilindro(0.3,0.1,0.2,20,20);
        lampara->setMatriz(new TAfin());
        lampara->setColor(new Color(0.0, 1.0, 1.0));
        vector = new PV3D(1.1,2.2,1.0,1);
        (lampara->getM())->trasladar(vector);
        delete vector;
        vector = new PV3D(1.0,0.0,0.0,1);
        (lampara->getM())->rotar(270, vector);
        delete vector;
        objetos->inserta((Objeto3D*)lampara);
        this->matriz = new TAfin();
    }
    else {
        this->matriz = new TAfin();
        vector = new PV3D(2.5, 0.0, 0.0, 1);
        matriz->trasladar(vector);
        delete vector;
        objetos = new Lista<Objeto3D>();
        Tablero* suelo = new Tablero(2.5, 2.5, 0.01, 10, 2, 10); //suelo
        suelo->setColor(new Color(0.2, 0, 0.3));
        suelo->setMatriz(new TAfin());
        objetos->inserta((Objeto3D*)suelo);
    }    
    /*
    PV3D* vector;
    if(nHabitacion==1){ //habitacion amueblada
        lampara = new Cilindro(0.3,0.1,0.2,20,20);
        lampara->setMatriz(new TAfin());
        lampara->setColor(new Color(0.0, 1.0, 1.0));

        vector = new PV3D(1.1,2.2,1.0,1);
        (lampara->getM())->trasladar(vector);
        delete vector;
        vector = new PV3D(1.0,0.0,0.0,1);
        (lampara->getM())->rotar(270, vector);
        delete vector;

        muebles = new Muebles();

        numObjetos = 8; //paredes, suelo, cuadro y estanterias
        this->matriz = new TAfin();
        objetos = new Objeto3D*[numObjetos];

        objetos[0] = new Estanteria(3,0.2, 0.6, 4, 8);
        objetos[0]->setMatriz(new TAfin());
        vector = new PV3D(0.0, 1.0, 0.0, 1);
        objetos[0]->getM()->trasladar(vector);
        delete vector;

        objetos[1] = new Tablero(2.5, 2.5, 0.01, 10, 2, 10); //suelo
        objetos[1]->setColor(new Color(0.5, 0, 0.5));
        objetos[1]->setMatriz(new TAfin());

        //crear paredes
        objetos[2] = new Tablero(0.2, 2.5, 2.5, 10, 2, 10);
        objetos[2]->setColor(new Color(0.5, 0, 0.5));
        objetos[2]->setMatriz(new TAfin());

        objetos[3] = new Tablero(0.7, 0.2, 2.5, 10, 2, 10);
        objetos[3]->setColor(new Color(0.5, 0, 0.5));
        objetos[3]->setMatriz(new TAfin());

        objetos[4] = new Tablero(0.7, 0.2, 2.5, 10, 2, 10);
        objetos[4]->setColor(new Color(0.5, 0, 0.5));
        objetos[4]->setMatriz(new TAfin());
        vector = new PV3D(1.8, 0.0,0.0,1);
        objetos[4]->getM()->trasladar(vector);
        delete vector;

        objetos[5] = new Tablero(2.5, 0.2, 0.7, 10, 2, 10);
        objetos[5]->setColor(new Color(0.5, 0, 0.5));
        objetos[5]->setMatriz(new TAfin());

        objetos[6] = new Tablero(2.5, 0.2, 0.7, 10, 2, 10);
        objetos[6]->setColor(new Color(0.5, 0, 0.5));
        objetos[6]->setMatriz(new TAfin());
        vector = new PV3D(0, 1.8,0.0,1);
        objetos[6]->getM()->trasladar(vector);
        delete vector;


        objetos[7] = new Tablero(0.1, 0.8, 0.8, 10, 2, 10);  //cuadro
        objetos[7]->setColor(new Color(0.5, 0.5, 0.5));
        objetos[7]->setMatriz(new TAfin());
        vector = new PV3D(0.2, 1.5,1.0,1);
        objetos[7]->getM()->trasladar(vector);
        delete vector;

    }
    else {
        numObjetos =  9;
        this->matriz = new TAfin();
        vector = new PV3D(2.5, 0.0, 0.0, 1);
        matriz->trasladar(vector);
        delete vector;

        objetos = new Objeto3D*[numObjetos];
        //crear paredes
        objetos[8] = new Tablero(2.5, 2.5, 0.01, 10, 2, 10); //suelo
        objetos[8]->setColor(new Color(0.2, 0, 0.3));
        objetos[8]->setMatriz(new TAfin());

        objetos[1] = new Tablero(0.7, 0.2, 2.5, 10, 2, 10);
        objetos[1]->setColor(new Color(0.2, 0, 0.3));
        objetos[1]->setMatriz(new TAfin());

        objetos[2] = new Tablero(0.7, 0.2, 2.5, 10, 2, 10);
        objetos[2]->setColor(new Color(0.2, 0, 0.3));
        objetos[2]->setMatriz(new TAfin());
        vector = new PV3D(1.8, 0.0,0.0,1);
        objetos[2]->getM()->trasladar(vector);
        delete vector;

        objetos[3] = new Tablero(2.5, 0.2, 0.7, 10, 2, 10);
        objetos[3]->setColor(new Color(0.2, 0, 0.3));
        objetos[3]->setMatriz(new TAfin());

        objetos[4] = new Tablero(2.5, 0.2, 0.7, 10, 2, 10);
        objetos[4]->setColor(new Color(0.2, 0, 0.3));
        objetos[4]->setMatriz(new TAfin());
        vector = new PV3D(0, 1.8,0.0,1);
        objetos[4]->getM()->trasladar(vector);
        delete vector;

        objetos[5] = new Tablero(0.2, 0.8, 2.5, 10, 2, 10);
        objetos[5]->setColor(new Color(0.2, 0, 0.3));
        objetos[5]->setMatriz(new TAfin());

        objetos[6] = new Tablero(0.2, 0.8, 2.5, 10, 2, 10);
        objetos[6]->setColor(new Color(0.2, 0, 0.3));
        objetos[6]->setMatriz(new TAfin());
        vector = new PV3D(0.0, 0.0,1.7,1);
        objetos[6]->getM()->trasladar(vector);
        delete vector;

        objetos[7] = new Tablero(0.2, 2.5, 0.3, 10, 2, 10);
        objetos[7]->setColor(new Color(0.2, 0, 0.3));
        objetos[7]->setMatriz(new TAfin());
        vector = new PV3D(0.0, 2.2,0.0,1);
        objetos[7]->getM()->trasladar(vector);
        delete vector;

        objetos[0] = new Puerta();
        objetos[0]->setMatriz(new TAfin());
        vector = new PV3D(0.0, 0.0, 0.8, 1);
        objetos[0]->getM()->trasladar(vector);
        delete vector;
        vector = new PV3D(0.0, 1.0, 0.0, 1);
        objetos[0]->getM()->rotar(45,vector);
        delete vector;
    }
    */
}

//---------------------------------------------------------------------------

void Habitacion::dibujar() {
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
    /*if(nHabitacion ==1) {
        muebles->dibujar();
        glPushMatrix();
		    glMultMatrixd(lampara->getM()->getMatriz());
		    lampara->dibujar();
	    glPopMatrix();
    }
    for(int i= 0; i < numObjetos;i++) {
        glPushMatrix();
		    glMultMatrixd(objetos[i]->getM()->getMatriz());
		    objetos[i]->dibujar();
	    glPopMatrix();
    }
    */
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
    /*
    if(nHabitacion == 1) {
        delete lampara;
        delete muebles;
    }
    delete objetos[0];
    for(int i = 1; i< numObjetos;i++) {
        delete objetos[i]->getColor();
        delete objetos[i]->getM();
        delete objetos[i];
    }
    delete []objetos;
    delete matriz;
    */
}

//---------------------------------------------------------------------------




 