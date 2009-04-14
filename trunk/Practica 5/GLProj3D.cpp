//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("GLProj3D.res");
USEFORM("GLSkel3D.cpp", GLForm3D);
USEUNIT("Camara.cpp");
USEUNIT("PV3D.cpp");
USEUNIT("Objeto3D.cpp");
USEUNIT("TAfin.cpp");
USEUNIT("Color.cpp");
USEUNIT("ObjetoCompuesto3D.cpp");
USEUNIT("ObjetoCuadrico.cpp");
USEUNIT("Esfera.cpp");
USEUNIT("Cilindro.cpp");
USEUNIT("Malla.cpp");
USEUNIT("Cara.cpp");
USEUNIT("VerticeNormal.cpp");
USEUNIT("Tablero.cpp");
USEUNIT("Muebles.cpp");
USEUNIT("Habitaciones.cpp");
USEUNIT("Escena.cpp");
USEUNIT("Lista.cpp");
USEUNIT("Nodo.cpp");
USEUNIT("Television.cpp");
USEUNIT("Puerta.cpp");
USEUNIT("Copa.cpp");
USEUNIT("MallaPorRevolucion.cpp");
USEUNIT("Mesa.cpp");
USEUNIT("Estanteria.cpp");
USEUNIT("Toro.cpp");
USEUNIT("Silla.cpp");
USEUNIT("Sofa.cpp");
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->CreateForm(__classid(TGLForm3D), &GLForm3D);
         Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------
