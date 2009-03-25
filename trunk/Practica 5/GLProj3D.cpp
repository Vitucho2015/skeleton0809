//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("GLProj3D.res");
USEFORM("GLSkel3D.cpp", GLForm3D);
USEUNIT("PV3D.cpp");
USEUNIT("Camara.cpp");
USEUNIT("Habitaciones.cpp");
USEUNIT("Objeto3D.cpp");
USEUNIT("ObjetoCompuesto3D.cpp");
USEUNIT("TAfin.cpp");
USEUNIT("Color.cpp");
USEUNIT("Tablero.cpp");
USEUNIT("Malla.cpp");
USEUNIT("VerticeNormal.cpp");
USEUNIT("Cara.cpp");
USEUNIT("Escena.cpp");
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
