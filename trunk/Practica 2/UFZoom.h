//---------------------------------------------------------------------------

#ifndef UFZoomH
#define UFZoomH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TFormZoom : public TForm
{
__published:	// IDE-managed Components
    TEdit *EditZoom;
    TEdit *EditIter;
    TButton *ButtonAceptar;
    TLabel *Label1;
    TLabel *Label2;
    TButton *ButtonCancel;
    void __fastcall ButtonAceptarClick(TObject *Sender);
    void __fastcall ButtonCancelClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TFormZoom(TComponent* Owner);
    bool pedirZoom(int& zoom, int& iteraciones);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormZoom *FormZoom;
//---------------------------------------------------------------------------
#endif
