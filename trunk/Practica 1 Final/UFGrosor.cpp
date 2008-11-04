//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UFGrosor.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TUFG *UFG;
//---------------------------------------------------------------------------
__fastcall TUFG::TUFG(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TUFG::BOkClick(TObject *Sender)
{
    float grosor = StrToFloat(EGrosor->Text);
    if (grosor > 0.0) ModalResult=mrOk;
    else
        ShowMessage("Error: Introduce un valor válido!");

}
//---------------------------------------------------------------------------

void __fastcall TUFG::BCancelClick(TObject *Sender)
{
        ModalResult=mrCancel;
}
//---------------------------------------------------------------------------
bool TUFG::pedirGrosor(float& grosor)
{
    bool valido = false;
    ShowModal();
    if (ModalResult==mrOk)
    {
        grosor = StrToFloat(EGrosor->Text);
        valido = true;
    }
    return valido;
}
//---------------------------------------------------------------------------

