object FormPoligono: TFormPoligono
  Left = 210
  Top = 178
  Width = 431
  Height = 221
  Caption = 'Datos Poligono'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 56
    Top = 32
    Width = 146
    Height = 24
    Caption = 'Numero de lados'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Label2: TLabel
    Left = 56
    Top = 72
    Width = 145
    Height = 24
    Caption = 'Logitud del lado'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Edit1: TEdit
    Left = 248
    Top = 32
    Width = 121
    Height = 21
    TabOrder = 0
  end
  object Edit2: TEdit
    Left = 248
    Top = 72
    Width = 121
    Height = 21
    TabOrder = 1
  end
  object ButtonAceptar: TButton
    Left = 104
    Top = 136
    Width = 75
    Height = 25
    Caption = 'Aceptar'
    TabOrder = 2
    OnClick = ButtonAceptarClick
  end
  object ButtonCacelar: TButton
    Left = 248
    Top = 136
    Width = 75
    Height = 25
    Caption = 'Cancelar'
    TabOrder = 3
    OnClick = ButtonCacelarClick
  end
end
