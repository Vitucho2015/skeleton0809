//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UFPoligono.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormPoligono *FormPoligono;
//---------------------------------------------------------------------------
__fastcall TFormPoligono::TFormPoligono(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormPoligono::ButtonCacelarClick(TObject *Sender)
{
    ModalResult=mrCancel;    
}
//---------------------------------------------------------------------------
void __fastcall TFormPoligono::ButtonAceptarClick(TObject *Sender)
{
    try{
        int numLados = StrToInt(Edit1->Text);
        int longLados = StrToInt(Edit2->Text);
        if ((numLados > 0)&&(longLados > 0)){
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
bool TFormPoligono::pedirPoligono(int& numLados, int& longLados)
{
    bool valido = false;
    ShowModal();
    if (ModalResult==mrOk){
        numLados = StrToInt(Edit1->Text);
        longLados = StrToInt(Edit2->Text);
        valido = true;
    }
    return valido;
}
//---------------------------------------------------------------------------
