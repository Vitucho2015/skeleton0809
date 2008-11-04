//---------------------------------------------------------------------------

#ifndef UFGrosorH
#define UFGrosorH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TUFG : public TForm
{
 __published:	// IDE-managed Components
        TButton *BOk;
        TButton *BCancel;
        TEdit *EGrosor;
        TLabel *LGrosor;
        void __fastcall BOkClick(TObject *Sender);
        void __fastcall BCancelClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TUFG(TComponent* Owner);
        bool pedirGrosor(float& grosor);
};
//---------------------------------------------------------------------------
extern PACKAGE TUFG *UFG;
//---------------------------------------------------------------------------
#endif
