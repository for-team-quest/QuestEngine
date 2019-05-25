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
	cout << "static_constructor �����ڰ� ����˴ϴ�." << endl;	
	PrintThreadID();
	cout << endl;

	//Ÿ�̸ӵ��� �����ϱ� ���� �ݹ�.
	Delegate() timerManage = delegate()
	{
		cout << "timerManage�� ����˴ϴ�." << endl;
		PrintThreadID();
		while (true)
		{
			//Ÿ�̸Ӱ� timers �ڷᱸ���� �߰� �ɶ����� Ÿ�̸��� �����带 �����Ͽ� ������.
			//����ũ�Ⱑ ����ũ�⺸�� Ŀ������ �˻�.
			//�߰��� Ÿ�̸Ӹ� ����.
			for (; previousSize < timers.size(); previousSize++)
			{
				once = true;
				cout << "�߰��Ϸ�, timers.size(): " << timers.size() << endl;
				timers[previousSize]->Start();
			}

			if (once)
			{
				once = false;
				cout << endl;
				cout << "callBacks size: " << mainScheduler->callBacks.size() << endl;
				cout << "�����..." << endl;
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
	cout << "timerManager�����尡 ����˴ϴ�." << endl;

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

