object GLForm2D: TGLForm2D
  Left = 286
  Top = 146
  Width = 408
  Height = 454
  Caption = 'Formulario Principal'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  OnKeyDown = FormKeyDown
  OnPaint = FormPaint
  OnResize = FormResize
  PixelsPerInch = 96
  TextHeight = 13
  object MainMenu1: TMainMenu
    object Anidar1: TMenuItem
      Caption = 'Anidar'
      OnClick = Anidar1Click
    end
    object Acercar1: TMenuItem
      Caption = 'Acercar'
      OnClick = Acercar1Click
    end
    object Alejar1: TMenuItem
      Caption = 'Alejar'
      OnClick = Alejar1Click
    end
    object Trasladar1: TMenuItem
      Caption = 'Trasladar'
      OnClick = Trasladar1Click
    end
    object Centrar1: TMenuItem
      Caption = 'Centrar'
      OnClick = Centrar1Click
    end
    object Tilling1: TMenuItem
      Caption = 'Tilling'
      OnClick = Tilling1Click
    end
    object Opcional1: TMenuItem
      Caption = 'Opcional'
      object ColorAnidamiento1: TMenuItem
        Caption = 'Color Anidamiento'
      end
      object ElegirColores1: TMenuItem
        Caption = 'Elegir Colores'
      end
      object AnidamientoTotal1: TMenuItem
        Caption = 'Anidamiento Total'
      end
    end
  end
  object ColorDialog1: TColorDialog
    Ctl3D = True
    Left = 32
  end
end
