#include "gameparser.h"
#include "myai.h"

// Main loop for our Yahtzee AI
//
// Created by: David Bell
// March 24th, 2012

int main()
{
	while(true)
	{
		YahtzeeAI.respondTo(YahtzeeParser.readNewState());
	}
}