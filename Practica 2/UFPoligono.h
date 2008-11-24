//---------------------------------------------------------------------------

#ifndef UFPoligonoH
#define UFPoligonoH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TFormPoligono : public TForm
{
__published:	// IDE-managed Components
    TLabel *Label1;
    TEdit *Edit1;
    TLabel *Label2;
    TEdit *Edit2;
    TButton *ButtonAceptar;
    TButton *ButtonCacelar;
    void __fastcall ButtonCacelarClick(TObject *Sender);
    void __fastcall ButtonAceptarClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TFormPoligono(TComponent* Owner);
    bool pedirPoligono(int& numLados, int& longLados);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormPoligono *FormPoligono;
//---------------------------------------------------------------------------
#endif
