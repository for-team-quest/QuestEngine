#pragma once
#include <vector>
#include <thread>
#include <functional>
#include "ICallBack.h"
#include "Defines.h"
using namespace std;
class Timer;

class Scheduler : public ICallBack
{
private:
	static Scheduler* mainScheduler;
	static vector<Timer*> timers;
	vector<ICallBack*> callBacks = vector<ICallBack*>();
public:
	// ICallBack을(를) 통해 상속됨
	virtual void Func() override;
	void AddCallBack(ICallBack* callBack);
public:
	static Scheduler* GetMainScheduler();
	Constructor Scheduler();
	Destructor Scheduler();

private:
	interface static_constructor
	{
		static_constructor();
	};
	static static_constructor c;
};


void Update();
void Render();