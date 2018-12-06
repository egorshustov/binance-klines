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
	if (CheckBox1->Checked)//использовать прокси
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
	String exchangeInfo_json=Form1->IdHTTP1->Get(TIdURI::URLEncode(exchangeInfo_get));//получим информацию о бирже

	TJSONObject* exchangeInfo_obj = (TJSONObject*)TJSONObject::ParseJSONValue(BytesOf((UnicodeString)exchangeInfo_json),0);//загрузим информацию о бирже в TJSONObject
	TJSONArray*  symbols_array =  (TJSONArray*)exchangeInfo_obj->GetValue("symbols");//из TJSONObject получим ссылку на массив данных TJSONArray "symbols"
	int size = symbols_array->Count;//определим размер массива данных "symbols"

	ofstream fout1;
	fout1.open("symbols.txt");
	fout1<<"BTC_USDT"<<std::endl;//добавлять также пару BTCUSDT
	for (int i = 0; i < size; ++i)//пройдёмся по каждому элементу данных массива "symbols"
	{
		TJSONValue* LJsonValue = symbols_array->Items[i];//получим значение TJSONValue элемента данных массива "symbols"
		TJSONArray*  symbol_array =  (TJSONArray*)LJsonValue;//преобразуем TJSONValue в TJSONArray
		TJSONObject* symbol_array_obj =(TJSONObject*)symbol_array;//преобразуем TJSONArray в TJSONObject для выполнения функции GetValue()
		//TJSONValue*  symbol_value =  symbol_array_obj->GetValue("symbol");//получим значение строки "symbol" элемента данных массива "symbols"
		//String symbol = symbol_value->Value();//преобразуем его в String
		//String last_three_symbols = symbol.SubString(symbol.Length()-2,3);//получим последние три символа валютной пары
		TJSONValue*  baseAsset_value =  symbol_array_obj->GetValue("baseAsset");//получим значение строки "baseAsset" элемента данных массива "symbols"
		String baseAsset = baseAsset_value->Value();//преобразуем его в String
		TJSONValue*  quoteAsset_value =  symbol_array_obj->GetValue("quoteAsset");//получим значение строки "quoteAsset" элемента данных массива "symbols"
		String quoteAsset = quoteAsset_value->Value();//преобразуем его в String
		TJSONValue*  status_value =  symbol_array_obj->GetValue("status");//получим значение строки "status" элемента данных массива "symbols"
		String status = status_value->Value();//преобразуем его в String
		if ((quoteAsset=="BTC")&&(status=="TRADING"))//запишем в файл те валютные пары, последние три символа которых - BTC, и которые находятся в статусе "TRADING"
		{
			fout1<<(UTF8String)baseAsset.c_str()+"_"+(UTF8String)quoteAsset.c_str()<<std::endl;
		}
	}
	fout1.close();
	delete exchangeInfo_obj;//указатель необходимо освобождать вручную,
		//так как он не освобождается сам, даже после завершения работы функции.
		//вместе с уничтожением данного указателя, автоматически уничтожаются все его подчиненные.


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
    if (CheckBox1->Checked)//использовать прокси
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

