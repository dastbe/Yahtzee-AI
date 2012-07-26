#ifndef _MY_AI_H_
#define _MY_AI_H_

#include "gameai.h"
#include "stdio.h"
#include "iostream"
#include "fstream"
#include "list"
#include "map"
#include "boost/array.hpp"

// Defines the logic for interpreting game state
// and what the appropriate response should be
// 
// Implements an heuristic that reasonably
// chooses a near-optimal response efficiently
// with regards to space and time
//
// Created by: David Bell
// March 24th, 2012

// TODO: Implement Joker Rule
// TODO: Better approximate upper section bonus in my heuristics

class MyAI : public virtual GameAI
{
private:
	std::map<int,float> ev_map;
	std::list< boost::array<bool,5> > keep_set_list;
public:
	MyAI(std::ostream&);
	void respondTo(const State) const;
	float expectedValue(const State, const Choice) const;
	float expectedPlayerScore(const State state) const;
	float expectedKeepSetScore(const State,const bool*) const;
	const std::list<Choice> allValidChoices(const State) const;
};


#endif
