object GLForm2D: TGLForm2D
  Left = 214
  Top = 112
  Width = 408
  Height = 434
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
  OnPaint = FormPaint
  OnResize = FormResize
  PixelsPerInch = 96
  TextHeight = 13
  object MainMenu1: TMainMenu
    object Anidar1: TMenuItem
      Caption = 'Anidar'
    end
    object Acercar1: TMenuItem
      Caption = 'Acercar'
    end
    object Alejar1: TMenuItem
      Caption = 'Alejar'
    end
    object Trasladar1: TMenuItem
      Caption = 'Trasladar'
    end
    object Centrar1: TMenuItem
      Caption = 'Centrar'
    end
    object Tilling1: TMenuItem
      Caption = 'Tilling'
    end
  end
end
