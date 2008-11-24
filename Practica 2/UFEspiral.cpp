//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UFEspiral.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormEspiral *FormEspiral;
//---------------------------------------------------------------------------
__fastcall TFormEspiral::TFormEspiral(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------

bool TFormEspiral::pedirEspiral(int& num_iter,int& lado_ini,int& incr_lado,int& giro)
{
    bool valido = false;
    ShowModal();
    if (ModalResult==mrOk){
        num_iter = StrToInt(Edit1->Text);
        lado_ini = StrToInt(Edit2->Text);
        incr_lado = StrToInt(Edit3->Text);
        giro = StrToInt(Edit4->Text);
        valido = true;
    }
    return valido;
}
//---------------------------------------------------------------------------
void __fastcall TFormEspiral::ButtonCancelarClick(TObject *Sender)
{
    ModalResult=mrCancel;    
}
//---------------------------------------------------------------------------

void __fastcall TFormEspiral::ButtonAceptarClick(TObject *Sender)
{
    num_iter = StrToInt(Edit1->Text);
    lado_ini = StrToInt(Edit2->Text);
    incr_lado = StrToInt(Edit3->Text);
    giro = StrToInt(Edit4->Text);
    if ((num_iter > 0)&&(giro > 0)&&(lado_ini > 0.0)&&(incr_lado > 0.0)){
        ModalResult=mrOk;
    }
    else{
        ShowMessage("Error: Introduce valores válidos!");
    }
}
//---------------------------------------------------------------------------

