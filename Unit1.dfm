object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'BinanceKlines 0709'
  ClientHeight = 378
  ClientWidth = 831
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnCloseQuery = FormCloseQuery
  PixelsPerInch = 96
  TextHeight = 13
  object Button1: TButton
    Left = 8
    Top = 327
    Width = 238
    Height = 45
    Caption = #1053#1072#1095#1072#1090#1100'!'
    TabOrder = 0
    OnClick = Button1Click
  end
  object Memo1: TMemo
    Left = 399
    Top = 8
    Width = 420
    Height = 360
    Lines.Strings = (
      'Kline/Candlestick chart intervals:'
      'm -> minutes; h -> hours; d -> days; w -> weeks; M -> months'
      '    1m'
      '    3m'
      '    5m'
      '    15m'
      '    30m'
      '    1h'
      '    2h'
      '    4h'
      '    6h'
      '    8h'
      '    12h'
      '    1d'
      '    3d'
      '    1w'
      '    1M')
    TabOrder = 1
  end
  object GroupBox1: TGroupBox
    Left = 8
    Top = 8
    Width = 385
    Height = 137
    Caption = #1059#1089#1083#1086#1074#1080#1103
    TabOrder = 2
    object Label1: TLabel
      Left = 16
      Top = 20
      Width = 53
      Height = 13
      Caption = #1048#1085#1090#1077#1088#1074#1072#1083':'
    end
    object Label2: TLabel
      Left = 16
      Top = 50
      Width = 102
      Height = 13
      Caption = #1050#1086#1083#1080#1095#1077#1089#1090#1074#1086' '#1089#1074#1077#1095#1077#1081':'
    end
    object Label3: TLabel
      Left = 16
      Top = 81
      Width = 351
      Height = 13
      Caption = #1055#1088#1086#1075#1088#1077#1089#1089' '#1087#1086#1089#1083#1077#1076#1085#1077#1081' '#1089#1074#1077#1095#1080' '#1076#1086#1083#1078#1077#1085' '#1073#1099#1090#1100' '#1073#1086#1083#1100#1096#1077' '#1089#1088#1077#1076#1085#1077#1075#1086' '#1087#1088#1086#1075#1088#1077#1089#1089#1072
    end
    object Label4: TLabel
      Left = 16
      Top = 100
      Width = 167
      Height = 13
      Caption = #1087#1088#1077#1076#1099#1076#1091#1097#1080#1093' '#1087#1086#1082#1091#1087#1085#1099#1093' '#1089#1074#1077#1095#1077#1081' '#1074
    end
    object Label5: TLabel
      Left = 239
      Top = 100
      Width = 31
      Height = 13
      Caption = #1088#1072#1079'('#1072')'
    end
    object Label6: TLabel
      Left = 175
      Top = 50
      Width = 82
      Height = 13
      Caption = '('#1084#1072#1082#1089#1080#1084#1091#1084' 1000)'
    end
    object Edit1: TEdit
      Left = 75
      Top = 17
      Width = 45
      Height = 21
      TabOrder = 0
      Text = '3m'
    end
    object Edit2: TEdit
      Left = 124
      Top = 47
      Width = 45
      Height = 21
      TabOrder = 1
      Text = '500'
    end
    object Edit3: TEdit
      Left = 189
      Top = 97
      Width = 44
      Height = 21
      TabOrder = 2
      Text = '100'
    end
  end
  object Button2: TButton
    Left = 267
    Top = 327
    Width = 100
    Height = 45
    Caption = #1054#1089#1090#1072#1085#1086#1074#1080#1090#1100
    TabOrder = 3
    OnClick = Button2Click
  end
  object GroupBox2: TGroupBox
    Left = 8
    Top = 151
    Width = 217
    Height = 170
    Caption = #1055#1088#1086#1082#1089#1080' ('#1076#1083#1103' IdHTTP2)'
    TabOrder = 4
    object Label7: TLabel
      Left = 24
      Top = 50
      Width = 41
      Height = 13
      Caption = #1057#1077#1088#1074#1077#1088':'
    end
    object Label8: TLabel
      Left = 24
      Top = 77
      Width = 29
      Height = 13
      Caption = #1055#1086#1088#1090':'
    end
    object Label9: TLabel
      Left = 24
      Top = 104
      Width = 34
      Height = 13
      Caption = #1051#1086#1075#1080#1085':'
    end
    object Label10: TLabel
      Left = 24
      Top = 131
      Width = 41
      Height = 13
      Caption = #1055#1072#1088#1086#1083#1100':'
    end
    object CheckBox1: TCheckBox
      Left = 24
      Top = 22
      Width = 133
      Height = 17
      Caption = #1048#1089#1087#1086#1083#1100#1079#1086#1074#1072#1090#1100' '#1087#1088#1086#1082#1089#1080
      Checked = True
      State = cbChecked
      TabOrder = 0
      OnClick = CheckBox1Click
    end
    object Edit4: TEdit
      Left = 79
      Top = 47
      Width = 88
      Height = 21
      TabOrder = 1
      Text = '196.19.9.32'
    end
    object Edit5: TEdit
      Left = 79
      Top = 74
      Width = 88
      Height = 21
      TabOrder = 2
      Text = '8000'
    end
    object Edit6: TEdit
      Left = 79
      Top = 101
      Width = 88
      Height = 21
      TabOrder = 3
      Text = '7YscLx'
    end
    object Edit7: TEdit
      Left = 79
      Top = 128
      Width = 88
      Height = 21
      TabOrder = 4
      Text = 'UWaag5'
    end
  end
  object IdHTTP1: TIdHTTP
    IOHandler = IdSSLIOHandlerSocketOpenSSL1
    AllowCookies = True
    HandleRedirects = True
    ProxyParams.BasicAuthentication = False
    ProxyParams.ProxyPort = 0
    Request.CacheControl = 'max-age=0'
    Request.Connection = 'keep-alive'
    Request.ContentLength = -1
    Request.ContentRangeEnd = -1
    Request.ContentRangeStart = -1
    Request.ContentRangeInstanceLength = -1
    Request.Accept = 'text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8'
    Request.BasicAuthentication = False
    Request.UserAgent = 
      'Mozilla/5.0 (Windows NT 6.1; Win64; x64) AppleWebKit/537.36 (KHT' +
      'ML, like Gecko) Chrome/66.0.3359.181 Safari/537.36'
    Request.Ranges.Units = 'bytes'
    Request.Ranges = <>
    HTTPOptions = [hoForceEncodeParams]
    Left = 248
    Top = 184
  end
  object IdSSLIOHandlerSocketOpenSSL1: TIdSSLIOHandlerSocketOpenSSL
    MaxLineAction = maException
    Port = 0
    DefaultPort = 0
    SSLOptions.Mode = sslmUnassigned
    SSLOptions.VerifyMode = []
    SSLOptions.VerifyDepth = 0
    Left = 344
    Top = 184
  end
  object IdSSLIOHandlerSocketOpenSSL2: TIdSSLIOHandlerSocketOpenSSL
    MaxLineAction = maException
    Port = 0
    DefaultPort = 0
    SSLOptions.Mode = sslmUnassigned
    SSLOptions.VerifyMode = []
    SSLOptions.VerifyDepth = 0
    Left = 344
    Top = 248
  end
  object IdHTTP2: TIdHTTP
    IOHandler = IdSSLIOHandlerSocketOpenSSL2
    AllowCookies = True
    HandleRedirects = True
    ProxyParams.BasicAuthentication = False
    ProxyParams.ProxyPort = 0
    Request.CacheControl = 'max-age=0'
    Request.Connection = 'keep-alive'
    Request.ContentLength = -1
    Request.ContentRangeEnd = -1
    Request.ContentRangeStart = -1
    Request.ContentRangeInstanceLength = -1
    Request.Accept = 'text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8'
    Request.BasicAuthentication = False
    Request.UserAgent = 
      'Mozilla/5.0 (Windows NT 6.1; Win64; x64) AppleWebKit/537.36 (KHT' +
      'ML, like Gecko) Chrome/66.0.3359.181 Safari/537.36'
    Request.Ranges.Units = 'bytes'
    Request.Ranges = <>
    HTTPOptions = [hoForceEncodeParams]
    Left = 248
    Top = 248
  end
end
