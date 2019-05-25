#pragma once
#include <vector>
#include "ICallBack.h"
using namespace std;
namespace base
{

	class Object
	{
	public:
		Object();
		~Object();
	};

	class Component
	{
	public:
		Component();
		~Component();
	};

	class Behavior : public Object, public ICallBack
	{
	private:
		vector<Component> components = { };
	public:
		//ICallBack을(를) 통해 상속됨
		virtual void Func() override;
		void Awake();
		void Update();
	public:
		Behavior();
		~Behavior();
	};
}