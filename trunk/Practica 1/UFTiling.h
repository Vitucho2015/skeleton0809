//---------------------------------------------------------------------------

#ifndef UFTilingH
#define UFTilingH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TUFT : public TForm
{
__published:	// IDE-managed Components
        TButton *BOk;
        TButton *BCancel;
        TEdit *ETiling;
        TLabel *LTiling;
        void __fastcall BOkClick(TObject *Sender);
        void __fastcall BCancelClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TUFT(TComponent* Owner);
        bool pedirNumColumnas(int& nCol);
};
//---------------------------------------------------------------------------
extern PACKAGE TUFT *UFT;
//---------------------------------------------------------------------------
#endif
