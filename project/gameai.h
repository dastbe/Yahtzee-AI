#ifndef _GAME_AI_H_
#define _GAME_AI_H_

#include "state.h"

// Interface that we expect our AIs to conform to.
// It must take an output stream, which it then
// uses to output it's response to a game state S.
//
// Created by: David Bell
// March 24th, 2012

class GameAI
{
protected:
	std::ostream& output;
public:
	GameAI(std::ostream& out) : output(out) {}
	virtual void respondTo(const State) const = 0;
};

#endif
