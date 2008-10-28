//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("glSkeleton.res");
USEFORM("UFP.cpp", GLForm2D);
USEFORM("UFTiling.cpp", UFT);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->CreateForm(__classid(TGLForm2D), &GLForm2D);
         Application->CreateForm(__classid(TUFT), &UFT);
         Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------
