//---------------------------------------------------------------------------

#include <vcl.h> 
#pragma hdrstop
USERES("glSkeleton.res");
USEFORM("UFP.cpp", GLForm2D);
USEUNIT("Nodo.cpp");
USEUNIT("Lista.cpp");
USEUNIT("PuntoV2F.cpp");
USEUNIT("tPelota.cpp");
USEUNIT("tObstaculo.cpp");
USEUNIT("tCirculo.cpp");
USEUNIT("tConvexo.cpp");
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->CreateForm(__classid(TGLForm2D), &GLForm2D);
         Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------
