#pragma once
#include <functional>
#include <combaseapi.h>
#include "Defines.h"

#define DelegateType void
interface ICallBack
{
	virtual void Func() = 0;
};

class CallBack : public ICallBack
{
public:
	Delegate() func;
public:
	CallBack(Delegate() func);
	~CallBack();

	// ICallBack��(��) ���� ��ӵ�
	virtual void Func() override;
};
