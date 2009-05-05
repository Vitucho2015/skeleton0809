//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UFDatos.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TFDatos *FDatos;
//---------------------------------------------------------------------------
__fastcall TFDatos::TFDatos(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TFDatos::BCancelClick(TObject *Sender)
{
    ModalResult=mrCancel;
}
//---------------------------------------------------------------------------
void __fastcall TFDatos::BOkClick(TObject *Sender)
{
    try{
        EditX->Text.ToDouble();
        EditY->Text.ToDouble();
        EditZ->Text.ToDouble();
        ModalResult=mrOk;
    }
    catch(Exception &e){
        ShowMessage("Valor no valido.");
    }

}
//---------------------------------------------------------------------------

bool TFDatos::pedirDatos(double& coorX,double& coorY,double& coorZ){
    bool valido = false;
    ShowModal();
    if (ModalResult==mrOk){
        coorX = EditX->Text.ToDouble();
        coorY = EditY->Text.ToDouble();
        coorZ = EditZ->Text.ToDouble();
        valido = true;
    }
    return valido;
}

//---------------------------------------------------------------------------

bool TFDatos::pedirDatos(double& coorX,double& coorY,double& coorZ,int& grados){
    bool valido = false;
    ShowModal();
    if (ModalResult==mrOk){
        coorX = EditX->Text.ToDouble();
        coorY = EditY->Text.ToDouble();
        coorZ = EditZ->Text.ToDouble();
        grados = EditAngulo->Text.ToInt();
        valido = true;
    }
    return valido;
}


//---------------------------------------------------------------------------
