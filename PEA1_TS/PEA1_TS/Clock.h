
#pragma once
#include "stdafx.h"  
#include <windows.h>

class Clock {
	double PCFreq;
	__int64 CounterStart;
	double time;

public:
	Clock(void);
	~Clock(void);
	void startTimer();
	void endTimer();
	double ReturnTime();

};