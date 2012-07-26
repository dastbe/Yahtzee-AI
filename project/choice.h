#ifndef _CHOICE_H_
#define _CHOICE_H_

#include "cassert"
#include "string"
#include "boost/lexical_cast.hpp"

// Defines a choice in our game
//
// Created by: David Bell
// March 24th, 2012

enum ChoiceAction {
	ACES,
	TWOS,
	THREES,
	FOURS,
	FIVES,
	SIXES,
	THREE_OF_A_KIND,
	FOUR_OF_A_KIND,
	FULL_HOUSE,
	SMALL_STRAIGHT,
	LARGE_STRAIGHT,
	YAHTZEE,
	CHANCE,
	ROLL
};

// Contains all the information for choice

struct Choice {
	bool keep[5];
	ChoiceAction choice_todo;
	Choice(const ChoiceAction,const bool* = NULL);
	const int toResponseValue() const;
	const std::string to_s() const;
};

#endif
