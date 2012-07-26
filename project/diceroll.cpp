#include "diceroll.h"

// Implements DiceRoll as defined in diceroll.h
//
// Created by: David Bell
// Edited: July 24, 2012

DiceRoll::DiceRoll(const int* dice_roll, const int turn_number) : turn(turn_number)
{
	dice[0] = dice_roll[0];
	dice[1] = dice_roll[1];
	dice[2] = dice_roll[2];
	dice[3] = dice_roll[3];
	dice[4] = dice_roll[4];
	std::sort(dice,dice+5);

}

// Returns the sum of the dice
const int DiceRoll::sumAll() const
{
	return std::accumulate(dice,dice+5,0);
}

// Returns the sum of all dice equal to num
const int DiceRoll::sumIfEqual(const int num) const
{
	assert(num > 0 and num < 7);
	int sum = 0;
	for (int i = 0; i < 5; ++i)
		if (dice[i] == num) sum += dice[i];
	return sum;
}

// Returns the roll's value for a given scoring choice
const int DiceRoll::rollValue(const ChoiceAction choice) const
{
	switch(choice) {
	case ACES:
		return sumIfEqual(1);
	case TWOS:
		return sumIfEqual(2);
	case THREES:
		return sumIfEqual(3);
	case FOURS:
		return sumIfEqual(4);
	case FIVES:
		return sumIfEqual(5);
	case SIXES:
		return sumIfEqual(6);
	case THREE_OF_A_KIND:
		if (isThreeOfAKind())
			return sumAll();
		return 0;
	case FOUR_OF_A_KIND:
		if (isFourOfAKind())
			return sumAll();
		return 0;
	case FULL_HOUSE:
		if (isFullHouse())
			return 25;
		return 0;
	case SMALL_STRAIGHT:
		if (isSmallStraight())
			return 30;
		return 0;
	case LARGE_STRAIGHT:
		if (isLargeStraight())
			return 40;
		return 0;
	case YAHTZEE:
		if (isYahtzee())
			return 50;
		return 0;
	case CHANCE:
		return sumAll();
	case ROLL:
		assert(false); // Unscorable!
	}
}

// Checks to see if there are num_satisfy of the same object starting at start_index
const bool DiceRoll::isKind(const int start_index, const int num_satisfy) const
{
	assert(start_index+num_satisfy <= 5 and num_satisfy > 0);

	int kind = *(dice+start_index);
	for (int* itr = (int*)dice+start_index; itr < dice+(start_index+num_satisfy); ++itr)
		if (*itr != kind) return false;
	return true;
}

// Checks to see if their a straight of length num_satisfy starting at start_index
const bool DiceRoll::isStraight(const int start_index, const int num_satisfy) const
{
	assert(start_index+num_satisfy <= 5 and num_satisfy > 0);

	int previous = *(dice+start_index);
	for (int* itr = (int*)dice+start_index+1; itr < dice+(start_index+num_satisfy); ++itr)
	{
		if (*itr != previous+1) return false;
		previous = *itr;
	}
	return true;

}


// Returns if the dice form a three of a kind
const bool DiceRoll::isThreeOfAKind() const
{
	return isKind(0,3) or isKind(1,3) or isKind(2,3);
}


// Returns if the dice form a four of a kind
const bool DiceRoll::isFourOfAKind() const
{
	return isKind(0,4) or isKind(1,4);
}

// Returns if the dice form a full house
const bool DiceRoll::isFullHouse() const
{
	return ((isKind(0,2) and isKind(2,3)) or (isKind(0,3) and isKind(3,2))) and dice[0] != dice[4];
}

// Returns if the dice form a small straight
const bool DiceRoll::isSmallStraight() const
{
	return isStraight(0,4) or isStraight(1,4);
}

// Returns if the dice form a large straight
const bool DiceRoll::isLargeStraight() const
{
	return isStraight(0,5);
}

// Returns if the dice form a Yahtzee
const bool DiceRoll::isYahtzee() const
{
	return dice[0] == dice[1] and dice[1] == dice[2] and dice[2] == dice[3] and dice[3] == dice[4];
}

// Returns a string representation of a dice roll. Used for debugging.
const std::string DiceRoll::to_s() const {
	return	"DiceRoll: ["+
			boost::lexical_cast<std::string>(dice[0])+", "+
			boost::lexical_cast<std::string>(dice[1])+", "+
			boost::lexical_cast<std::string>(dice[2])+", "+
			boost::lexical_cast<std::string>(dice[3])+", "+
			boost::lexical_cast<std::string>(dice[4])+"] Turn: ["+
			boost::lexical_cast<std::string>(turn)+"]";
}
