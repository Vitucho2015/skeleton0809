object FormZoom: TFormZoom
  Left = 218
  Top = 141
  Width = 404
  Height = 237
  Caption = 'Datos Zoom'
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
    Left = 40
    Top = 32
    Width = 50
    Height = 24
    Caption = 'Zoom'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Label2: TLabel
    Left = 40
    Top = 88
    Width = 91
    Height = 24
    Caption = 'Iteraciones'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object EditZoom: TEdit
    Left = 144
    Top = 32
    Width = 129
    Height = 21
    TabOrder = 0
  end
  object EditIter: TEdit
    Left = 144
    Top = 88
    Width = 129
    Height = 21
    TabOrder = 1
  end
  object ButtonAceptar: TButton
    Left = 88
    Top = 144
    Width = 75
    Height = 25
    Caption = 'Aceptar'
    TabOrder = 2
    OnClick = ButtonAceptarClick
  end
  object ButtonCancel: TButton
    Left = 224
    Top = 144
    Width = 75
    Height = 25
    Caption = 'Cancelar'
    TabOrder = 3
    OnClick = ButtonCancelClick
  end
end
