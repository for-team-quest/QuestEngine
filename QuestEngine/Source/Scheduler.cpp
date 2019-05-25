#pragma once
#include <iostream>
#include <string.h>
#include "Scheduler.h"
#include "Timer.h"
#define DelegateType void
Scheduler* Scheduler::mainScheduler  = new Scheduler();
vector<Timer*> Scheduler::timers = vector<Timer*>();
Scheduler::static_constructor Scheduler::c = Scheduler::static_constructor();

Scheduler::static_constructor::
static_constructor()
{
	bool once = true;
	size_t previousSize = 0;
	cout << "static_constructor 생성자가 실행됩니다." << endl;	
	PrintThreadID();
	cout << endl;

	//타이머들을 관리하기 위한 콜백.
	Delegate() timerManage = delegate()
	{
		cout << "timerManage가 실행됩니다." << endl;
		PrintThreadID();
		while (true)
		{
			//타이머가 timers 자료구조에 추가 될때마다 타이머의 스레드를 실행하여 갱신함.
			//현재크기가 이전크기보다 커졌는지 검사.
			//추가된 타이머를 실행.
			for (; previousSize < timers.size(); previousSize++)
			{
				once = true;
				cout << "추가완료, timers.size(): " << timers.size() << endl;
				timers[previousSize]->Start();
			}

			if (once)
			{
				once = false;
				cout << endl;
				cout << "callBacks size: " << mainScheduler->callBacks.size() << endl;
				cout << "대기중..." << endl;
			}
			Sleep(20);
		}
	};
	thread timerManager(timerManage);
	//...
	timers.push_back(new Timer(mainScheduler, 10));
	//Update for Physics and Logics
	timers.push_back(new Timer(Update, FrameRateForUpdate));
	//Update for Renderings
	timers.push_back(new Timer(Render, FrameRateForRender));
	//...
	timerManager.join();
	cout << "timerManager스레드가 종료됩니다." << endl;

	for (size_t i = 0; i < timers.size(); i++)
	{
		delete timers[i];
	}
	delete mainScheduler;
}

Scheduler* Scheduler::GetMainScheduler()
{
	return mainScheduler;
}

Scheduler::Scheduler()
{
}

Scheduler::~Scheduler()
{
	for (size_t i = 0; i < callBacks.size(); i++)
	{
		delete callBacks[i];
	}
}

void Scheduler::Func()
{
	for (size_t i = 0; i < callBacks.size(); i++)
	{
		callBacks[i]->Func();
	}
}

void Scheduler::AddCallBack(ICallBack* callBack)
{
	callBacks.push_back(callBack);
}
//Update for Physics and Logics
void Update()
{
	cout << "Update" << endl;
}
//Update for Renderings
void Render() 
{
	cout << "Renderer" << endl;
}

