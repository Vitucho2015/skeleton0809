//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UFTiling.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TUFT *UFT;
//---------------------------------------------------------------------------
__fastcall TUFT::TUFT(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TUFT::BOkClick(TObject *Sender)
{
    int nCol = StrToInt(ETiling->Text);
    if (nCol > 0) ModalResult=mrOk;
    else
        ShowMessage("Error: Introduce un valor válido!");

}
//---------------------------------------------------------------------------

void __fastcall TUFT::BCancelClick(TObject *Sender)
{
        ModalResult=mrCancel;
}
//---------------------------------------------------------------------------
bool TUFT::pedirNumColumnas(int& nCol)
{
    bool valido = false;
    ShowModal();
    if (ModalResult==mrOk)
    {
        nCol = StrToInt(ETiling->Text);
        valido = true;
    }
    return valido;
}
//---------------------------------------------------------------------------

