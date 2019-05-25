#include "Timer.h"

void TimeCall(ICallBack* callBack, Timer* timer)
{
	TimerState* state = &timer->state;

	cout << "타이머를 시작합니다. 현재상태는" << (*state) << "입니다." << endl;
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
			cout << "잘못된 state의 값입니다. 코드를 확인바랍니다." << endl;
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