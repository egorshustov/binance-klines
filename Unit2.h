//---------------------------------------------------------------------------

#ifndef Unit2H
#define Unit2H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
//---------------------------------------------------------------------------
class TParseThread1 : public TThread
{
private:
	String memoline;
protected:
	void __fastcall Execute();
public:
	__fastcall TParseThread1(bool CreateSuspended);
	void __fastcall GetKlines(String symbol);
	void __fastcall AddLineMemo1();
    void __fastcall SendSignal(String m_info);
};
//---------------------------------------------------------------------------
#endif
