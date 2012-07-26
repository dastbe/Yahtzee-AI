#include "state.h"

// Implements States as defined in state.h
//
// Created By: David Bell
// Edited: July 24, 2012


// Creates a state two PlayerCards and a DiceRoll
State::State(const PlayerCard player, const PlayerCard rival, const DiceRoll dice) : player_card(player), rival_card(rival), current_dice(dice)
{}

// Determines if a given Choice is legal for this state
bool State::isLegal(const Choice choice) const
{
	return isLegal(choice.choice_todo);
}

// Updates the State with a given choice (scoring only)
const State State::performScoringChoice(const Choice choice) const
{
	State return_state(*this);
	switch(choice.choice_todo)
	{
	case ACES:
		return_state.player_card.aces = current_dice.rollValue(ACES);
		break;
	case TWOS:
		return_state.player_card.twos = current_dice.rollValue(TWOS);
		break;
	case THREES:
		return_state.player_card.threes = current_dice.rollValue(THREES);
		break;
	case FOURS:
		return_state.player_card.fours = current_dice.rollValue(FOURS);
		break;
	case FIVES:
		return_state.player_card.fives = current_dice.rollValue(FIVES);
		break;
	case SIXES:
		return_state.player_card.sixes = current_dice.rollValue(SIXES);
		break;
	case THREE_OF_A_KIND:
		return_state.player_card.three_of_a_kind = current_dice.rollValue(THREE_OF_A_KIND);
		break;
	case FOUR_OF_A_KIND:
		return_state.player_card.four_of_a_kind = current_dice.rollValue(FOUR_OF_A_KIND);
		break;
	case FULL_HOUSE:
		return_state.player_card.full_house = current_dice.rollValue(FULL_HOUSE);
		break;
	case SMALL_STRAIGHT:
		return_state.player_card.small_straight = current_dice.rollValue(SMALL_STRAIGHT);
		break;
	case LARGE_STRAIGHT:
		return_state.player_card.large_straight = current_dice.rollValue(LARGE_STRAIGHT);
		break;
	case YAHTZEE:
		return_state.player_card.yahtzee = current_dice.rollValue(YAHTZEE);
		break;
	case CHANCE:
		return_state.player_card.chance = current_dice.rollValue(CHANCE);
		break;
	}

	return return_state;
}

// Determines if a given ChoiceAction is legal for this state
bool State::isLegal(const ChoiceAction choice) const
{
	switch(choice) {
	case ACES:
		return player_card.aces == -1;
	case TWOS:
		return player_card.twos == -1;
	case THREES:
		return player_card.threes == -1;
	case FOURS:
		return player_card.fours == -1;
	case FIVES:
		return player_card.fives == -1;
	case SIXES:
		return player_card.sixes == -1;
	case THREE_OF_A_KIND:
		return player_card.three_of_a_kind == -1;
	case FOUR_OF_A_KIND:
		return player_card.four_of_a_kind == -1;
	case FULL_HOUSE:
		return player_card.full_house == -1;
	case SMALL_STRAIGHT:
		return player_card.small_straight == -1;
	case LARGE_STRAIGHT:
		return player_card.large_straight == -1;
	case YAHTZEE:
		return player_card.yahtzee == -1;
	case CHANCE:
		return player_card.chance == -1;
	case ROLL:
		return current_dice.turn != 3;
	}
}

// Returns the contents of state in a nice string format for debugging
const std::string State::to_s() const {
	return "Current"+player_card.to_s()+", Rival"+rival_card.to_s()+", "+current_dice.to_s();
}
