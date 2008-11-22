//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("glSkeleton.res");
USEFORM("UFP.cpp", GLForm2D);
USEUNIT("DibujoLineas.cpp");
USEUNIT("Lapiz.cpp");
USEUNIT("Linea.cpp");
USEUNIT("Lista.cpp");
USEUNIT("Nodo.cpp");
USEUNIT("PuntoV2F.cpp");
USEUNIT("Escena.cpp");
USEFORM("UFZoom.cpp", FormZoom);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->CreateForm(__classid(TGLForm2D), &GLForm2D);
         Application->CreateForm(__classid(TFormZoom), &FormZoom);
         Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------
