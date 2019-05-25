#pragma once


	#define NAME(v) v
	#define Enum(name) enum name { MAKE_ENUMS };
	#define Strings(name) static const char* \
	name##Strings[] = { MAKE_ENUMS, };
	#undef MAKE_ENUMS

