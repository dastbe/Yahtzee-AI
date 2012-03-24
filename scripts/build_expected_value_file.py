# Builds a file that holds keep-set => expected value pairs
# Used by the Game AI to predict the value of keeping various rolls
#
# Created by: David Bell
# March 24th, 2012

import itertools, math

# The expected values for all 13 entries in the score card
score_card_ev = [1.88,5.28,8.56,12.16,15.69,19.18,21.66,13.09,22.59,29.46,32.70,16.87,22.01,23.80]

def isKind(dice,start_index, num_satisfy):
	previous = dice[start_index]
	for index in range(start_index,start_index+num_satisfy):
		if dice[index] != previous:
			return False
	return True

# functions for calculating types of rolls and their values
def isStraight(dice,start_index,num_satisfy):
	previous = dice[start_index]
	for index in range(start_index+1,start_index+num_satisfy):
		if dice[index] != previous+1:
			return False
		previous = dice[index]
	return True

def isThreeOfAKind(dice):
	return isKind(dice,0,3) or isKind(dice,1,3) or isKind(dice,2,3)

def isFourOfAKind(dice):
	return isKind(dice,0,4) or isKind(dice,1,4)

def isFullHouse(dice):
	return ((isKind(dice,0,2) and isKind(dice,2,3)) or (isKind(dice,0,3) and isKind(dice,3,2))) and dice[0] != dice[4]

def isSmallStraight(dice):
	return isStraight(dice,0,4) or isStraight(dice,1,4)

def isLargeStraight(dice):
	return isStraight(dice,0,5)

def isYahtzee(dice):
	return isKind(dice,0,5)

def acesValue(dice):
	return sum([x for x in dice if x == 1])

def twosValue(dice):
	return sum([x for x in dice if x == 2])

def threesValue(dice):
	return sum([x for x in dice if x == 3])

def foursValue(dice):
	return sum([x for x in dice if x == 4])

def fivesValue(dice):
	return sum([x for x in dice if x == 5])

def sixesValue(dice):
	return sum([x for x in dice if x == 6])

def threeOfAKindValue(dice):
	if isThreeOfAKind(dice):
		return sum(dice)
	return 0

def fourOfAKindValue(dice):
	if isFourOfAKind(dice):
		return sum(dice)
	return 0

def fullHouseValue(dice):
	if isFullHouse(dice):
		return 25
	return 0

def smallStraightValue(dice):
	if isSmallStraight(dice):
		return 30
	return 0

def largeStraightValue(dice):
	if isLargeStraight(dice):
		return 40
	return 0

def yahtzeeValue(dice):
	if isYahtzee(dice):
		return 50
	return 0

def chanceValue(dice):
	return sum(dice)

# Calculates expected value of a die roll
def expectedValueOfDice(dice):
	expected_value = 0
	expected_value += sum(score_card_ev[:0])+acesValue(dice)+sum(score_card_ev[1:])
	expected_value += sum(score_card_ev[:1])+twosValue(dice)+sum(score_card_ev[2:])
	expected_value += sum(score_card_ev[:2])+threesValue(dice)+sum(score_card_ev[3:])
	expected_value += sum(score_card_ev[:3])+foursValue(dice)+sum(score_card_ev[4:])
	expected_value += sum(score_card_ev[:4])+fivesValue(dice)+sum(score_card_ev[5:])
	expected_value += sum(score_card_ev[:5])+sixesValue(dice)+sum(score_card_ev[6:])
	expected_value += sum(score_card_ev[:6])+threeOfAKindValue(dice)+sum(score_card_ev[7:])
	expected_value += sum(score_card_ev[:7])+fourOfAKindValue(dice)+sum(score_card_ev[8:])
	expected_value += sum(score_card_ev[:8])+fullHouseValue(dice)+sum(score_card_ev[9:])
	expected_value += sum(score_card_ev[:9])+smallStraightValue(dice)+sum(score_card_ev[10:])
	expected_value += sum(score_card_ev[:10])+largeStraightValue(dice)+sum(score_card_ev[11:])
	expected_value += sum(score_card_ev[:11])+yahtzeeValue(dice)+sum(score_card_ev[12:])
	expected_value += sum(score_card_ev[:12])+chanceValue(dice)+sum(score_card_ev[13:])
	expected_value /= 13
	return expected_value

# Builds all possible dice rolls
dice_rolls = [p for p in itertools.combinations_with_replacement([1,2,3,4,5,6],5)]


# Builds dice_expected_value dictionary
dice_expected_value = {}

for dice_roll in dice_rolls:
	dice_expected_value[dice_roll] = expectedValueOfDice(dice_roll)


# Calculates the probability of a given keep-set of size n occuring when n dice are rolled
def probabilityOfKeepSet(keep_set):
	probability = math.factorial(len(keep_set))
	for value in range(1,7):
		num_value_in_set = sum([1 for x in keep_set if x == value])
		probability /= math.factorial(num_value_in_set)
	probability = float(probability)/6**len(keep_set) # Divide by all possible choices
	return probability

# Takes a keep_set and all possible adjunct keep_sets and calculates an expected value for that keep_set
def expectedValueOfKeepSet(keep_set,keep_set_list):
	expected_value = 0
	for keep_adjunct in keep_set_list:
		temp = list(keep_set+keep_adjunct)
		temp.sort()
		expected_value += probabilityOfKeepSet(keep_adjunct)*dice_expected_value[tuple(temp)]
	return expected_value

# All the possible keep-sets of various sizes
keep_set_list_zero = [x for x in itertools.combinations_with_replacement([1,2,3,4,5,6],0)]
keep_set_list_one = [x for x in itertools.combinations_with_replacement([1,2,3,4,5,6],1)]
keep_set_list_two = [x for x in itertools.combinations_with_replacement([1,2,3,4,5,6],2)]
keep_set_list_three = [x for x in itertools.combinations_with_replacement([1,2,3,4,5,6],3)]
keep_set_list_four = [x for x in itertools.combinations_with_replacement([1,2,3,4,5,6],4)]
keep_set_list_five = [x for x in itertools.combinations_with_replacement([1,2,3,4,5,6],5)]

# Converts a tuple to a string concatenation of its values
def catTuple(tuple):
	s = ""
	for t in tuple:
		s += str(t)
	s += "0"
	return s

# out puts keep-sets and expected values
for k in keep_set_list_zero:
	print catTuple(k), expectedValueOfKeepSet(k,keep_set_list_five)

for k in keep_set_list_one:
	print catTuple(k), expectedValueOfKeepSet(k,keep_set_list_four)

for k in keep_set_list_two:
	print catTuple(k), expectedValueOfKeepSet(k,keep_set_list_three)

for k in keep_set_list_three:
	print catTuple(k), expectedValueOfKeepSet(k,keep_set_list_two)

for k in keep_set_list_four:
	print catTuple(k), expectedValueOfKeepSet(k,keep_set_list_one)

for k in keep_set_list_five:
	print catTuple(k), expectedValueOfKeepSet(k,keep_set_list_zero)
