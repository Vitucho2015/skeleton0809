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
USEFORM("UFEspiral.cpp", FormEspiral);
USEFORM("UFPoligono.cpp", FormPoligono);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->CreateForm(__classid(TGLForm2D), &GLForm2D);
         Application->CreateForm(__classid(TFormZoom), &FormZoom);
         Application->CreateForm(__classid(TFormEspiral), &FormEspiral);
         Application->CreateForm(__classid(TFormPoligono), &FormPoligono);
         Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------
