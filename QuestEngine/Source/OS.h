#pragma once
#define Windows

#ifdef Windows
#include <Windows.h>
#elif Linux
#include <pthread.h>
#endif

