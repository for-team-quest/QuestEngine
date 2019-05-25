#include "ICallBack.h"

CallBack::CallBack(Delegate() func) : func(func)
{
}

CallBack::~CallBack()
{
}

void CallBack::Func()
{
	func();
}
