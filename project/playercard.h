#ifndef _PLAYER_CARD_H_
#define _PLAYER_CARD_H_

#include "string"
#include "boost/lexical_cast.hpp"

// A struct for holding a player's scorecard
//
// Created by: David Bell
// March 24th, 2012

struct PlayerCard {
	int aces;
	int twos;
	int threes;
	int fours;
	int fives;
	int sixes;
	int three_of_a_kind;
	int four_of_a_kind;
	int full_house;
	int small_straight;
	int large_straight;
	int yahtzee;
	int chance;
	int yahtzee_bonus;
	PlayerCard(const int*);
	int upperSectionBonus() const;
	int currentTurn() const;
	const std::string to_s() const;
};

#endif
