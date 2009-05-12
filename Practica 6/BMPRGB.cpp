//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "BMPRGB.h"

//---------------------------------------------------------------------------

BMPRGB::BMPRGB(){
    pixmap = NULL;
    nCols = 0;
    nRows = 0;
}

//---------------------------------------------------------------------------

BMPRGB::~BMPRGB(){
    delete []pixmap;
}

//---------------------------------------------------------------------------

bool BMPRGB::cargarBMP(String ruta){
    Graphics::TBitmap* AuxBMP = new Graphics::TBitmap();
    AuxBMP->LoadFromFile(ruta);
    if(AuxBMP->Empty){
        delete AuxBMP;
        return false;
    }
    else{
        recoloca(AuxBMP);
        delete AuxBMP;
        return true;
    }
}

//----------------------------------------------------------------------------

void BMPRGB::recoloca(Graphics::TBitmap* auxBMP){
   delete pixmap;
   pixmap = new ColorRGB[auxBMP->Width*auxBMP->Height];
   nCols = auxBMP->Width;
   nRows = auxBMP->Height;
   int count, i, j;
   for(i=0; i<nRows; i++){
    for(j=0; j<nCols; j++){
        count = i*nCols + j;
        pixmap[count][0] = GetRValue(auxBMP->Canvas->Pixels[j][nRows - i - 1]);
        pixmap[count][1] = GetGValue(auxBMP->Canvas->Pixels[j][nRows - i - 1]);
        pixmap[count][2] = GetBValue(auxBMP->Canvas->Pixels[j][nRows - i - 1]) ;
    }
   }
}

//---------------------------------------------------------------------------

#pragma package(smart_init)
