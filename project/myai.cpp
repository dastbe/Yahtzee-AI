#include "myai.h"

// Implements MyAI as defined in myai.h
//
// Created By: David Bell
// Edited: July 24, 2012

// Default object
MyAI YahtzeeAI(std::cout);

// Constructor
MyAI::MyAI(std::ostream& out) : GameAI(out) 
{

	// Build a map of key-set => expected value pairs
	std::ifstream ev_file;
	ev_file.open("data/ev_file.txt");

	if (!ev_file.is_open())
	{
		std::cout << "ev_file.txt does not exist! Rerun the build script" << std::endl;
		exit(1);
	}

	while(ev_file.good())
	{
		int key = -1;
		float value = 0.0f;
		ev_file >> key >> value;
		ev_map.insert(std::pair<int,float>(key,value));
	}

	ev_file.close();

	// Build a list of all possible key-set-booleans
	std::ifstream ksb_file;
	ksb_file.open("data/ksb_file.txt");

	if (!ksb_file.is_open())
	{
		std::cout << "ksb_file.txt does not exist! Rerun the build script" << std::endl;
		exit(1);
	}

	while(ksb_file.good()) {
		boost::array<bool,5> keep_set = {false,false,false,false,false};
		ksb_file >> keep_set[0] >> keep_set[1] >> keep_set[2] >> keep_set[3] >> keep_set[4];
		keep_set_list.push_front(keep_set);
	}

	ksb_file.close();

}

// Method that takes a state and gives an appropriate response
void MyAI::respondTo(const State state) const
{
	std::list<Choice> choice_list = allValidChoices(state);

	Choice max_choice = choice_list.front();

	for (std::list<Choice>::iterator itr = choice_list.begin(); itr != choice_list.end(); ++itr)
	{
		if (expectedValue(state,max_choice) < expectedValue(state,*itr)) max_choice = *itr;
		#ifdef _TEST_
			output << itr->to_s() << " with expected value: "  << expectedValue(state,*itr) << std::endl;
		#endif

	}

	#ifdef _TEST_
		output << "Best Choice was: " << max_choice.to_s() << " with expected value: " << expectedValue(state,max_choice) << std::endl;
	#else
		output << max_choice.toResponseValue() << std::endl;
	#endif
}


// Returns the expectedValue of a given State,Choice pair
float MyAI::expectedValue(const State state, const Choice choice) const
{
	float expected_value = 0.0f;
	switch(choice.choice_todo)
	{
		case ACES:
		case TWOS:
		case THREES:
		case FOURS:
		case FIVES:
		case SIXES:
		case THREE_OF_A_KIND:
		case FOUR_OF_A_KIND:
		case FULL_HOUSE:
		case SMALL_STRAIGHT:
		case LARGE_STRAIGHT:
		case YAHTZEE:
		case CHANCE:
			return expectedPlayerScore(state.performScoringChoice(choice));
			break;
		case ROLL:
			return expectedKeepSetScore(state,choice.keep);
			break;
	}
	return expected_value;
}

// Calculates the expected score for a player in a given state
float MyAI::expectedPlayerScore(const State state) const
{
	float ev_array[14] = {1.88f, 5.28f, 8.56f, 12.16f, 15.69f, 19.18f, 21.66f, 13.09f, 22.59f, 29.46f, 32.70f, 16.87f, 22.01f, 23.80};

	float score = 0.0f;

	// Calculate score for each scoring category
	if (state.player_card.aces >= 0) score += state.player_card.aces; else score += ev_array[0];
	if (state.player_card.twos >= 0) score += state.player_card.twos; else score += ev_array[1];
	if (state.player_card.threes >= 0) score += state.player_card.threes; else score += ev_array[2];
	if (state.player_card.fours >= 0) score += state.player_card.fours; else score += ev_array[3];
	if (state.player_card.fives >= 0) score += state.player_card.fives; else score += ev_array[4];
	if (state.player_card.sixes >= 0) score += state.player_card.sixes; else score += ev_array[5];
	if (state.player_card.three_of_a_kind >= 0) score += state.player_card.three_of_a_kind; else score += ev_array[6];
	if (state.player_card.four_of_a_kind >= 0) score += state.player_card.four_of_a_kind; else score += ev_array[7];
	if (state.player_card.full_house >= 0) score += state.player_card.full_house; else score += ev_array[8];
	if (state.player_card.small_straight >= 0) score += state.player_card.small_straight; else score += ev_array[9];
	if (state.player_card.large_straight >= 0) score += state.player_card.large_straight; else score += ev_array[10];
	if (state.player_card.yahtzee >= 0) score += state.player_card.yahtzee; else score += ev_array[11];
	if (state.player_card.chance >= 0) score += state.player_card.chance; else score += ev_array[12];
	
	// Calculate upper score bonus
	// This is a poor approximation!
	if (state.player_card.upperSectionBonus() > 0) score += state.player_card.upperSectionBonus(); else score += ev_array[13];


	float turn = state.player_card.currentTurn()-1;
	float modifier = (-turn*0.04f)+0.925f;

	return score;
}

