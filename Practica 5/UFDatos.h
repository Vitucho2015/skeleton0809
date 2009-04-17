//---------------------------------------------------------------------------

#ifndef UFDatosH
#define UFDatosH

//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TFDatos : public TForm
{
__published:	// IDE-managed Components
    TLabel *Label1;
    TLabel *Label2;
    TLabel *Label3;
    TButton *BOk;
    TButton *BCancel;
    TEdit *EditX;
    TEdit *EditY;
    TEdit *EditZ;
    TLabel *Label4;
    TEdit *EditAngulo;
    void __fastcall BCancelClick(TObject *Sender);
    void __fastcall BOkClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TFDatos(TComponent* Owner);
    bool pedirDatos(double& coorX,double& coorY,double& coorZ);
    bool pedirDatos(double& coorX,double& coorY,double& coorZ,int& grados);
};
//---------------------------------------------------------------------------
extern PACKAGE TFDatos *FDatos;
//---------------------------------------------------------------------------
#endif
