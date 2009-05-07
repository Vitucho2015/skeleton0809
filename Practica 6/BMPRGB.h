//---------------------------------------------------------------------------

#ifndef BMPRGBH
#define BMPRGBH

#include "Color.h"
#include <gl\gl.h>
#include <gl\glu.h>

typedef GLubyte ColorRGB[3];

//---------------------------------------------------------------------------

class BMPRGB{
    private:
        int nCols;
        int nRows;
        ColorRGB* pixmap;

    public:
        BMPRGB();
        ~BMPRGB();
        GLint getCols(){return nCols;};
        GLint getRows(){return nRows;};
        ColorRGB* getBMP(){return pixmap;};
        bool cargarBMP(AnsiString);
        void recoloca(Graphics::TBitmap*);

};

//---------------------------------------------------------------------------

#endif
