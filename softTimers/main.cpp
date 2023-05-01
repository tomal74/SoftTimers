
#include <iostream>
#include <stdio.h>
#include <chrono>
#include <string>
#include <format>
#include <ctime>
#include <winsock2.h>
#include <ws2ipdef.h>
#include <conio.h>
#include <stdlib.h>

#include "SoftTimer.h"


enum
{
	WTCH_TIM, 
	RST_TIM
};


multiTimer Timers;
int cbCnt = 0;

void myTimerCb(SoftTimer* ST)
{
	//std::cout << ST->getTimerName() << " time elapsed: " << ST->getElapsedTime() << " time remaining: " << ST->getRemainingTime() << " callback called" << std::endl;

	if (cbCnt < 4u)
	{
		cbCnt++;
		std::cout << "RST_TIMER: " << " trigered?: " << (Timers.getTimer(WTCH_TIM).isTriggered() ? "yes" : "no") << std::endl;
		Timers.getTimer(WTCH_TIM).resetTimer();
	}
}

void myTimer2Cb(SoftTimer* ST)
{
	static bool isInitialized = false;
	std::cout << "WTCH_TIMER" << " cb no. 2 -- trigered?: " <<(  ST->isTriggered() ? "yes" : "no" )<< std::endl;

	cbCnt = 0;
	system("cls");

	if (!isInitialized)
	{
		isInitialized = true;

		std::cout << "adding New Timer RST_TIMER!" << std::endl;
		Timers.addTimer(1.1, RST_TIM, myTimerCb, true);
	}
	else 	std::cout << "WATCHDOG RESET!" << std::endl;
}





int main()
{
	// SoftTimer Timer1(2.1, NULL, false);
	//std::vector<SoftTimer> Timers;

	//Timers.push_back( SoftTimer(1, myTimerCb, true));
	//Timers.push_back( SoftTimer(2, myTimerCb, true));

	//Timers.push_back(SoftTimer(1.2, myTimer2Cb, true));


	Sleep(1000u);
	std::cout << "Main START" << std::endl;

	Timers.addTimer(1.4, WTCH_TIM, myTimer2Cb, true);
	//Timers.addTimer(3.0, myTimerCb, true);

	while ( true )
	{
		Timers.TIMERS_EVENT();

		// Timer1.timerProcess();
		//TIMERS_EVENT(Timers);

		//Timers.pop_back();

	    // Timers.push_back( SoftTimer(2, myTimerCb, true));
	}

}