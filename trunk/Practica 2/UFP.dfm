object GLForm2D: TGLForm2D
  Left = 284
  Top = 120
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
  OnKeyDown = FormKeyDown
  OnMouseDown = FormMouseDown
  OnMouseMove = FormMouseMove
  OnMouseUp = FormMouseUp
  OnPaint = FormPaint
  OnResize = FormResize
  PixelsPerInch = 96
  TextHeight = 13
  object MainMenu1: TMainMenu
    Left = 368
    object Dibujar1: TMenuItem
      Caption = 'Dibujar'
      object Lineas1: TMenuItem
        Caption = 'Lineas'
        OnClick = Lineas1Click
      end
      object Poligono1: TMenuItem
        Caption = 'Poligono'
        OnClick = Poligono1Click
      end
      object Espiral1: TMenuItem
        Caption = 'Espiral'
        OnClick = Espiral1Click
      end
    end
    object Editar1: TMenuItem
      Caption = 'Editar'
      object Seleccionar1: TMenuItem
        Caption = 'Seleccionar'
        OnClick = Seleccionar1Click
      end
      object Borrar1: TMenuItem
        Caption = 'Borrar'
        OnClick = Borrar1Click
      end
    end
    object Explorar1: TMenuItem
      Caption = 'Explorar'
      object Zoom1: TMenuItem
        Caption = 'Zoom'
        OnClick = Zoom1Click
      end
      object Traslacion1: TMenuItem
        Caption = 'Traslacion'
        OnClick = Traslacion1Click
      end
    end
    object Fractales1: TMenuItem
      Caption = 'Fractales'
      object K1: TMenuItem
        Caption = 'Koch1'
        OnClick = K1Click
      end
      object Koch21: TMenuItem
        Caption = 'Koch2'
        OnClick = Koch21Click
      end
      object Dragon1: TMenuItem
        Caption = 'Dragon'
        OnClick = Dragon1Click
      end
    end
    object Cortar1: TMenuItem
      Caption = 'Cortar'
      OnClick = Cortar1Click
    end
    object Opcional1: TMenuItem
      Caption = 'Opcional'
    end
  end
end
