//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
#include <DBXJSON.hpp>
#include <fstream>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
TParseThread1 *myThread1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	Button2->Enabled=false;
	if (CheckBox1->Checked)//������������ ������
	{
		IdHTTP2->ProxyParams->ProxyServer = Edit4->Text;
		IdHTTP2->ProxyParams->ProxyPort = StrToInt(Edit5->Text);
		IdHTTP2->ProxyParams->ProxyUsername = Edit6->Text;
		IdHTTP2->ProxyParams->ProxyPassword = Edit7->Text;
	}
}
//---------------------------------------------------------------------------
__fastcall TForm1::~TForm1()
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
	Memo1->Clear();
	Button1->Enabled=false;
	Button2->Enabled=true;

	String exchangeInfo_get="https://api.binance.com/api/v1/exchangeInfo";
	String exchangeInfo_json=Form1->IdHTTP1->Get(TIdURI::URLEncode(exchangeInfo_get));//������� ���������� � �����

	TJSONObject* exchangeInfo_obj = (TJSONObject*)TJSONObject::ParseJSONValue(BytesOf((UnicodeString)exchangeInfo_json),0);//�������� ���������� � ����� � TJSONObject
	TJSONArray*  symbols_array =  (TJSONArray*)exchangeInfo_obj->GetValue("symbols");//�� TJSONObject ������� ������ �� ������ ������ TJSONArray "symbols"
	int size = symbols_array->Count;//��������� ������ ������� ������ "symbols"

	ofstream fout1;
	fout1.open("symbols.txt");
	fout1<<"BTC_USDT"<<std::endl;//��������� ����� ���� BTCUSDT
	for (int i = 0; i < size; ++i)//�������� �� ������� �������� ������ ������� "symbols"
	{
		TJSONValue* LJsonValue = symbols_array->Items[i];//������� �������� TJSONValue �������� ������ ������� "symbols"
		TJSONArray*  symbol_array =  (TJSONArray*)LJsonValue;//����������� TJSONValue � TJSONArray
		TJSONObject* symbol_array_obj =(TJSONObject*)symbol_array;//����������� TJSONArray � TJSONObject ��� ���������� ������� GetValue()
		//TJSONValue*  symbol_value =  symbol_array_obj->GetValue("symbol");//������� �������� ������ "symbol" �������� ������ ������� "symbols"
		//String symbol = symbol_value->Value();//����������� ��� � String
		//String last_three_symbols = symbol.SubString(symbol.Length()-2,3);//������� ��������� ��� ������� �������� ����
		TJSONValue*  baseAsset_value =  symbol_array_obj->GetValue("baseAsset");//������� �������� ������ "baseAsset" �������� ������ ������� "symbols"
		String baseAsset = baseAsset_value->Value();//����������� ��� � String
		TJSONValue*  quoteAsset_value =  symbol_array_obj->GetValue("quoteAsset");//������� �������� ������ "quoteAsset" �������� ������ ������� "symbols"
		String quoteAsset = quoteAsset_value->Value();//����������� ��� � String
		TJSONValue*  status_value =  symbol_array_obj->GetValue("status");//������� �������� ������ "status" �������� ������ ������� "symbols"
		String status = status_value->Value();//����������� ��� � String
		if ((quoteAsset=="BTC")&&(status=="TRADING"))//������� � ���� �� �������� ����, ��������� ��� ������� ������� - BTC, � ������� ��������� � ������� "TRADING"
		{
			fout1<<(UTF8String)baseAsset.c_str()+"_"+(UTF8String)quoteAsset.c_str()<<std::endl;
		}
	}
	fout1.close();
	delete exchangeInfo_obj;//��������� ���������� ����������� �������,
		//��� ��� �� �� ������������� ���, ���� ����� ���������� ������ �������.
		//������ � ������������ ������� ���������, ������������� ������������ ��� ��� �����������.


	myThread1 = new TParseThread1(false);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
	if (myThread1!=0)
	{
		myThread1->Terminate();
		//myThread1->Free();
	}
	Button1->Enabled=true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CheckBox1Click(TObject *Sender)
{
    if (CheckBox1->Checked)//������������ ������
	{
		IdHTTP2->ProxyParams->ProxyServer = Edit4->Text;
		IdHTTP2->ProxyParams->ProxyPort = StrToInt(Edit5->Text);
		IdHTTP2->ProxyParams->ProxyUsername = Edit6->Text;
		IdHTTP2->ProxyParams->ProxyPassword = Edit7->Text;
	}
	else
	{
		IdHTTP2->ProxyParams->ProxyServer = "";
		IdHTTP2->ProxyParams->ProxyPort = 0;
		IdHTTP2->ProxyParams->ProxyUsername = "";
		IdHTTP2->ProxyParams->ProxyPassword = "";
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCloseQuery(TObject *Sender, bool &CanClose)
{
 	if (myThread1!=0)
	{
		myThread1->Terminate();
		//myThread1->Free();
	}
}
//---------------------------------------------------------------------------

