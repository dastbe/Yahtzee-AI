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
	Choice(const ChoiceAction,const bool*);
	const int toResponseValue() const;
	const std::string to_s() const;
};

// Creates a choice from a keep set and a ChoiceAction. Makes sure there is a keep set if I want to roll.
Choice::Choice(const ChoiceAction choice, const bool* keep_set = NULL) : choice_todo(choice)
{
	if (choice == ROLL)
	{
		if (keep_set == NULL)
			assert("Cannot roll with no keep set");
		keep[0] = keep_set[0];
		keep[1] = keep_set[1];
		keep[2] = keep_set[2];
		keep[3] = keep_set[3];
		keep[4] = keep_set[4];
	}
}

// Converts a choice to its numeric representation wrt the spec
const int Choice::toResponseValue() const
{
	int response_value = 0;
	switch(choice_todo)
	{
		case ACES:
			response_value = 0;
			response_value <<= 1;
			return response_value;
		case TWOS:
			response_value = 1;
			response_value <<= 1;
			return response_value;
		case THREES:
			response_value = 2;
			response_value <<= 1;
			return response_value;
		case FOURS:
			response_value = 3;
			response_value <<= 1;
			return response_value;
		case FIVES:
			response_value = 4;
			response_value <<= 1;
			return response_value;
		case SIXES:
			response_value = 5;
			response_value <<= 1;
			return response_value;
		case THREE_OF_A_KIND:
			response_value = 6;
			response_value <<= 1;
			return response_value;
		case FOUR_OF_A_KIND:
			response_value = 7;
			response_value <<= 1;
			return response_value;
		case FULL_HOUSE:
			response_value = 8;
			response_value <<= 1;
			return response_value;
		case SMALL_STRAIGHT:
			response_value = 9;
			response_value <<= 1;
			return response_value;
		case LARGE_STRAIGHT:
			response_value = 10;
			response_value <<= 1;
			return response_value;
		case YAHTZEE:
			response_value = 11;
			response_value <<= 1;
			return response_value;
		case CHANCE:
			response_value = 12;
			response_value <<= 1;
			return response_value;
		case ROLL:
			for (bool* itr = (bool*)keep+4; itr >= keep; --itr)
			{
				response_value += (int)*itr;
				response_value <<= 1;
			}
			return response_value+1;

	}
}

// Returns a string representation of a Choice. Useful for debugging
const std::string Choice::to_s() const
{
	switch(choice_todo)
	{
		case ACES:
			return "ACES";
		case TWOS:
			return "TWOS";
		case THREES:
			return "THREES";
		case FOURS:
			return "FOURS";
		case FIVES:
			return "FIVES";
		case SIXES:
			return "SIXES";
		case THREE_OF_A_KIND:
			return "THREE_OF_A_KIND";
		case FOUR_OF_A_KIND:
			return "FOUR_OF_A_KIND";
		case FULL_HOUSE:
			return "FULL_HOUSE";
		case SMALL_STRAIGHT:
			return "SMALL_STRAIGHT";
		case LARGE_STRAIGHT:
			return "LARGE_STRAIGHT";
		case YAHTZEE:
			return "YAHTZEE";
		case CHANCE:
			return "CHANCE";
		case ROLL:
			return "KEEP ["+boost::lexical_cast<std::string>(keep[0])+","+
							boost::lexical_cast<std::string>(keep[1])+","+
							boost::lexical_cast<std::string>(keep[2])+","+
							boost::lexical_cast<std::string>(keep[3])+","+
							boost::lexical_cast<std::string>(keep[4])+"]";
	}
}

#endif