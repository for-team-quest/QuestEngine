#include "Timer.h"

void TimeCall(ICallBack* callBack, Timer* timer)
{
	TimerState* state = &timer->state;

	cout << "Ÿ�̸Ӹ� �����մϴ�. ������´�" << (*state) << "�Դϴ�." << endl;
	while (true)
	{
		switch (*state)
		{
		case TimerState::Active:
			callBack->Func();
			Sleep(timer->GetDelay());
			break;

		case TimerState::Pause:
			Sleep(10);
			break;

		case TimerState::Exit:
			return;

		default:
			int s;
			cout << "�߸��� state�� ���Դϴ�. �ڵ带 Ȯ�ιٶ��ϴ�." << endl;
			cin >> s;
			*state = (TimerState)s;
			break;
		}
	}

	delete[] state;
	state = nullptr;
	return;
}

void Timer::Start()
{
	space = new thread(&TimeCall, callBack, this);
	cout << "Start" << endl;
}

void Timer::Join()
{
	if (space->joinable())
	{
		cout << "join" << endl;
		space->join();
	}
}

int Timer::GetDelay()
{
	return delay;
}

void Timer::Pause()
{
	state = TimerState::Pause;
	return;
}

Timer::Timer(ICallBack* callBack, int delay) : callBack(callBack), delay(delay)
{
	state = TimerState::Active;
}

Timer::Timer(CallBack* callBack, int delay) : callBack(callBack), delay(delay)
{
	state = TimerState::Active;
}

Timer::Timer(Delegate() callBack, int delay) : callBack(new CallBack(callBack)), delay(delay)
{
	state = TimerState::Active;	
}

Timer::~Timer()
{
	state = TimerState::Exit;
	delete[] space;
}