#include "playercard.h"

// Implements PlayerCard as defined in playercard.h
//
// Created By: David Bell
// Edited: July 24, 2012

// Constructs a PlayCard from a int[14]
PlayerCard::PlayerCard(const int* score) :
	aces(score[0]), twos(score[1]), threes(score[2]), fours(score[3]), fives(score[4]),
	sixes(score[5]), three_of_a_kind(score[6]), four_of_a_kind(score[7]), full_house(score[8]),
	small_straight(score[9]), large_straight(score[10]), yahtzee(score[11]), chance(score[12]), yahtzee_bonus(score[13])
{}

int PlayerCard::upperSectionBonus() const
{
	if (aces+twos+threes+fours+fives+sixes >= 63)
		return 35;
	return 0;
}

// Returns the current turn number 0-indexed
int PlayerCard::currentTurn() const
{
	int turn = 0;
	if (aces >= 0) turn++;
	if (twos >= 0) turn++;
	if (threes >= 0) turn++;
	if (fours >= 0) turn++;
	if (fives >= 0) turn++;
	if (sixes >= 0) turn++;
	if (three_of_a_kind >= 0) turn++;
	if (four_of_a_kind >= 0) turn++;
	if (full_house >= 0) turn++;
	if (small_straight >= 0) turn++;
	if (large_straight >= 0) turn++;
	if (chance >= 0) turn++;
	if (yahtzee >= 0) turn++;
	return turn;

}

// Returns a string representation of a PlayerCard. Useful for debugging.
const std::string PlayerCard::to_s() const {
	return	"PlayerCard: ["+
			boost::lexical_cast<std::string>(aces)+", "+
			boost::lexical_cast<std::string>(twos)+", "+
			boost::lexical_cast<std::string>(threes)+", "+
			boost::lexical_cast<std::string>(fours)+", "+
			boost::lexical_cast<std::string>(fives)+", "+
			boost::lexical_cast<std::string>(sixes)+", "+
			boost::lexical_cast<std::string>(three_of_a_kind)+", "+
			boost::lexical_cast<std::string>(four_of_a_kind)+", "+
			boost::lexical_cast<std::string>(full_house)+", "+
			boost::lexical_cast<std::string>(small_straight)+", "+
			boost::lexical_cast<std::string>(large_straight)+", "+
			boost::lexical_cast<std::string>(yahtzee)+", "+
			boost::lexical_cast<std::string>(chance)+", "+
			boost::lexical_cast<std::string>(yahtzee_bonus)+"]";
}
