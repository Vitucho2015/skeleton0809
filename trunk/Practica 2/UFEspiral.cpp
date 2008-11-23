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

bool TFormEspiral::pedirEspiral(int& num_iter,float& lado_ini,float& incr_lado,int& giro)
{
    bool valido = false;
    ShowModal();
    if (ModalResult==mrOk){
        num_iter = StrToInt(Edit1->Text);
        lado_ini = StrToFloat(Edit2->Text);
        incr_lado = StrToFloat(Edit3->Text);
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
    int num_iter = StrToInt(Edit1->Text);
    float lado_ini = StrToFloat(Edit2->Text);
    float incr_lado = StrToFloat(Edit3->Text);
    int giro = StrToInt(Edit4->Text);
    if ((num_iter > 0)&&(giro > 0)&&(lado_ini > 0.0)&&(incr_lado > 0.0)){
        ModalResult=mrOk;
    }
    else{
        ShowMessage("Error: Introduce valores válidos!");
    }
}
//---------------------------------------------------------------------------

