//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UFZoom.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormZoom *FormZoom;
//---------------------------------------------------------------------------
__fastcall TFormZoom::TFormZoom(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TFormZoom::ButtonAceptarClick(TObject *Sender)
{
    try{
        int zoom = StrToInt(EditZoom->Text);
        int iteraciones = StrToInt(EditIter->Text);
        if ((zoom > 0)&&(iteraciones > 0)){
            ModalResult=mrOk;
        }
        else{
            ShowMessage("Error: Introduce un valor válido!");
        }
    } catch(EConvertError &){
        ShowMessage("Introduce un entero");
    }
}
//---------------------------------------------------------------------------

void __fastcall TFormZoom::ButtonCancelClick(TObject *Sender)
{
    ModalResult=mrCancel;    
}
//---------------------------------------------------------------------------
bool TFormZoom::pedirZoom(int& zoom, int& iteraciones)
{
    bool valido = false;
    ShowModal();
    if (ModalResult==mrOk){
        zoom = StrToInt(EditZoom->Text);
        iteraciones = StrToInt(EditIter->Text);
        valido = true;
    }
    return valido;
}
//---------------------------------------------------------------------------
