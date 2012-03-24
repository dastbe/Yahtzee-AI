#ifndef _GAME_PARSER_H_
#define _GAME_PARSER_H_

#include "iostream"
#include "string"
#include "state.h"
#include "stdio.h"
#include "boost/tokenizer.hpp"
#include "boost/lexical_cast.hpp"

// Parses a line from an inputstream and
// converts it into a State. If EOF is reached,
// terminates.
//
// Since we have high faith in the yahtzee gameplay
// and throwing an error would be pointless, this
// class performs no error checking on the data
//
// Created by: David Bell
// March 24th, 2012

class GameParser
{
private:
	std::istream& input;
public:
	GameParser(std::istream&);
	State readNewState();
} YahtzeeParser(std::cin);
	

GameParser::GameParser(std::istream& in) : input(in) {}

// Reads a line of input and creates a State
State GameParser::readNewState()
{
	// Arrays to be passed to various constructor functions
	int state_array[34] = {0};

	std::string line = "";
	getline(input,line);

	if (input.eof()) // Match is over
	{
		exit(0);
	}


	// Tokenize line input and put it into our state array
	boost::tokenizer< boost::char_separator<char> > str_tokenizer(line,boost::char_separator<char>(" "));

	int index = 0; // index for our state array
	for(boost::tokenizer< boost::char_separator<char> >::iterator itr = str_tokenizer.begin(); itr != str_tokenizer.end(); ++itr)
	{
		state_array[index] = boost::lexical_cast<int>(*itr);
		++index;
	}

	// Create PlayerCards and DiceRolls and return a new State
	PlayerCard player1(state_array);
	PlayerCard player2(state_array+14);
	DiceRoll dice_roll(state_array+28,*(state_array+33));
	return State(player1,player2,dice_roll);

}

#endif