#include "gameparser.h"
#include "myai.h"
#include "boost/timer.hpp"

// Main loop for our Yahtzee AI
//
// Created by: David Bell
// March 24th, 2012

// extern YahtzeeParser;
// extern MyAI YahtzeeAI;

extern MyAI YahtzeeAI;

int main()
{
	#ifdef _TEST_
		boost::timer time;
		while(true)
		{
			State state = YahtzeeParser.readNewState();
			std::cout << state.to_s() << std::endl;
			time.restart();
			YahtzeeAI.respondTo(state);
			std::cout << "Response Time: " << time.elapsed() << " seconds" << std::endl;
		}
	#else
		while(true)
		{
			YahtzeeAI.respondTo(YahtzeeParser.readNewState());
		}
	#endif
}
