//---------------------------------------------------------------------------

#ifndef UFEspiralH
#define UFEspiralH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TFormEspiral : public TForm
{
__published:	// IDE-managed Components
    TLabel *Label1;
    TLabel *Label2;
    TLabel *Label3;
    TLabel *Label4;
    TEdit *Edit1;
    TEdit *Edit2;
    TEdit *Edit3;
    TEdit *Edit4;
    TButton *ButtonAceptar;
    TButton *ButtonCancelar;
    void __fastcall ButtonCancelarClick(TObject *Sender);
    void __fastcall ButtonAceptarClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TFormEspiral(TComponent* Owner);
    bool pedirEspiral(int& num_iter,float& lado_ini,float& incr_lado,int& giro);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormEspiral *FormEspiral;
//---------------------------------------------------------------------------
#endif
