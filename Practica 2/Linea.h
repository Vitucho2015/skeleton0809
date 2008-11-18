//---------------------------------------------------------------------------

 #ifndef LineaH
 #define LineaH
 #include "Punto.h"
 #include <gl\gl.h>     //Librería OPENGL
 #include <gl\glu.h>
 #include "Lapiz.h"

 class Linea
 {
        private:
                Punto* origen;             //Punto origen
                Punto* destino;            //Punto destino

                //Funciones de implementación interna del recorte
                bool CS(Punto* p1, Punto* p2, Punto* ii, Punto* sd);
                GLbyte codigoCS(Punto* punto, Punto* ii, Punto* sd);
                void recortarDer(Punto*& p1, Punto* p2, Punto* sd);
                void recortarIzq(Punto*& p1, Punto* p2, Punto* ii);
                void recortarSup(Punto*& p1, Punto* p2, Punto* sd);
                void recortarInf(Punto*& p1, Punto* p2, Punto* ii);

        public:
                Linea();
                Linea(Linea* linea);
                Linea(ifstream& f);
                Linea(Punto* puntoOrigen, Punto* puntoDestino);
                ~Linea();
                void setOrigen(Punto* punto);
                Punto* getOrigen();
                void setDestino(Punto* punto);
                Punto* getDestino();
                void draw();
                bool recorte(Punto* puntoA, Punto* puntoB);
                bool estaPuntoVertices(Punto* punto);
                bool estaPuntoIzq(Punto* punto);
                void girar(Punto* centro, float ang);
                bool salvaTxt(ofstream& f);
                void mover(Punto* desplazamiento);
                void buscarInfIzqYSupDer(Punto*& sd,Punto*& ii);
 };

//---------------------------------------------------------------------------

 #endif
