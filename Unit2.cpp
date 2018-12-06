//---------------------------------------------------------------------------

#include <System.hpp>
#pragma hdrstop

#include "Unit2.h"
#include "Unit1.h"
#include <DBXJSON.hpp>
#include <fstream>
#include <math.hpp>
#pragma package(smart_init)
//---------------------------------------------------------------------------

__fastcall TParseThread1::TParseThread1(bool CreateSuspended)
	: TThread(CreateSuspended)
{
}
//---------------------------------------------------------------------------
void __fastcall TParseThread1::GetKlines(String symbol)
{
	String klines_get="https://api.binance.com/api/v1/klines?symbol="+StringReplace(symbol,"_","", TReplaceFlags()<<rfReplaceAll)+"&interval="+Form1->Edit1->Text+"&limit="+Form1->Edit2->Text;
	String klines_json;

	if (!Terminated)
	{
		klines_json="";
		try
		{
			klines_json=Form1->IdHTTP1->Get(klines_get);
		}
		catch (EIdException &E)
		{
			ofstream fout3;
			fout3.open("log_exception_GetKlines.txt");
			fout3<<klines_json.c_str()<<std::endl;
			fout3<<AnsiString(E.Message).c_str()<<std::endl<<std::endl;
			fout3.close();

			Form1->IdHTTP1->Socket->Close();
			Sleep(10000);
			Form1->IdHTTP1->Socket->Open();
			klines_json=Form1->IdHTTP1->Get(klines_get);
		}

		TJSONArray* klines_array = (TJSONArray*)TJSONObject::ParseJSONValue(BytesOf((UnicodeString)klines_json),0);

		int size = klines_array->Count;
		double open_last, close_last, spread_last, volume_last, progress_last, open, close, spread, volume, progress;

		//получим данные последней свечи:
		TJSONValue* LJsonValue = klines_array->Items[size-1];//получим значение TJSONValue элемента данных массива "symbols"
		TJSONArray*  kline_array =  (TJSONArray*)LJsonValue;//преобразуем TJSONValue в TJSONArray
		open_last = StrToFloat(StringReplace(kline_array->Items[1]->Value(),".",",", TReplaceFlags()<<rfReplaceAll));
		close_last = StrToFloat(StringReplace(kline_array->Items[4]->Value(),".",",", TReplaceFlags()<<rfReplaceAll));
		volume_last = StrToFloat(StringReplace(kline_array->Items[5]->Value(),".",",", TReplaceFlags()<<rfReplaceAll));
		spread_last = close_last - open_last;
		if (spread_last > 0)//если последняя свеча - свеча покупок, то сравним её прогресс (spread*volume) со средним прогрессом предыдущих свечей покупок
		{
			int buy_kandles_count=0;//количество покупных свечей
			double progress_sum=0;//суммарный прогресс покупных свечей
			for (int i = size-2; i >= 0; --i)
			{
				LJsonValue = klines_array->Items[i];//получим значение TJSONValue элемента данных массива "symbols"
				kline_array =  (TJSONArray*)LJsonValue;//преобразуем TJSONValue в TJSONArray
				open = StrToFloat(StringReplace(kline_array->Items[1]->Value(),".",",", TReplaceFlags()<<rfReplaceAll));
				close = StrToFloat(StringReplace(kline_array->Items[4]->Value(),".",",", TReplaceFlags()<<rfReplaceAll));
				volume = StrToFloat(StringReplace(kline_array->Items[5]->Value(),".",",", TReplaceFlags()<<rfReplaceAll));
				spread = close - open;
				if (spread > 0)//если свеча покупок
				{
					progress = spread*volume;
					progress_sum += progress;
					++buy_kandles_count;
				}

			  /*memoline = IntToStr(i); Synchronize(AddLineMemo1);

			  TJSONValue* LJsonValue = klines_array->Items[i];
			  TJSONArray*  kline_array =  (TJSONArray*)LJsonValue;
			  int size2 = kline_array->Count;
			  for (int j = 0; j < size2; ++j)
			  {
				  TJSONValue* LItem   = kline_array->Items[j];
				  memoline = (UTF8String )(LItem->Value()).c_str(); Synchronize(AddLineMemo1);
			  }
			  memoline = ""; Synchronize(AddLineMemo1);*/
			}

			String info;
			double progress_last = spread_last*volume_last;
			if (buy_kandles_count != 0)
			{
				double progress_avg = progress_sum/buy_kandles_count;
				double ratio = progress_last/progress_avg;
				memoline = symbol +": "+ FloatToStr(progress_last)+" "+FloatToStr(progress_avg)+" "+FloatToStr(RoundTo((ratio),-2)); Synchronize(AddLineMemo1);
				if (ratio > StrToFloat(Form1->Edit3->Text))
				{
					//подавать сигнал в телеграм

                    //узнаем цену на покупку, чтобы фиксировать её в сигнале:
					String bookTicker_json = Form1->IdHTTP1->Get("https://api.binance.com/api/v3/ticker/bookTicker?symbol="+StringReplace(symbol,"_","", TReplaceFlags()<<rfReplaceAll));
					TJSONObject* bookTicker_obj = (TJSONObject*)TJSONObject::ParseJSONValue(BytesOf((UnicodeString)bookTicker_json),0);
					TJSONValue*  askPrice_json =  bookTicker_obj->GetValue("askPrice");
					String askPrice = askPrice_json->Value();
					delete bookTicker_obj;

					info="СВЕЧА ПОКУПОК! https://www.binance.com/en/trade/"+symbol+" (соотношение прогрессов "+FloatToStr(RoundTo((ratio),-2))+", интервал "+Form1->Edit1->Text+", количество свечей "+Form1->Edit2->Text+", цена на покупку "+askPrice+")";
					memoline = "ПОДАЁМ СИГНАЛ!"; Synchronize(AddLineMemo1);
					//new TSendThread(false, info);
					SendSignal(info);
				}
			}
			else
			{
				//подавать сигнал в телеграм

				//узнаем цену на покупку, чтобы фиксировать её в сигнале:
				String bookTicker_json = Form1->IdHTTP1->Get("https://api.binance.com/api/v3/ticker/bookTicker?symbol="+StringReplace(symbol,"_","", TReplaceFlags()<<rfReplaceAll));
				TJSONObject* bookTicker_obj = (TJSONObject*)TJSONObject::ParseJSONValue(BytesOf((UnicodeString)bookTicker_json),0);
				TJSONValue*  askPrice_json =  bookTicker_obj->GetValue("askPrice");
				String askPrice = askPrice_json->Value();
                delete bookTicker_obj;

				memoline = symbol +": "+ FloatToStr(progress_last); Synchronize(AddLineMemo1);
				info="СВЕЧА ПОКУПОК! https://www.binance.com/en/trade/"+symbol+" (прогресс последней свечи "+FloatToStr(progress_last)+", интервал "+Form1->Edit1->Text+", количество свечей "+Form1->Edit2->Text+", цена на покупку "+askPrice+")";
				memoline = "ПОДАЁМ СИГНАЛ!"; Synchronize(AddLineMemo1);
				//new TSendThread(false, info);
				SendSignal(info);
			}
		}
		delete klines_array;//указатель необходимо освобождать вручную,
		//так как он не освобождается сам, даже после завершения работы функции.
		//вместе с уничтожением данного указателя, автоматически уничтожаются все его подчиненные (LJsonValue, kline_array и другие).
	}
}
void __fastcall TParseThread1::SendSignal(String m_info)
{
	String messages_send="https://api.telegram.org/bot672161629:AAGdGgdDATn5Ghl7yFp9_jnNEj_jeq5EDZA/sendMessage?chat_id=-1001252001706&text=";
	messages_send.operator +=(m_info);
	try
	{
		String buf=Form1->IdHTTP2->Get(TIdURI::URLEncode(messages_send));
		ofstream fout2;
		fout2.open("log_tg.txt",ios::app);
		fout2<<AnsiString(buf).c_str()<<std::endl<<std::endl;
		fout2.close();
		if ((Pos("error",buf)!=0))
		{
			//Application->ProcessMessages();
			Sleep(30000);
			buf = Form1->IdHTTP2->Get(TIdURI::URLEncode(messages_send));
		}
	}
	catch (EIdException &E)
	{
		Form1->IdHTTP2->Socket->Close();
		Sleep(10000);
		Form1->IdHTTP2->Socket->Open();

		String buf=Form1->IdHTTP2->Get(TIdURI::URLEncode(messages_send));
		ofstream fout3;
		fout3.open("log_exception_SendSignal.txt",ios::app);
		fout3<<AnsiString(E.Message+" ----- "+buf).c_str()<<std::endl<<std::endl;
		fout3.close();
	}
}
//---------------------------------------------------------------------------
void __fastcall TParseThread1::AddLineMemo1()
{
	Form1->Memo1->Lines->Add(memoline);
}
//---------------------------------------------------------------------------
void __fastcall TParseThread1::Execute()
{
	//---- Place thread code here ----
	FreeOnTerminate = true;
	//получим список валютных пар из текстовика:
	ifstream f("symbols.txt", ios::in);
	String symbols[1000];
	char txt_line[10];
	int n=0;
	if (f != 0)
	{
		while (f.eof() != true)
		{
			memset(txt_line,'\0', 10);
			f.getline(txt_line, 10);
			symbols[n++] = txt_line;
		}
	}
	int i=0;
	while (!Terminated)
	{
		GetKlines(symbols[i++]);
		if (i==n-1)
		{
			i=0;
		}
	}
}
//---------------------------------------------------------------------------
