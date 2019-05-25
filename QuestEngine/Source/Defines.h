#pragma once

#define null nullptr
#define Constructor 
#define Destructor ~

//가변인자 매크로를 사용함
#define delegate(...) [&](__VA_ARGS__)-> DelegateType
#define Delegate(...) std::function<DelegateType(__VA_ARGS__)>
#define DelegateList(...) std::vector<Delegate(__VA_ARGS__)>

#define IsNull(x) x == null
#define IsNullToString_1(x) (const char*) (IsNull(x)? "true" : "false")
#define IsNullToString_2(x, y, z) (const char*) (IsNull(x)? y : z)
#define IsNullToString(...) IsNullToString_MACRO(__VA_ARGS__, IsNullToString_2, IsNullToString_1)(__VA_ARGS__)
#define IsNullToString_MACRO(_1,_2, NAME,...) NAME

#define PrintThreadID() cout << "currnt thread ID:" << this_thread::get_id() << endl

#define MainScheduler Scheduler::GetMainScheduler

#define OneSec 1000
#define FrameRateForUpdate OneSec/100
#define FrameRateForRender OneSec/50