//---------------------------------------------------------------------------

#ifndef ColorH
#define ColorH

//---------------------------------------------------------------------------

class Color {
     private:
          float rojo, verde, azul;

     public:
          Color();
          Color(Color* c);
          Color(float red, float blue, float green);
          void setRojo(float red);
          void setAzul(float blue);
          void setVerde(float green);
          float getRojo();
          float getAzul();
          float getVerde();
};

#endif

//---------------------------------------------------------------------------
 