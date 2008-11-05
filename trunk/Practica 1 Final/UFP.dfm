object GLForm2D: TGLForm2D
  Left = 694
  Top = 178
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
      Caption = 'Tiling'
      OnClick = Tiling1Click
    end
    object Opcional1: TMenuItem
      Caption = 'Opcional'
      object ColorAnidamiento1: TMenuItem
        Caption = 'Color Anidamiento'
        object Activar1: TMenuItem
          Caption = 'Activar'
          OnClick = Activar1Click
        end
        object Desactivar1: TMenuItem
          Caption = 'Desactivar'
          OnClick = Desactivar1Click
        end
      end
      object ElegirColores1: TMenuItem
        Caption = 'Elegir Color y Grosor'
        object Puntos1: TMenuItem
          Caption = 'Color'
          object CentroAVE1: TMenuItem
            Caption = 'Centro AVE'
            OnClick = CentroAVE1Click
          end
          object CentroGravedad1: TMenuItem
            Caption = 'Centro Gravedad'
            OnClick = CentroGravedad1Click
          end
          object Triangulos1: TMenuItem
            Caption = 'Triangulos'
            OnClick = Triangulos1Click
          end
          object Reiniciar1: TMenuItem
            Caption = 'Reiniciar'
            OnClick = Reiniciar1Click
          end
        end
        object Lineas1: TMenuItem
          Caption = 'Grosor'
          object CentroAVE2: TMenuItem
            Caption = 'Centro AVE'
            OnClick = CentroAVE2Click
          end
          object CentroGravedad2: TMenuItem
            Caption = 'Centro Gravedad'
            OnClick = CentroGravedad2Click
          end
          object Triangulos2: TMenuItem
            Caption = 'Triangulos'
            OnClick = Triangulos2Click
          end
          object Reiniciar2: TMenuItem
            Caption = 'Reiniciar'
            OnClick = Reiniciar2Click
          end
        end
      end
      object AnidamientoTotal1: TMenuItem
        Caption = 'Anidamiento Total'
        OnClick = AnidamientoTotal1Click
        object Activar2: TMenuItem
          Caption = 'Activar'
          OnClick = Activar2Click
        end
        object Desactivar2: TMenuItem
          Caption = 'Desactivar'
          OnClick = Desactivar2Click
        end
      end
    end
  end
  object ColorDialog1: TColorDialog
    Ctl3D = True
    Left = 32
  end
end
