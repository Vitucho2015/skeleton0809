object FDatos: TFDatos
  Left = 384
  Top = 159
  Width = 403
  Height = 326
  Caption = 'Datos'
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
    Left = 96
    Top = 40
    Width = 16
    Height = 24
    Caption = 'X'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label2: TLabel
    Left = 96
    Top = 88
    Width = 14
    Height = 24
    Caption = 'Y'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label3: TLabel
    Left = 96
    Top = 136
    Width = 14
    Height = 24
    Caption = 'Z'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label4: TLabel
    Left = 72
    Top = 176
    Width = 68
    Height = 24
    Caption = 'Ángulo'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object BOk: TButton
    Left = 72
    Top = 224
    Width = 97
    Height = 25
    Caption = 'Aceptar'
    TabOrder = 0
    OnClick = BOkClick
  end
  object BCancel: TButton
    Left = 240
    Top = 224
    Width = 97
    Height = 25
    Caption = 'Cancelar'
    TabOrder = 1
    OnClick = BCancelClick
  end
  object EditX: TEdit
    Left = 152
    Top = 40
    Width = 121
    Height = 21
    TabOrder = 2
  end
  object EditY: TEdit
    Left = 152
    Top = 88
    Width = 121
    Height = 21
    TabOrder = 3
  end
  object EditZ: TEdit
    Left = 152
    Top = 136
    Width = 121
    Height = 21
    TabOrder = 4
  end
  object EditAngulo: TEdit
    Left = 152
    Top = 176
    Width = 121
    Height = 21
    TabOrder = 5
  end
end
