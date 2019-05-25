#pragma once
#include "SetEnum.h"


#define MAKE_ENUMS \
	NAME(Active),\
	NAME(Pause),\
	NAME(Exit) 

Enum(TimerState);
#undef NAME 
#define NAME(v) #v 
Strings(TimerState);

#undef MAKE_ENUMS