// Calculates the expected score for a given keep-set
float MyAI::expectedKeepSetScore(const State state, const bool* keep_set) const
{
	// Expected values for entries
	float ev_array[14] = {1.88f, 5.28f, 8.56f, 12.16f, 15.69f, 19.18f, 21.66f, 13.09f, 22.59f, 29.46f, 32.70f, 16.87f, 22.01f, 23.80};
	
	// Generate keep_set
	std::list<int> keep_set_val;
	for (int i = 0; i < 5; ++i)
	{
		if (keep_set[i])
		{
			keep_set_val.push_back(state.current_dice.dice[i]);
		}
	}

	int keep_set_index = 0;

	for (std::list<int>::iterator itr = keep_set_val.begin(); itr != keep_set_val.end(); ++itr)
	{
		keep_set_index += *itr;
		keep_set_index *= 10;
	}

	float score = ev_map.find(keep_set_index)->second;

	// Update it with known values
	if (state.player_card.aces >= 0) score += (state.player_card.aces - ev_array[0]);
	if (state.player_card.twos >= 0) score += (state.player_card.twos - ev_array[1]);
	if (state.player_card.threes >= 0) score += (state.player_card.threes - ev_array[2]);
	if (state.player_card.fours >= 0) score += (state.player_card.fours - ev_array[3]);
	if (state.player_card.fives >= 0) score += (state.player_card.fives - ev_array[4]);
	if (state.player_card.sixes >= 0) score += (state.player_card.sixes - ev_array[5]);
	if (state.player_card.three_of_a_kind >= 0) score += (state.player_card.three_of_a_kind - ev_array[6]);
	if (state.player_card.four_of_a_kind >= 0) score += (state.player_card.four_of_a_kind - ev_array[7]);
	if (state.player_card.full_house >= 0) score += (state.player_card.full_house - ev_array[8]);
	if (state.player_card.small_straight >= 0) score += (state.player_card.small_straight - ev_array[9]);
	if (state.player_card.large_straight >= 0) score += (state.player_card.large_straight - ev_array[10]);
	if (state.player_card.yahtzee >= 0) score += (state.player_card.yahtzee - ev_array[11]);
	if (state.player_card.chance >= 0) score += (state.player_card.chance - ev_array[12]);

	// Calculate upper score bonus
	// This is a poor approximation!
	if (state.player_card.upperSectionBonus() > 0) score += (state.player_card.upperSectionBonus() - ev_array[13]);

	return score;
}

// Constructs a list of all valid choices for a given state.
// 
// Assumes that we only want to score after the second reroll
const std::list<Choice> MyAI::allValidChoices(const State state) const
{
	std::list<Choice> choice_list;

	// Append all scoring options if we've rerolled twice

	if (state.current_dice.turn == 3) 
	{
		if (state.isLegal(ACES)) choice_list.push_front(Choice(ACES));
		if (state.isLegal(TWOS)) choice_list.push_front(Choice(TWOS));
		if (state.isLegal(THREES)) choice_list.push_front(Choice(THREES));
		if (state.isLegal(FOURS)) choice_list.push_front(Choice(FOURS));
		if (state.isLegal(FIVES)) choice_list.push_front(Choice(FIVES));
		if (state.isLegal(SIXES)) choice_list.push_front(Choice(SIXES));
		if (state.isLegal(THREE_OF_A_KIND)) choice_list.push_front(Choice(THREE_OF_A_KIND));
		if (state.isLegal(FOUR_OF_A_KIND)) choice_list.push_front(Choice(FOUR_OF_A_KIND));
		if (state.isLegal(FULL_HOUSE)) choice_list.push_front(Choice(FULL_HOUSE));
		if (state.isLegal(SMALL_STRAIGHT)) choice_list.push_front(Choice(SMALL_STRAIGHT));
		if (state.isLegal(LARGE_STRAIGHT)) choice_list.push_front(Choice(LARGE_STRAIGHT));
		if (state.isLegal(YAHTZEE)) choice_list.push_front(Choice(YAHTZEE));
		if (state.isLegal(CHANCE)) choice_list.push_front(Choice(CHANCE));
	}


	// If I can roll, test all possible keep sets
	if (state.isLegal(ROLL))
	{
		for (std::list< boost::array<bool,5> >::const_iterator itr = keep_set_list.begin(); itr != keep_set_list.end(); ++itr)
			choice_list.push_front(Choice(ROLL,itr->data()));
	}

	return choice_list;
}

