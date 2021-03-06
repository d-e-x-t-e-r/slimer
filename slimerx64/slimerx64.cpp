﻿/* slimerx64.cpp : A sleep and timer (slimer) extension to Lua. Includes a sleep,
*    msleep, and usleep function, as well as high resolution clock with a
*    resolution of under 1 microsecond. It's really more of a "Slock" than it is
*    "Slimer", but the name is too cool to change!
*
*    Specifically for use with 64bit Lua. See slimerx86 for a 32bit version.
*
* Author: Dexter Hughes
*/

#include "slimerx64.h"

// Query performance frequency
int slimer_qpf(lua_State *L) {
	LARGE_INTEGER perfrq;
	QueryPerformanceFrequency(&perfrq);
	lua_pushinteger(L, perfrq.QuadPart);
	return 1;
}

// Query performance counter
int slimer_qpc(lua_State *L) {
	LARGE_INTEGER percount;
	QueryPerformanceCounter(&percount);
	lua_pushinteger(L, percount.QuadPart);
	return 1;
}

// Query period in seconds
int slimer_period(lua_State *L) {
	LARGE_INTEGER perfrq;
	QueryPerformanceFrequency(&perfrq);
	double period = (double)1 / (double)perfrq.QuadPart;
	lua_pushinteger(L, period);
	return 1;
}

// sleep
int slimer_sleep(lua_State *L) {
	__int64 seconds = (__int64)luaL_checkinteger(L, 1) * 1000;
	Sleep(seconds);
	return 0;
}

// msleep
int slimer_msleep(lua_State *L) {
	__int64 mseconds = (__int64)luaL_checkinteger(L, 1);
	Sleep(mseconds);
	return 0;
}

// usleep
int slimer_usleep(lua_State *L) {
	HANDLE timer;
	LARGE_INTEGER dt;

	__int64 usec = (__int64)luaL_checkinteger(L, 1);
	dt.QuadPart = -(10 * usec); // converting microseconds to units of 100 nanoseconds
	timer = CreateWaitableTimer(NULL, TRUE, NULL); // timer uses 100 nanosecond intervals
	SetWaitableTimer(timer, &dt, 0, NULL, NULL, FALSE); // timer becomes signaled after dt * 100 nanoseconds
	WaitForSingleObject(timer, INFINITE); // waits thread until timer is signaled
	CloseHandle(timer);
	return 0;
}

// array of library functions to be registered
static const struct luaL_Reg slimer_functions [] = {
	{"frequency", slimer_qpf},
	{"clock", slimer_qpc},
	{"period", slimer_period},
	{"sleep", slimer_sleep},
	{"msleep", slimer_msleep},
	{"usleep", slimer_usleep},
	{NULL, NULL}
};

// registering function library
int luaopen_slimerx64(lua_State *L) {
	luaL_newlib(L, slimer_functions);
	return 1;
}

