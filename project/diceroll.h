#ifndef _DICE_ROLL_H_
#define _DICE_ROLL_H_

#include "algorithm"
#include "numeric"
#include "cassert"
#include "climits"
#include "choice.h"
#include "string"
#include "boost/lexical_cast.hpp"

// Holds all the information regarding the currently rolled dice and turn number
// Is queryable for the types of rolls it satisfies 
// and their value for a given Choice.
// Sorts the dice to make types easier to find
//
// Created by: David Bell
// March 24th, 2012

// TODO: Make a function that returns all possible subsets of a given roll
// TODO: Implement understanding of the joker rule

struct DiceRoll
{
	int dice[5];
	int turn; 
	DiceRoll(const int*,const int);

	// Determining the value of a roll for a given scoring choice
	const int sumAll() const;
	const int sumIfEqual(const int) const;
	const int rollValue(const ChoiceAction) const;

	// Determining if rolls have certain characteristics
	const bool isKind(const int, const int) const;
	const bool isStraight(const int, const int) const;
	const bool isThreeOfAKind() const;
	const bool isFourOfAKind() const;
	const bool isFullHouse() const;
	const bool isSmallStraight() const;
	const bool isLargeStraight() const;
	const bool isYahtzee() const;
	const std::string to_s() const;
};

#endif
