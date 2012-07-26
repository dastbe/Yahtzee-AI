#ifndef _STATE_H_
#define _STATE_H_

#include "playercard.h"
#include "diceroll.h"
#include "choice.h"
#include "string"

// State contains the current state of the game
// in an easily queryable form.
// 
// The validity of a choice is checked here
// because it depends on both PlayerCard AND DiceRoll
//
// Created by: David Bell
// March 24th, 2012

// TODO: Implement Joker rule

struct State
{
	PlayerCard player_card;
	PlayerCard rival_card;
	DiceRoll current_dice;
	State(const PlayerCard,const PlayerCard,const DiceRoll);
	const State performScoringChoice(const Choice) const;
	bool isLegal(const Choice) const;
	bool isLegal(const ChoiceAction) const;
	const std::string to_s() const;
};

#endif
