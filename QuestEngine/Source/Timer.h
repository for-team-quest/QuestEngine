#pragma once
#include <iostream>
#include <vector>
#include <thread>
#include "ICallBack.h"
#include "TimerState.h"
#include "Defines.h"
using namespace std;
using namespace chrono;
using namespace this_thread;

#define DelegateType void
#define Sleep(x) sleep_for(milliseconds(x))


class Timer
{
public:
	TimerState state = TimerState::Active;

private:
	thread* space;
	ICallBack* callBack = nullptr;
	int delay = 1000;

public:
	void Start();
	int GetDelay();
	void Pause();
	void Join();

	Constructor Timer(ICallBack* callBack, int delay);
	Constructor Timer(CallBack* callBack, int delay);
	Constructor Timer(Delegate() callBack, int delay);
	Destructor Timer();
};



/*
	TEST CODE
*/
//class MyClass : public ICallBack
//{
//public:
//	void Run();
//};
//
//void MyClass::Run() 
//{
//	cout << "¾È³çÇÏ¼¼¿ä" << endl;
//	return;
//}
//...
//MyClass* my = new MyClass();
//Timer timer(my, 100);
//timer.Start();